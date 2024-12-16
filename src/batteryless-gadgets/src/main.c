/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/services/bas.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/logging/log.h>

#include <bluetooth/services/mds.h>

#include <zephyr/settings/settings.h>

#include <dk_buttons_and_leds.h>

#include <memfault/metrics/metrics.h>
#include <memfault/core/trace_event.h>

#include <memfault/core/platform/core.h>
#include "memfault/metrics/platform/overrides.h"
#include "memfault/core/data_export.h"

// -------------------------- ADC ----------------
#define ADC_DEVICE_NAME     DT_NODELABEL(arduino_adc)
#define ADC_RESOLUTION		12  // nRF52840 supports up to 12-bit resolution
#define ADC_GAIN            ADC_GAIN_1
#define ADC_REFERENCE       ADC_REF_INTERNAL
#define ADC_ACQUISITION_TIME  ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 10)
#define ADC_CHANNEL_ID      1  // AIN1 corresponds to channel 1

// Buffer for ADC sampling
static int16_t sample_buffer;

struct adc_channel_cfg adc_channel_cfg = {
    .gain             = ADC_GAIN_1_6,
    .reference        = ADC_REFERENCE,
    .acquisition_time = ADC_ACQUISITION_TIME,
    .channel_id       = ADC_CHANNEL_ID,
    .differential     = 0,
    .input_positive   = SAADC_CH_PSELP_PSELP_AnalogInput1 // differential SAADC_CH_PSELN_PSELN_AnalogInput1
};

// --------------------- ADC -------------------

#define DEVICE_NAME     CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

#define RUN_STATUS_LED DK_LED1
#define CON_STATUS_LED DK_LED2

#define RUN_LED_BLINK_INTERVAL 200

uint32_t button_press_count;

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_MDS_VAL),
};

static const struct bt_data sd[] = {
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static struct bt_conn *pairing_confirmation_conn;
static struct bt_conn *mds_conn;

static int batterylvl = 100;

// void memfault_platform_boot(void) {
//     memfault_boot();
// }

static void bas_work_handler(struct k_work *work);

static K_WORK_DELAYABLE_DEFINE(bas_work, bas_work_handler);

// --------------------- ADC ----------------------

// Setup ADC configuration
void configure_adc(void)
{
    const struct device *adc_dev = DEVICE_DT_GET(DT_NODELABEL(adc));
	// printk("1");
    if (!adc_dev) {
        printk("ADC device not found");
        return;
    }
	// printk("2");
    int err = adc_channel_setup(adc_dev, &adc_channel_cfg);
	// printk("3");
    if (err < 0) {
        printk("Error in ADC channel setup: %d", err);
        return;
    }
}


int read_adc_sample(void)
{
	// printk("4");
    const struct device *adc_dev = DEVICE_DT_GET(DT_NODELABEL(adc));
    if (!adc_dev) {
        printk("ADC device not found");
        return -ENODEV;
    }
	// printk("5");
    struct adc_sequence sequence = {
        .channels    = BIT(ADC_CHANNEL_ID),
        .buffer      = &sample_buffer,
        .buffer_size = sizeof(sample_buffer),
        .resolution  = ADC_RESOLUTION,
    };
	// printk("6");
    int err = adc_read(adc_dev, &sequence);
	// printk("7");
    if (err < 0) {
        printk("Error in ADC read: %d", err);
        return err;
    }
	// printk("8");
    // Convert the raw ADC value to a voltage (in millivolts)
    int16_t raw_value = sample_buffer;

	// Vref (set to internal voltage reference of the device, or set your own)
    float vref = 0.6;  // Internal reference voltage, for example

    // ADC Max Value for signed 12-bit resolution is 2047 (2^11 - 1)
    float adc_max_value = (1 << (ADC_RESOLUTION));  // 2047 for 12-bit

    // Apply the conversion formula to get the voltage in millivolts
    double millivolts = (raw_value / adc_max_value) * vref * 6;

    // int16_t millivolts = raw_value * 0.6 / (2<<(ADC_RESOLUTION-1));
	// int16_t millivolts = raw_value * ADC_GAIN / ADC_REFERENCE * (2<<(ADC_RESOLUTION));


    printk("ADC Reading: %d, Voltage: %.3f V \n", raw_value, millivolts);

    return millivolts;
}

// --------------------- ADC ----------------------

static void security_changed(struct bt_conn *conn, bt_security_t level,
			     enum bt_security_err err)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	if (!err) {
		printk("Security changed: %s level %u\n", addr, level);
	} else {
		printk("Security failed: %s level %u err %d\n", addr, level,
			err);
	}

	if (level >= BT_SECURITY_L2) {
		if (!mds_conn) {
			mds_conn = conn;
		}
	}
}

static void connected(struct bt_conn *conn, uint8_t conn_err)
{
	char addr[BT_ADDR_LE_STR_LEN];

	if (conn_err) {
		printk("Connection failed (err %u)\n", conn_err);
		return;
	}

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
	printk("Connected %s\n", addr);

	dk_set_led_on(CON_STATUS_LED);
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected (reason %u)\n", reason);

	dk_set_led_off(CON_STATUS_LED);

	if (conn == mds_conn) {
		mds_conn = NULL;
	}
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
	.security_changed = security_changed
};

static void pairing_complete(struct bt_conn *conn, bool bonded)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Pairing completed: %s, bonded: %d\n", addr, bonded);
}

static void pairing_failed(struct bt_conn *conn, enum bt_security_err reason)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Pairing failed conn: %s, reason %d\n", addr, reason);

	if (pairing_confirmation_conn) {
		pairing_confirmation_conn = NULL;
	}
}

static struct bt_conn_auth_info_cb conn_auth_info_callbacks = {
	.pairing_complete = pairing_complete,
	.pairing_failed = pairing_failed
};

static void auth_cancel(struct bt_conn *conn)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	printk("Pairing cancelled: %s\n", addr);
}

static void pairing_confirm(struct bt_conn *conn)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	pairing_confirmation_conn = conn;

	printk("Pairing confirmation required for %s\n", addr);
	printk("Press Button 1 to confirm, Button 2 to reject.\n");
}

static struct bt_conn_auth_cb conn_auth_callbacks = {
	.cancel = auth_cancel,
	.pairing_confirm = pairing_confirm,
};

static bool mds_access_enable(struct bt_conn *conn)
{
	if (mds_conn && (conn == mds_conn)) {
		return true;
	}

	return false;
}

static const struct bt_mds_cb mds_cb = {
	.access_enable = mds_access_enable,
};

static void button_handler(uint32_t button_state, uint32_t has_changed)
{
	static bool time_measure_start;

	int err;
	uint32_t buttons = button_state & has_changed;

	if ((buttons & DK_BTN1_MSK) & !pairing_confirmation_conn) {
		time_measure_start = !time_measure_start;

		if (time_measure_start) {
			err = MEMFAULT_METRIC_TIMER_START(button_1_elapsed_time_ms);
			if (err) {
				printk("Failed to start memfault metrics timer: %d\n", err);
			}
		} else {
			err = MEMFAULT_METRIC_TIMER_STOP(button_1_elapsed_time_ms);
			if (err) {
				printk("Failed to stop memfault metrics: %d\n", err);
			}

			/* Trigger collection of heartbeat data. */
			memfault_metrics_heartbeat_debug_trigger();
		}
	}

	if (buttons & DK_BTN1_MSK) {
		if (pairing_confirmation_conn) {
			err = bt_conn_auth_pairing_confirm(pairing_confirmation_conn);
			if (err) {
				printk("Failed to confirm the pairing: %d\n", err);
			} else {
				printk("Pairing confirmed\n");
			}

			pairing_confirmation_conn = NULL;
		}
	}

	if ((has_changed & DK_BTN2_MSK) && !pairing_confirmation_conn) {
		bool button_state = (buttons & DK_BTN2_MSK) ? 1 : 0;

		MEMFAULT_TRACE_EVENT_WITH_LOG(button_2_state_changed, "Button state: %u",
					      button_state);

		printk("button_2_state_changed event has been tracked, button state: %u\n",
		       button_state);
	}

	if (buttons & DK_BTN2_MSK) {
		if (pairing_confirmation_conn) {
			err = bt_conn_auth_cancel(pairing_confirmation_conn);
			if (err) {
				printk("Failed to reject the pairing: %d\n", err);
			} else {
				printk("Pairing rejected\n");
			}

			pairing_confirmation_conn = NULL;
		}
	}

	if (buttons & DK_BTN3_MSK) {
		button_press_count++;
		// err = MEMFAULT_METRIC_SET_UNSIGNED(button_3_press_count, button_press_count);
		memfault_metrics_heartbeat_add(MEMFAULT_METRICS_KEY(button_3_press_count), 1);
		if (err) {
			printk("Failed to increase button_3_press_count metric: %d\n", err);
		} else {
			printk("button_3_press_count metric increased to %d\n", button_press_count);
		}
	}

	if (buttons & DK_BTN4_MSK) {
		volatile uint32_t i;

		printk("Division by zero will now be triggered\n");
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdiv-by-zero"
		i = 1 / 0;
#pragma GCC diagnostic pop
		ARG_UNUSED(i);
	}
}

static void bas_notify(void)
{
	int err;
	// uint8_t battery_level = bt_bas_get_battery_level();

	uint8_t battery_level = batterylvl;

	__ASSERT_NO_MSG(battery_level > 0);

	battery_level--;

	if (battery_level == 0) {
		battery_level = 100U;
	}

	err = MEMFAULT_METRIC_SET_UNSIGNED(battery_soc_pct, battery_level);
	if (err) {
		printk("Failed to set battery_soc_pct memfault metrics (err %d)\n", err);
	}

	bt_bas_set_battery_level(battery_level);
}

static void bas_work_handler(struct k_work *work)
{
	bas_notify();
	k_work_reschedule((struct k_work_delayable *)work, K_SECONDS(1));
}

// LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main(void)
{
	uint32_t blink_status = 0;
	button_press_count=0;
	int err;
	memfault_metrics_heartbeat_set_unsigned(MEMFAULT_METRICS_KEY(button_3_press_count), 0);

	MEMFAULT_METRIC_SET_UNSIGNED(button_3_press_count, button_press_count);

	printk("Starting Bluetooth Memfault example\n");

	err = dk_leds_init();
	if (err) {
		printk("LEDs init failed (err %d)\n", err);
		return 0;
	}

	err = dk_buttons_init(button_handler);
	if (err) {
		printk("Failed to initialize buttons (err %d)\n", err);
		return 0;
	}

	err = bt_mds_cb_register(&mds_cb);
	if (err) {
		printk("Memfault Diagnostic service callback registration failed (err %d)\n", err);
		return 0;
	}

	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return 0;
	}

	err = bt_conn_auth_cb_register(&conn_auth_callbacks);
	if (err) {
		printk("Failed to register authorization callbacks (err %d)\n", err);
		return 0;
	}

	err = bt_conn_auth_info_cb_register(&conn_auth_info_callbacks);
	if (err) {
		printk("Failed to register authorization info callbacks (err %d)\n", err);
		return 0;
	}

	printk("Bluetooth initialized\n");

	if (IS_ENABLED(CONFIG_SETTINGS)) {
		err = settings_load();
		if (err) {
			printk("Failed to load settings (err %d)\n", err);
			return 0;
		}
	}

	err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad),
			      sd, ARRAY_SIZE(sd));
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return 0;
	}

	printk("Advertising successfully started\n");

	k_work_schedule(&bas_work, K_SECONDS(1));

	configure_adc();

	int times = 0;

	for (;;) {
		dk_set_led(RUN_STATUS_LED, (++blink_status) % 2);
		if(times%20 == 0){
			batterylvl--;
			// memfault_metrics_heartbeat_debug_print();
			printk("Should Execute memfault_metrics_heartbeat_debug_print\n");
			memfault_metrics_heartbeat_debug_trigger();
			// memfault_data_export_dump_chunks();
		}
		times++;
		read_adc_sample();
		k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL));
	}
}
