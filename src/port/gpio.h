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

#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Direction
#define GPIO_IN                 (0)
#define GPIO_OUT                (1)

// Value
#define GPIO_LOW                (0)
#define GPIO_HIGH               (1)

//nanopi
#define GPIO_PIN(x)             (x)

int exportGPIOPin(int pin);
int unexportGPIOPin(int pin);

// GPIO_IN or GPIO_OUT
int setGPIODirection(int pin, int direction);
int getGPIODirection(int pin);

// GPIO_LOW or GPIO_HIGH
int setGPIOValue(int pin, int value);
int getGPIOValue(int pin);

#endif
