/*
 * Copyright (c) 2021 Bosch Sensortec GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

// SDA - P0-16
// SCL - P0-17
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <math.h>

int main(void) {
    const struct device *const dev = DEVICE_DT_GET_ONE(bosch_bmi270);
    struct sensor_value acc[3], gyr[3];
    struct sensor_value full_scale, sampling_freq, oversampling;

    if (!device_is_ready(dev)) {
        printk("Device %s is not ready\n", dev->name);
        return 0;
    }

    printk("Device %p name is %s\n", dev, dev->name);

    /* Setting scale in G, due to loss of precision if the SI unit m/s^2
	 * is used
	 */
    full_scale.val1 = 2; /* G */
    full_scale.val2 = 0;
    sampling_freq.val1 = 100; /* Hz. Performance mode */
    sampling_freq.val2 = 0;
    oversampling.val1 = 1; /* Normal mode */
    oversampling.val2 = 0;

    sensor_attr_set(dev, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_FULL_SCALE, &full_scale);
    sensor_attr_set(dev, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_OVERSAMPLING, &oversampling);
    /* Set sampling frequency last as this also sets the appropriate
	 * power mode. If already sampling, change to 0.0Hz before changing
	 * other attributes
	 */
    sensor_attr_set(dev, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_SAMPLING_FREQUENCY, &sampling_freq);

    /* Setting scale in degrees/s to match the sensor scale */
    full_scale.val1 = 500; /* dps */
    full_scale.val2 = 0;
    sampling_freq.val1 = 100; /* Hz. Performance mode */
    sampling_freq.val2 = 0;
    oversampling.val1 = 1; /* Normal mode */
    oversampling.val2 = 0;

    sensor_attr_set(dev, SENSOR_CHAN_GYRO_XYZ, SENSOR_ATTR_FULL_SCALE, &full_scale);
    sensor_attr_set(dev, SENSOR_CHAN_GYRO_XYZ, SENSOR_ATTR_OVERSAMPLING, &oversampling);
    /* Set sampling frequency last as this also sets the appropriate
	 * power mode. If already sampling, change sampling frequency to
	 * 0.0Hz before changing other attributes
	 */
    sensor_attr_set(dev, SENSOR_CHAN_GYRO_XYZ, SENSOR_ATTR_SAMPLING_FREQUENCY, &sampling_freq);

    uint32_t iteration = 0;  // Declare a counter

    while (1) {
        /* 10ms period, 100Hz Sampling frequency */
        k_sleep(K_MSEC(10));

        sensor_sample_fetch(dev);

        if (iteration++ % 200 == 0) {
            sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ, acc);  // m/s^2
            sensor_channel_get(dev, SENSOR_CHAN_GYRO_XYZ, gyr);   // rad/s

            float acc_x = acc[0].val1 + acc[0].val2 / 1000000.0;
            float acc_y = acc[1].val1 + acc[1].val2 / 1000000.0;
            float acc_z = acc[2].val1 + acc[2].val2 / 1000000.0;

            float gyr_x = gyr[0].val1 + gyr[0].val2 / 1000000.0;
            float gyr_y = gyr[1].val1 + gyr[1].val2 / 1000000.0;
            float gyr_z = gyr[2].val1 + gyr[2].val2 / 1000000.0;

            float gyr_x_dps = gyr_x * (180.0 / 3.14159265359);
            float gyr_y_dps = gyr_y * (180.0 / 3.14159265359);
            float gyr_z_dps = gyr_z * (180.0 / 3.14159265359);

            // Calculate pitch and roll 
            float pitch = atan2(acc_y, sqrt(acc_x * acc_x + acc_z * acc_z)) * (180.0 / 3.14159265359);
            float roll = atan2(-acc_x, sqrt(acc_y * acc_y + acc_z * acc_z)) * (180.0 / 3.14159265359);

            printk(
                "Acceleration (m/s^2): AX: %.6f; AY: %.6f; AZ: %.6f; \n"
                "Rotational velocity (deg/s): GX: %.6f; GY: %.6f; GZ: %.6f\n",
                acc_x, acc_y, acc_z, gyr_x_dps, gyr_y_dps, gyr_z_dps);

            // Print the calculated angles
            printk("Pitch (Angle X): %.2f degrees\n", pitch);
            printk("Roll (Angle Y): %.2f degrees\n", roll);

            printf("\n");
        }
        // Increment and reset the counter to avoid overflow
        iteration = (iteration + 1) % 200;

        k_sleep(K_MSEC(10));  // 10 ms sleep
    }
    return 0;
}