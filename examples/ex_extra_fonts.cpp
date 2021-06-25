/*
 Licence: CC0/Public Domain http://creativecommons.org/publicdomain/zero/1.0/
 Author: Adrian Rossiter <adrian@antiprism.com>

 libu8g2arm example showing how to initialise a display U8g2-style using C++
*/

#include <libu8g2arm/U8g2lib.h>
#include <libu8g2arm/u8g2arm.h>

// The following header is needed for using GPL fonts
#include <libu8g2arm/u8g2_fonts_gplcopyleft.h>

#include <cstdio>

// U8g2 compile time setup for example display with HW I2C
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

int main()
{
  // U8g2arm needs an extra call for hardware I2C to set the bus number
  // (and for hardware SPI to set the bus number and CS number)
  if (!u8g2arm_arm_init_hw_i2c(u8g2.getU8x8(), /* bus_number = */ 1)) {
    fprintf(stderr, "could not initialise I2C device");
    exit(1);
  }

  // U8g2 begin
  u8g2.begin();

  // Draw something to the display
  u8g2.clearBuffer();                  // clear the internal memory

  // Use a GPL font for text
  // must use #include <libu8g2arm/u8g2_fonts_gplcopyleft.h>
  // and link to libu8g2fonts_gplcopyleft
  u8g2.setFont(u8g2_font_unifont_t_extended);  // choose a suitable font

  u8g2.drawStr(0, 10, "Hello World!"); // write something to the internal memory
  u8g2.sendBuffer(); // transfer internal memory to the display

  // Leave it on the screen for a time
  sleep(5);

  // Clear the screen
  u8g2.clearBuffer(); // clear the internal memory
  u8g2.sendBuffer();  // transfer internal memory to the display

  return 0;
}

