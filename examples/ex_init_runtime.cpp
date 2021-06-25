/*
 Licence: CC0/Public Domain http://creativecommons.org/publicdomain/zero/1.0/
 Author: Adrian Rossiter <adrian@antiprism.com>

 libu8g2arm example showing how to initialise a display specified at runtime
 with C++
*/

#include <libu8g2arm/U8g2Controller.h>
#include <libu8g2arm/U8g2lib.h>

#include <string>
#include <unistd.h>

U8G2 u8g2;

int main()
{
  std::string display_type = "SH1106";
  std::string display_model = "128X64_NONAME";
  std::string com_type = "HW_I2C";
  std::string errmsg;

  // U8g2arm runtime setup for example display with HW I2C
  ControllerSetup setup;
  if (!setup.set_controller(display_type, display_model, com_type, errmsg)) {
    fprintf(stderr, "error: initializing display: %s\n", errmsg.c_str());
    exit(1);
  }

  // Set any parameters
  if (!setup.set_value("bus_number=1", errmsg)) { // bus to default as example
    fprintf(stderr, "error: initializing display: %s\n", errmsg.c_str());
    exit(1);
  }

  // Initialize the display
  if (!setup.init(&u8g2, errmsg)) {
    fprintf(stderr, "error: initializing display: %s\n", errmsg.c_str());
    exit(1);
  }

  // U8g2 begin
  u8g2.begin();

  // Draw something to the display
  u8g2.clearBuffer();                  // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);  // choose a suitable font
  u8g2.drawStr(0, 10, "Hello World!"); // write something to the internal memory
  u8g2.sendBuffer(); // transfer internal memory to the display

  // Leave it on the screen for a time
  sleep(5);

  // Clear the screen
  u8g2.clearBuffer(); // clear the internal memory
  u8g2.sendBuffer();  // transfer internal memory to the display

  return 0;
}

