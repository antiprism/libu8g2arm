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
    VAL_SPI_MHZ,     ///< HW SPI speed in MHz
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
   *    <<<CONTROLLER_LIST>>>
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
   *      optional: rotation,reset,bus_number,cs_number,spi_mhz
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

