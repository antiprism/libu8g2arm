/*
 Licence: CC0/Public Domain http://creativecommons.org/publicdomain/zero/1.0/
 Author: Adrian Rossiter <adrian@antiprism.com>

 libu8g2arm example showing how to initialise a display specified at runtime
 with C++
*/

#include "u8x8_d_sdl.h"

#include <libu8g2arm/U8g2Controller.h>
#include <libu8g2arm/U8g2lib.h>

#include <string>
#include <vector>
#include <unistd.h>

using std::string;
using std::vector;

U8G2 *p_u8g2;

vector<string> split(const string &text,
                               const string &delims)
{
  vector<string> tokens;
  std::size_t start = text.find_first_not_of(delims), end = 0;

  while ((end = text.find_first_of(delims, start)) != string::npos) {
    tokens.push_back(text.substr(start, end - start));
    start = text.find_first_not_of(delims, end);
  }
  if (start != string::npos)
    tokens.push_back(text.substr(start));

  return tokens;
}

bool read_int(const char *str, int *i)
{
  char buff;
  return (sscanf(str, " %d %c", i, &buff) == 1 && *i != INT_MAX);
}

bool init_display(U8G2 **pp_u8g2, string oled, string &errmsg)
{
  auto settings = split(oled, ",");
  if(settings.size() == 0) {
    errmsg = "must specify a controller";
    return false;
  }
  if(settings[0] == "SDL") {
    if (settings.size() > 2) {
      errmsg = "controller SDL: extra parameters specified (use SDL,WXH)";
    return false;
    }
    string dim_string = settings.size() == 1 ? "128X64" : settings[1];
    auto dims = split(dim_string, "X");
    if(dims.size() != 2) {
      errmsg = "controller SDL: dimensions is not in form WxH";
      return false;
    }
    int width;
    if(!read_int(dims[0].c_str(), &width)) {
      errmsg = "controller SDL: width dimension is not a number";
    return false;
    }
    int height;
    if(!read_int(dims[1].c_str(), &height)) {
      errmsg = "controller SDL: height dimension is not a number";
      return false;
    }

    *pp_u8g2 = new U8G2;
    if (u8g2_SetupBuffer_SDL((*pp_u8g2)->getU8g2(), U8G2_R0, width, height)) {
      u8x8_InitDisplay((*pp_u8g2)->getU8x8());
      u8x8_SetPowerSave((*pp_u8g2)->getU8x8(), 0);
    }
    else {
      delete *pp_u8g2;
      *pp_u8g2 =  nullptr;
      errmsg = "controller SDL: SDL support was not included";
      return false;
    }
  }
  else {
    if (settings.size() < 3) {
      settings.resize(3, string("not specified"));
      //  fprintf(stderr, "error: did find three controller parameters
      //  CONTROLLER_TYPE,DISPLAY_NAME,COM_TYPE\n"); exit(1);
    }
    ControllerSetup setup;

    string errmsg;
    if (!setup.set_controller(settings[0], settings[1], settings[2], errmsg))
      return false;

    for (size_t i = 3; i < settings.size(); i++) {
      if(!setup.set_value(settings[i], errmsg))
        return false;
    }

    *pp_u8g2 = new U8G2;
    if(!setup.init(*pp_u8g2, errmsg)) {
      delete *pp_u8g2;
      *pp_u8g2 =  nullptr;
      errmsg = "controller type '" + settings[0] + "', name '" + settings[1] +
               "', protocol '" + settings[2] + "': " + errmsg;
      return false;
    }
  }

  return true;
}


int main(int argc, char *argv[])
{
  if(argc != 2) {
    fprintf(stderr, "error: must specify one controller argument");
    exit(1);
  }

  string errmsg;
  if(!init_display(&p_u8g2, argv[1], errmsg)) {
    fprintf(stderr, "error: controller: %s", errmsg.c_str());
    exit(1);
  }

  auto u8g2 = *p_u8g2;

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

