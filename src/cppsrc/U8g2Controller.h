/*
  Copyright (c) 2021, Adrian Rossiter <adrian@antiprism.com>

  Antiprism - http://www.antiprism.com

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

#ifndef U8G2CONTROLLER_H
#define U8G2CONTROLLER_H
#include "../csrc/u8g2_controllers.h"
#include "U8g2lib.h"

#include <map>
#include <set>
#include <string>
#include <vector>

/// Class to manage settings for a U8G2 controller
class ControllerSetup {
public:
  // Setup Values
  enum {
    VAL_ROTATION,    ///< rotation (0: 0deg, 1: 90deg, 2: 180deg, 3: 270deg)
    VAL_CLOCK,       ///< clock pin (GPIO number)
    VAL_DATA,        ///< data pin (GPIO number)
    VAL_CS,          ///< CS pin (GPIO number)
    VAL_DC,          ///< DC pin (GPIO number)
    VAL_RESET,       ///< eset pin (GPIO number)
    VAL_D0,          ///< D0 pin (GPIO number)
    VAL_D1,          ///< D1 pin (GPIO number)
    VAL_D2,          ///< D2 pin (GPIO number)
    VAL_D3,          ///< D3 pin (GPIO number)
    VAL_D4,          ///< D4 pin (GPIO number)
    VAL_D5,          ///< D5 pin (GPIO number)
    VAL_D6,          ///< D6 pin (GPIO number)
    VAL_D7,          ///< D7 pin (GPIO number)
    VAL_WR,          ///< WR pin (GPIO number)
    VAL_I2C_ADDRESS, ///< I2C address (hex: from 01 to fe)
    VAL_BUS_NUMBER,  ///< bus number
    VAL_CS_NUMBER,   ///< CS number
    VAL_LAST         ///< marker for last entry
  };

  // Name and description of a setup value
  struct ValueDetails {
    std::string id;
    std::string desc;
  };

  /// Get the setup value ID number for a value name
  /**\param value_name the value name
   * \return the ID number, or -1 if the name was invalid */
  static int get_value_id(const std::string &value_name);

  /// Get the value details for a setup value ID number
  /**\param value_id the value type ID number
   * \return the value type details, or \c nullptr if the ID was invalid */
  static const ValueDetails *get_value_details(int value_id);

  /// Communication protocol types
  enum {
    COM_4W_SW_SPI, ///< 4 wire software SPI
    COM_4W_HW_SPI, ///< 4 wire hardware SPI
    COM_3W_SW_SPI, ///< 3 wire software SPI
    COM_SW_I2C,    ///< software I2C
    COM_HW_I2C,    ///< hardware I2C
    COM_8080,      ///< 8080
    COM_LAST       ///< marker for last entry
  };

  /// Communication protocol details
  struct ComDetails {
    std::string name;               ///< Protocol name
    std::string desc;               ///< Protocol description
    std::set<int> values_required;  ///< required value types (ID numbers)
    std::set<int> values_optional;  ///< optional value types (ID numbers)
  };

  /// Get the communication protol ID number for a protocol name
  /**\param com_name the communication protocol name
   * \return the ID number, or -1 if the name was invalid */
  static int get_com_id(const std::string &com_name);

  /// Get the protocol details for a communication protol ID number
  /**\param com_id the communication protocol type ID number
   * \return the value type details, or \c nullptr if the ID was invalid */
  static const ComDetails *get_com_details(int com_id);

  /// Get the list of controllers
  /**\return list of controllers - controller : model : protocol ->
             check_result */
  static std::map<std::string,
                  std::map<std::string, std::map<std::string, size_t>>>
  get_controllers();

  /// Set the controller
  /**
   *    CONTROLLER SETUP DETAILS
   *    PROTOCOL KEY
   *    I2C                    - I2C (alias of HW_I2C), HW_I2C, SW_I2C
   *    SPI (4 wire SPI)       - SPI (alias of 4W_HW_SPI), 4W_HW_SPI, 4W_SW_SPI
   *    3W_SW_SPI (3 wire SPI) - 3W_SW_SPI
   *    8080                   - 8080
   *
   *    CONTROLLER     MODEL               PROTOCOLS
   *    ----------     -----               ---------
   *    
   *    HX1230         96X68               SPI,3W_SW_SPI
   *    
   *    IL3820         296X128             SPI,3W_SW_SPI
   *                   V2_296X128          SPI,3W_SW_SPI
   *    
   *    IST3020        ERC19264            SPI,8080
   *    
   *    IST7920        128X128             SPI,8080
   *    
   *    LD7032         60X32               I2C,SPI
   *                   60X32_ALT           I2C,SPI
   *    
   *    LS013B7DH03    128X128             SPI
   *    
   *    LS013B7DH05    144X168             SPI
   *    
   *    LS027B7DH01    400X240             SPI
   *                   M0_400X240          SPI
   *    
   *    MAX7219        32X8                SPI
   *                   64X8                SPI
   *                   8X8                 SPI
   *    
   *    NT7534         TG12864R            SPI,8080
   *    
   *    PCD8544        84X48               SPI,3W_SW_SPI
   *    
   *    PCF8812        96X65               SPI,3W_SW_SPI
   *    
   *    RA8835         320X240             8080
   *                   NHD_240X128         8080
   *    
   *    S1D15721       240X64              SPI,8080
   *    
   *    S1D15E06       160100              SPI,8080
   *    
   *    SED1330        240X128             8080
   *    
   *    SH1106         128X32_VISIONOX     I2C,SPI,3W_SW_SPI,8080
   *                   128X64_NONAME       I2C,SPI,3W_SW_SPI,8080
   *                   128X64_VCOMH0       I2C,SPI,3W_SW_SPI,8080
   *                   128X64_WINSTAR      I2C,SPI,3W_SW_SPI,8080
   *                   64X32               I2C,SPI,3W_SW_SPI,8080
   *                   72X40_WISE          I2C,SPI,3W_SW_SPI,8080
   *    
   *    SH1107         128X128             I2C,SPI,3W_SW_SPI,8080
   *                   64X128              I2C,SPI,3W_SW_SPI,8080
   *                   PIMORONI_128X128    I2C,SPI,3W_SW_SPI,8080
   *                   SEEED_128X128       I2C,SPI,3W_SW_SPI,8080
   *                   SEEED_96X96         I2C,SPI,3W_SW_SPI,8080
   *    
   *    SH1108         160X160             I2C,SPI,3W_SW_SPI,8080
   *    
   *    SH1122         256X64              I2C,SPI,3W_SW_SPI,8080
   *    
   *    SSD0323        OS128064            I2C,SPI,3W_SW_SPI,8080
   *    
   *    SSD1305        128X32_ADAFRUIT     I2C,SPI,8080
   *                   128X32_NONAME       I2C,SPI,8080
   *                   128X64_ADAFRUIT     I2C,SPI,8080
   *                   128X64_RAYSTAR      I2C,SPI,8080
   *    
   *    SSD1306        128X32_UNIVISION    I2C,SPI,3W_SW_SPI,8080
   *                   128X32_WINSTAR      I2C,SPI,3W_SW_SPI,8080
   *                   128X64_ALT0         I2C,SPI,3W_SW_SPI,8080
   *                   128X64_NONAME       I2C,SPI,3W_SW_SPI,8080
   *                   128X64_VCOMH0       I2C,SPI,3W_SW_SPI,8080
   *                   2040X16             SPI,3W_SW_SPI,8080
   *                   48X64_WINSTAR       I2C,SPI,3W_SW_SPI,8080
   *                   64X32_1F            I2C,SPI,3W_SW_SPI,8080
   *                   64X32_NONAME        I2C,SPI,3W_SW_SPI,8080
   *                   64X48_ER            I2C,SPI,3W_SW_SPI,8080
   *                   72X40_ER            I2C,SPI,3W_SW_SPI,8080
   *                   96X16_ER            I2C,SPI,3W_SW_SPI,8080
   *    
   *    SSD1309        128X64_NONAME0      I2C,SPI,8080
   *                   128X64_NONAME2      I2C,SPI,8080
   *    
   *    SSD1316        128X32              I2C,SPI,8080
   *    
   *    SSD1317        96X96               I2C,SPI,8080
   *    
   *    SSD1318        128X96              I2C,SPI,3W_SW_SPI,8080
   *                   128X96_XCP          I2C,SPI,3W_SW_SPI,8080
   *    
   *    SSD1320        160X132             SPI,3W_SW_SPI,8080
   *                   160X32              SPI,3W_SW_SPI,8080
   *    
   *    SSD1322        NHD_128X64          SPI,3W_SW_SPI,8080
   *                   NHD_256X64          SPI,3W_SW_SPI,8080
   *    
   *    SSD1325        NHD_128X64          I2C,SPI,3W_SW_SPI,8080
   *    
   *    SSD1326        ER_256X32           I2C,SPI,3W_SW_SPI,8080
   *    
   *    SSD1327        EA_W128128          I2C,SPI,3W_SW_SPI,8080
   *                   MIDAS_128X128       I2C,SPI,3W_SW_SPI,8080
   *                   SEEED_96X96         I2C,SPI,3W_SW_SPI,8080
   *                   VISIONOX_128X96     I2C,SPI,3W_SW_SPI,8080
   *                   WS_128X128          I2C,SPI,3W_SW_SPI,8080
   *                   WS_96X64            I2C,SPI,3W_SW_SPI,8080
   *    
   *    SSD1329        128X96_NONAME       SPI,8080
   *                   96X96_NONAME        SPI,8080
   *    
   *    SSD1606        172X72              SPI,3W_SW_SPI
   *    
   *    SSD1607        200X200             SPI,3W_SW_SPI
   *                   GD_200X200          SPI,3W_SW_SPI
   *                   WS_200X200          SPI,3W_SW_SPI
   *    
   *    ST7511         AVD_320X240         SPI,3W_SW_SPI,8080
   *    
   *    ST75256        JLX172104           I2C,SPI,3W_SW_SPI,8080
   *                   JLX19296            I2C,SPI,3W_SW_SPI,8080
   *                   JLX240160           I2C,SPI,3W_SW_SPI,8080
   *                   JLX256128           I2C,SPI,3W_SW_SPI,8080
   *                   JLX256160           I2C,SPI,3W_SW_SPI,8080
   *                   JLX256160M          I2C,SPI,3W_SW_SPI,8080
   *                   JLX256160_ALT       I2C,SPI,3W_SW_SPI,8080
   *                   JLX25664            I2C,SPI,3W_SW_SPI,8080
   *                   WO256X128           I2C,SPI,3W_SW_SPI,8080
   *    
   *    ST7528         ERC16064            I2C,SPI,8080
   *                   NHD_C160100         I2C,SPI,8080
   *    
   *    ST75320        JLX320240           I2C,SPI,3W_SW_SPI,8080
   *    
   *    ST7565         64128N              SPI,3W_SW_SPI,8080
   *                   EA_DOGM128          SPI,3W_SW_SPI,8080
   *                   EA_DOGM132          SPI,3W_SW_SPI,8080
   *                   ERC12864            SPI,3W_SW_SPI,8080
   *                   ERC12864_ALT        SPI,3W_SW_SPI,8080
   *                   JLX12864            SPI,3W_SW_SPI,8080
   *                   KS0713              SPI,3W_SW_SPI,8080
   *                   LM6059              SPI,3W_SW_SPI,8080
   *                   LM6063              SPI,3W_SW_SPI,8080
   *                   LX12864             SPI,3W_SW_SPI,8080
   *                   NHD_C12832          SPI,3W_SW_SPI,8080
   *                   NHD_C12864          SPI,3W_SW_SPI,8080
   *                   ZOLEN_128X64        SPI,3W_SW_SPI,8080
   *    
   *    ST7567         64X32               I2C,SPI,8080
   *                   ENH_DG128064        SPI,8080
   *                   ENH_DG128064I       SPI,8080
   *                   HEM6432             I2C,SPI,8080
   *                   JLX12864            SPI,8080
   *                   OS12864             SPI,8080
   *                   PI_132X64           SPI,8080
   *    
   *    ST7571         128X128             I2C,SPI,8080
   *    
   *    ST7586S        ERC240160           SPI,3W_SW_SPI,8080
   *                   S028HN118A          SPI
   *                   YMC240160           SPI,3W_SW_SPI,8080
   *    
   *    ST7588         JLX12864            I2C,SPI,3W_SW_SPI,8080
   *    
   *    ST7920         128X64              8080
   *                   192X32              8080
   *    
   *    T6963          128X64              8080
   *                   128X64_ALT          8080
   *                   160X80              8080
   *                   240X128             8080
   *                   240X64              8080
   *                   256X64              8080
   *    
   *    UC1601         128X32              I2C,SPI,3W_SW_SPI,8080
   *                   128X64              I2C,SPI,3W_SW_SPI,8080
   *    
   *    UC1604         JLX19264            I2C,SPI,3W_SW_SPI,8080
   *    
   *    UC1608         240X128             I2C,SPI,3W_SW_SPI,8080
   *                   DEM240064           I2C,SPI,3W_SW_SPI,8080
   *                   ERC240120           I2C,SPI,3W_SW_SPI,8080
   *                   ERC24064            I2C,SPI,3W_SW_SPI,8080
   *    
   *    UC1610         EA_DOGXL160         I2C,SPI,3W_SW_SPI,8080
   *    
   *    UC1611         CG160160            I2C,SPI,3W_SW_SPI,8080
   *                   EA_DOGM240          I2C,SPI,3W_SW_SPI,8080
   *                   EA_DOGXL240         I2C,SPI,3W_SW_SPI,8080
   *                   EW50850             I2C,SPI,3W_SW_SPI,8080
   *                   IDS4073             I2C,SPI,3W_SW_SPI,8080
   *    
   *    UC1617         JLX128128           I2C,SPI,3W_SW_SPI
   *    
   *    UC1638         160X128             SPI,3W_SW_SPI,8080
   *                   192X96              I2C,SPI,3W_SW_SPI,8080
   *    
   *    UC1701         EA_DOGS102          SPI,3W_SW_SPI,8080
   *                   MINI12864           SPI,3W_SW_SPI,8080
   *    
   *
   *    PROTOCOL OPTIONS
   *
   *    I2C is an alias for HW_I2C, SPI is an alias for 4W_HW_SPI
   *    HW_I2C - hardware I2C
   *      required:
   *      optional: rotation,clock,data,reset,i2c_address,bus_number
   *    SW_I2C - software I2C
   *      required: clock,data
   *      optional: rotation,reset,i2c_address
   *    4W_HW_SPI - 4 wire hardware SPI
   *      required: dc
   *      optional: rotation,reset,bus_number,cs_number
   *    4W_SW_SPI - 4 wire software SPI
   *      required: clock,data,cs,dc
   *      optional: rotation,reset
   *    3W_SW_SPI - 3 wire software SPI
   *      required: clock,data,cs
   *      optional: rotation,reset
   *    8080 - 8080
   *      required: clock,data,d0,d1,d2,d3,d4,d5,d6,d7,wr
   *      optional: rotation,reset
   *
   * \param type controller type
   * \param model model name
   * \param com communication protocol
   * \param errmsg to return any error message
   * \return \c true is the controller was set, otherwise \c false and
   *        errmsg contains the error message */
  bool set_controller(const std::string &type, const std::string &model,
                      const std::string &com, std::string &errmsg);

  /// Set a setup value
  /**\param val_type the ID number of the value type
   * \param val the value to set
   * \param errmsg to return any error message
   * \return \c true is the value was set, otherwise \c false and \c errmsg
   *        contains error message */
  bool set_value(int val_type, uint8_t val, std::string &errmsg);

  /// Set a setup value from a string
  /**\param setting a string in the form "value_type_name=value"
   *    value_type_name   value
   *    rotation          rotation degrees (0: 0, 1: 90, 2: 180, 3: 270)
   *    clock             clock pin (GPIO number)
   *    data              data pin (GPIO number)
   *    cs                CS pin (GPIO number)
   *    dc                DC pin (GPIO number)
   *    reset             reset pin (GPIO number)
   *    d0                D0 pin (GPIO number)
   *    d1                D1 pin (GPIO number)
   *    d2                D2 pin (GPIO number)
   *    d3                D3 pin (GPIO number)
   *    d4                D4 pin (GPIO number)
   *    d5                D5 pin (GPIO number)
   *    d6                D6 pin (GPIO number)
   *    d7                D7 pin (GPIO number)
   *    wr                WR pin (GPIO number)
   *    i2c_address       I2C address (hex 01-fe)
   *    bus_number        bus number
   *    cs_number         CS number
   * \param errmsg to return any error message
   * \param separator the separator character
   * \return \c true is the value was set, otherwise \c false and \c errmsg
   *        contains error message */
  bool set_value(const std::string &setting, std::string &errmsg,
                 char separator = '=');

  /// Get the value for a setup value type
  /**\param val_type the ID number of the value type
   * \return the value */
  uint8_t get_value(int val_type);

  /// Check if setup values are valid for a communication protocol
  /**\param com communication protocol to check for
   * \param errmsg to return any error message
   * \return \c true if the settings are valid, otherwise \c false and
   *        errmsg contains the error message */
  bool check_values(const std::string &com_name, std::string &errmsg);

  /// Get a string representation of the current settings
  /**\return the string representation*/
  std::string to_str();

  /// Initialise U8G2 with the current settings
  /**\param u8g2 the U8G2 object to initialize
   * \param errmsg to return any error message
   * \return \c true if the object was initialized, otherwise \c false and
   *        errmsg contains the error message */
  bool init(U8G2 *u8g2, std::string &errmsg);

private:
  /// Setup values (indexed by setup value ID number)
  std::vector<uint8_t> values = std::vector<uint8_t>(VAL_LAST, U8X8_PIN_NONE);
  const controller_details_t *controller = nullptr;
};

#endif // U8G2CONTROLLER_H

