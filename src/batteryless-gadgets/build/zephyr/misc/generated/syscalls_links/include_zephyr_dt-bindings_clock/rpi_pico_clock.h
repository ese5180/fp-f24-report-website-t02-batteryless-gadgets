/*
 * Copyright (c) 2022 Andrei-Edward Popa
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_RPI_PICO_CLOCK_H_
#define ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_RPI_PICO_CLOCK_H_

#define RPI_PICO_PLL_SYS   0
#define RPI_PICO_PLL_USB   1
#define RPI_PICO_PLL_COUNT 2

#define RPI_PICO_GPIN_0     0
#define RPI_PICO_GPIN_1     1
#define RPI_PICO_GPIN_COUNT 2

#define RPI_PICO_CLKID_CLK_GPOUT0 0
#define RPI_PICO_CLKID_CLK_GPOUT1 1
#define RPI_PICO_CLKID_CLK_GPOUT2 2
#define RPI_PICO_CLKID_CLK_GPOUT3 3
#define RPI_PICO_CLKID_CLK_REF    4
#define RPI_PICO_CLKID_CLK_SYS    5
#define RPI_PICO_CLKID_CLK_PERI   6
#define RPI_PICO_CLKID_CLK_USB    7
#define RPI_PICO_CLKID_CLK_ADC    8
#define RPI_PICO_CLKID_CLK_RTC    9

#define RPI_PICO_CLKID_PLL_SYS 10
#define RPI_PICO_CLKID_PLL_USB 11
#define RPI_PICO_CLKID_XOSC    12
#define RPI_PICO_CLKID_ROSC    13
#define RPI_PICO_CLKID_ROSC_PH 14
#define RPI_PICO_CLKID_GPIN0   15
#define RPI_PICO_CLKID_GPIN1   16

#define RPI_PICO_ROSC_RANGE_RESET   0xAA0
#define RPI_PICO_ROSC_RANGE_LOW     0xFA4
#define RPI_PICO_ROSC_RANGE_MEDIUM  0xFA5
#define RPI_PICO_ROSC_RANGE_HIGH    0xFA7
#define RPI_PICO_ROSC_RANGE_TOOHIGH 0xFA6

#define RPI_PICO_CLOCK_COUNT 10

#endif /* ZEPHYR_INCLUDE_DT_BINDINGS_CLOCK_RPI_PICO_CLOCK_H_ */
