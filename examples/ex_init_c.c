/*
 Licence: CC0/Public Domain http://creativecommons.org/publicdomain/zero/1.0/
 Author: Adrian Rossiter <adrian@antiprism.com>

 libu8g2arm example showing how to initialise a display U8g2-style using C
*/

#include <libu8g2arm/u8g2.h>
#include <libu8g2arm/u8g2arm.h>

#include <stdio.h>

u8g2_t u8g2;

int main()
{
  u8x8_t *p_u8x8 = u8g2_GetU8x8(&u8g2);

  // U8g2 Setup for example display with HW I2C
  u8g2_Setup_sh1106_i2c_128x64_noname_f(&u8g2, U8G2_R0,
                                        u8x8_byte_arm_linux_hw_i2c,
                                        u8x8_arm_linux_gpio_and_delay);
  u8x8_SetPin(p_u8x8, U8X8_PIN_I2C_CLOCK, U8X8_PIN_NONE);
  u8x8_SetPin(p_u8x8, U8X8_PIN_I2C_DATA, U8X8_PIN_NONE);
  u8x8_SetPin(p_u8x8, U8X8_PIN_RESET, U8X8_PIN_NONE);

  // U8g2arm needs an extra call for hardware I2C to set the bus number
  // (and for hardware SPI to set the bus number and CS number)
  if (!u8g2arm_arm_init_hw_i2c(p_u8x8, /* bus_number = */ 1)) {
    fprintf(stderr, "could not initialise I2C device");
    exit(1);
  }

  // U8g2 begin
  u8g2_InitDisplay(&u8g2);
  u8g2_ClearDisplay(&u8g2);
  u8g2_SetPowerSave(&u8g2, 0);

  // Draw something to the display
  u8g2_ClearBuffer(&u8g2);                    // clear the internal memory
  u8g2_SetFont(&u8g2, u8g2_font_ncenB08_tr);  // choose a suitable font
  u8g2_DrawStr(&u8g2, 0, 10, "Hello World!"); // write string to internal mem
  u8g2_SendBuffer(&u8g2); // transfer internal memory to the display

  // Leave it on the screen for a time
  sleep(5);

  // Clear the screen
  u8g2_ClearBuffer(&u8g2); // clear the internal memory
  u8g2_SendBuffer(&u8g2);  // transfer internal memory to the display

  return 0;
}
