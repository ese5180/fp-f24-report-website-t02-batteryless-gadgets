/*
 * Copyright (c) 2021, Yonatan Schachter
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __RP2040_PINCTRL_H__
#define __RP2040_PINCTRL_H__

#define RP2_PINCTRL_GPIO_FUNC_XIP 0
#define RP2_PINCTRL_GPIO_FUNC_SPI 1
#define RP2_PINCTRL_GPIO_FUNC_UART 2
#define RP2_PINCTRL_GPIO_FUNC_I2C 3
#define RP2_PINCTRL_GPIO_FUNC_PWM 4
#define RP2_PINCTRL_GPIO_FUNC_SIO 5
#define RP2_PINCTRL_GPIO_FUNC_PIO0 6
#define RP2_PINCTRL_GPIO_FUNC_PIO1 7
#define RP2_PINCTRL_GPIO_FUNC_GPCK 8
#define RP2_PINCTRL_GPIO_FUNC_USB 9
#define RP2_PINCTRL_GPIO_FUNC_NULL 0xf

#define RP2_ALT_FUNC_POS 0
#define RP2_ALT_FUNC_MASK 0xf

#define RP2_PIN_NUM_POS 4
#define RP2_PIN_NUM_MASK 0x1f

#define RP2040_PINMUX(pin_num, alt_func) (pin_num << RP2_PIN_NUM_POS |	\
					alt_func << RP2_ALT_FUNC_POS)

#define UART0_TX_P0 RP2040_PINMUX(0, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART0_RX_P1 RP2040_PINMUX(1, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART0_CTS_P2 RP2040_PINMUX(2, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART0_RTS_P3 RP2040_PINMUX(3, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_TX_P4 RP2040_PINMUX(4, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_RX_P5 RP2040_PINMUX(5, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_CTS_P6 RP2040_PINMUX(6, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_RTS_P7 RP2040_PINMUX(7, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_TX_P8 RP2040_PINMUX(8, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_RX_P9 RP2040_PINMUX(9, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_CTS_P10 RP2040_PINMUX(10, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_RTS_P11 RP2040_PINMUX(11, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART0_TX_P12 RP2040_PINMUX(12, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART0_RX_P13 RP2040_PINMUX(13, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART0_CTS_P14 RP2040_PINMUX(14, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART0_RTS_P15 RP2040_PINMUX(15, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART0_TX_P16 RP2040_PINMUX(16, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART0_RX_P17 RP2040_PINMUX(17, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART0_CTS_P18 RP2040_PINMUX(18, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART0_RTS_P19 RP2040_PINMUX(19, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_TX_P20 RP2040_PINMUX(20, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_RX_P21 RP2040_PINMUX(21, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_CTS_P22 RP2040_PINMUX(22, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_RTS_P23 RP2040_PINMUX(23, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_TX_P24 RP2040_PINMUX(24, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_RX_P25 RP2040_PINMUX(25, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_CTS_P26 RP2040_PINMUX(26, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART1_RTS_P27 RP2040_PINMUX(27, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART0_TX_P28 RP2040_PINMUX(28, RP2_PINCTRL_GPIO_FUNC_UART)
#define UART0_RX_P29 RP2040_PINMUX(29, RP2_PINCTRL_GPIO_FUNC_UART)

#define I2C0_SDA_P0 RP2040_PINMUX(0, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SCL_P1 RP2040_PINMUX(1, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SDA_P2 RP2040_PINMUX(2, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SCL_P3 RP2040_PINMUX(3, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SDA_P4 RP2040_PINMUX(4, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SCL_P5 RP2040_PINMUX(5, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SDA_P6 RP2040_PINMUX(6, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SCL_P7 RP2040_PINMUX(7, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SDA_P8 RP2040_PINMUX(8, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SCL_P9 RP2040_PINMUX(9, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SDA_P10 RP2040_PINMUX(10, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SCL_P11 RP2040_PINMUX(11, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SDA_P12 RP2040_PINMUX(12, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SCL_P13 RP2040_PINMUX(13, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SDA_P14 RP2040_PINMUX(14, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SCL_P15 RP2040_PINMUX(15, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SDA_P16 RP2040_PINMUX(16, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SCL_P17 RP2040_PINMUX(17, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SDA_P18 RP2040_PINMUX(18, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SCL_P19 RP2040_PINMUX(19, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SDA_P20 RP2040_PINMUX(20, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SCL_P21 RP2040_PINMUX(21, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SDA_P22 RP2040_PINMUX(22, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SCL_P23 RP2040_PINMUX(23, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SDA_P24 RP2040_PINMUX(24, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SCL_P25 RP2040_PINMUX(25, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SDA_P26 RP2040_PINMUX(26, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C1_SCL_P27 RP2040_PINMUX(27, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SDA_P28 RP2040_PINMUX(28, RP2_PINCTRL_GPIO_FUNC_I2C)
#define I2C0_SCL_P29 RP2040_PINMUX(29, RP2_PINCTRL_GPIO_FUNC_I2C)

#define PWM_0A_P0 RP2040_PINMUX(0, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_0B_P1 RP2040_PINMUX(1, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_1A_P2 RP2040_PINMUX(2, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_1B_P3 RP2040_PINMUX(3, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_2A_P4 RP2040_PINMUX(4, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_2B_P5 RP2040_PINMUX(5, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_3A_P6 RP2040_PINMUX(6, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_3B_P7 RP2040_PINMUX(7, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_4A_P8 RP2040_PINMUX(8, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_4B_P9 RP2040_PINMUX(9, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_5A_P10 RP2040_PINMUX(10, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_5B_P11 RP2040_PINMUX(11, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_6A_P12 RP2040_PINMUX(12, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_6B_P13 RP2040_PINMUX(13, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_7A_P14 RP2040_PINMUX(14, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_7B_P15 RP2040_PINMUX(15, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_0A_P16 RP2040_PINMUX(16, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_0B_P17 RP2040_PINMUX(17, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_1A_P18 RP2040_PINMUX(18, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_1B_P19 RP2040_PINMUX(19, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_2A_P20 RP2040_PINMUX(20, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_2B_P21 RP2040_PINMUX(21, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_3A_P22 RP2040_PINMUX(22, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_3B_P22 RP2040_PINMUX(23, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_4A_P24 RP2040_PINMUX(24, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_4B_P25 RP2040_PINMUX(25, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_5A_P26 RP2040_PINMUX(26, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_5B_P27 RP2040_PINMUX(27, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_6A_P28 RP2040_PINMUX(28, RP2_PINCTRL_GPIO_FUNC_PWM)
#define PWM_6B_P29 RP2040_PINMUX(29, RP2_PINCTRL_GPIO_FUNC_PWM)

#define SPI0_RX_P0 RP2040_PINMUX(0, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_CSN_P1 RP2040_PINMUX(1, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_SCK_P2 RP2040_PINMUX(2, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_TX_P3 RP2040_PINMUX(3, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_RX_P4 RP2040_PINMUX(4, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_CSN_P5 RP2040_PINMUX(5, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_SCK_P6 RP2040_PINMUX(6, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_TX_P7 RP2040_PINMUX(7, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_RX_P8 RP2040_PINMUX(8, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_CSN_P9 RP2040_PINMUX(9, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_SCK_P10 RP2040_PINMUX(10, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_TX_P11 RP2040_PINMUX(11, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_RX_P12 RP2040_PINMUX(12, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_CSN_P13 RP2040_PINMUX(13, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_SCK_P14 RP2040_PINMUX(14, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_TX_P15 RP2040_PINMUX(15, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_RX_P16 RP2040_PINMUX(16, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_CSN_P17 RP2040_PINMUX(17, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_SCK_P18 RP2040_PINMUX(18, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_TX_P19 RP2040_PINMUX(19, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_RX_P20 RP2040_PINMUX(20, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_CSN_P21 RP2040_PINMUX(21, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_SCK_P22 RP2040_PINMUX(22, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI0_TX_P23 RP2040_PINMUX(23, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_RX_P24 RP2040_PINMUX(24, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_CSN_P25 RP2040_PINMUX(25, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_SCK_P26 RP2040_PINMUX(26, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_TX_P27 RP2040_PINMUX(27, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_RX_P28 RP2040_PINMUX(28, RP2_PINCTRL_GPIO_FUNC_SPI)
#define SPI1_CSN_P29 RP2040_PINMUX(29, RP2_PINCTRL_GPIO_FUNC_SPI)

#define ADC_CH0_P26 RP2040_PINMUX(26, RP2_PINCTRL_GPIO_FUNC_NULL)
#define ADC_CH1_P27 RP2040_PINMUX(27, RP2_PINCTRL_GPIO_FUNC_NULL)
#define ADC_CH2_P28 RP2040_PINMUX(28, RP2_PINCTRL_GPIO_FUNC_NULL)
#define ADC_CH3_P29 RP2040_PINMUX(29, RP2_PINCTRL_GPIO_FUNC_NULL)

#define PIO0_P0 RP2040_PINMUX(0, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P1 RP2040_PINMUX(1, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P2 RP2040_PINMUX(2, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P3 RP2040_PINMUX(3, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P4 RP2040_PINMUX(4, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P5 RP2040_PINMUX(5, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P6 RP2040_PINMUX(6, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P7 RP2040_PINMUX(7, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P8 RP2040_PINMUX(8, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P9 RP2040_PINMUX(9, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P10 RP2040_PINMUX(10, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P11 RP2040_PINMUX(11, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P12 RP2040_PINMUX(12, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P13 RP2040_PINMUX(13, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P14 RP2040_PINMUX(14, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P15 RP2040_PINMUX(15, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P16 RP2040_PINMUX(16, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P17 RP2040_PINMUX(17, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P18 RP2040_PINMUX(18, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P19 RP2040_PINMUX(19, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P20 RP2040_PINMUX(20, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P21 RP2040_PINMUX(21, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P22 RP2040_PINMUX(22, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P23 RP2040_PINMUX(23, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P24 RP2040_PINMUX(24, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P25 RP2040_PINMUX(25, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P26 RP2040_PINMUX(26, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P27 RP2040_PINMUX(27, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P28 RP2040_PINMUX(28, RP2_PINCTRL_GPIO_FUNC_PIO0)
#define PIO0_P29 RP2040_PINMUX(29, RP2_PINCTRL_GPIO_FUNC_PIO0)

#define PIO1_P0 RP2040_PINMUX(0, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P1 RP2040_PINMUX(1, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P2 RP2040_PINMUX(2, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P3 RP2040_PINMUX(3, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P4 RP2040_PINMUX(4, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P5 RP2040_PINMUX(5, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P6 RP2040_PINMUX(6, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P7 RP2040_PINMUX(7, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P8 RP2040_PINMUX(8, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P9 RP2040_PINMUX(9, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P10 RP2040_PINMUX(10, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P11 RP2040_PINMUX(11, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P12 RP2040_PINMUX(12, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P13 RP2040_PINMUX(13, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P14 RP2040_PINMUX(14, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P15 RP2040_PINMUX(15, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P16 RP2040_PINMUX(16, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P17 RP2040_PINMUX(17, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P18 RP2040_PINMUX(18, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P19 RP2040_PINMUX(19, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P20 RP2040_PINMUX(20, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P21 RP2040_PINMUX(21, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P22 RP2040_PINMUX(22, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P23 RP2040_PINMUX(23, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P24 RP2040_PINMUX(24, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P25 RP2040_PINMUX(25, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P26 RP2040_PINMUX(26, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P27 RP2040_PINMUX(27, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P28 RP2040_PINMUX(28, RP2_PINCTRL_GPIO_FUNC_PIO1)
#define PIO1_P29 RP2040_PINMUX(29, RP2_PINCTRL_GPIO_FUNC_PIO1)

#define GPIN0_P20 RP2040_PINMUX(20, RP2_PINCTRL_GPIO_FUNC_GPCK)
#define GPIN1_P22 RP2040_PINMUX(22, RP2_PINCTRL_GPIO_FUNC_GPCK)
#define GPOUT0_P21 RP2040_PINMUX(21, RP2_PINCTRL_GPIO_FUNC_GPCK)
#define GPOUT1_P23 RP2040_PINMUX(23, RP2_PINCTRL_GPIO_FUNC_GPCK)
#define GPOUT2_P24 RP2040_PINMUX(24, RP2_PINCTRL_GPIO_FUNC_GPCK)
#define GPOUT3_P25 RP2040_PINMUX(25, RP2_PINCTRL_GPIO_FUNC_GPCK)

#endif /* __RP2040_PINCTRL_H__ */
