/*
   Copyright (c) 2019, Wu Han <wuhanstudio@hust.edu.cn>
                       http://wuhanstudio.cc

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

      The above copyright notice and this permission notice shall be included
      in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/

#ifndef U8G2LIB_H
#define U8G2LIB_H

#ifdef __cplusplus
extern "C" {
#endif


#include "u8g2.h"
#include "gpio.h"
#include "i2c.h"
#include "spi.h"

// Initialize the U8X8 user pointer to hold hardware device details
// when using hardware I2C or SPI drivers.
// The details are held in dynamic memory pointed to by the U8X8 user
// pointer (u8x8_GetUserPtr(u8x8)), and can be freed when all access to
// the display has finished

// Initialize hardware SPI driver
int u8g2arm_arm_init_hw_spi(u8x8_t *u8x8, int bus_number, int cs_number,
    int speed_mhz);

// Initialize hardware I2C driver
int u8g2arm_arm_init_hw_i2c(u8x8_t *u8x8, int bus_number);


uint8_t u8x8_arm_linux_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_byte_arm_linux_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_byte_arm_linux_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);

#ifdef __cplusplus
}
#endif

#endif
