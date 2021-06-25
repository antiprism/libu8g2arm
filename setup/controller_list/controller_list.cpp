/*
 * Author: Adrian Rossiter <adrian@antiprism.com>
 * Licence: CC0/Public Domain http://creativecommons.org/publicdomain/zero/1.0/
 */

#include <string>
#include <map>
#include <set>

using std::string;

#include "out.txt"

int main()
{

  std::map<string, std::map<string, std::map<string, int>>> setup;
  for (size_t i = 0; controllers[i][0][0] != '\0'; i++)
    setup[controllers[i][0]][controllers[i][1]][controllers[i][2]] = 0;

  const char *pre = "   *    ";
  //printf("%s%-15s%-20s%s\n", pre, "CONTROLLER", "MODEL", "PROTOCOLS");
  //printf("%s%-15s%-20s%s\n", pre, "----------", "-----", "---------");

  for (auto &kp0 : setup) {
    bool first_model = true;
    printf("%s\n", pre);
    for (auto &kp1 : kp0.second) {
      std::set<string> protocols;
      for (auto &kp2 : kp1.second) {
        auto com = kp2.first;
        if (com == "I2C" || com == "HW_I2C" || com == "SW_I2C")
          protocols.insert("aI2C");
        else if (com == "SPI" || com == "4W_HW_SPI" || com == "4W_SW_SPI")
          protocols.insert("bSPI");
        else
          protocols.insert("c" + com); // 3W_SW_SPI, 8080
      }
      string protos;
      for (auto proto : protocols)
        protos += proto.substr(1) + ",";
      if (!protos.empty())
        protos.pop_back();

      printf("%s%-15s%-20s%s\n", pre, (first_model) ? kp0.first.c_str() : "",
             kp1.first.c_str(), protos.c_str());
      first_model = false;
    }
  }

  printf("%s\n", pre);

  return 0;
}

