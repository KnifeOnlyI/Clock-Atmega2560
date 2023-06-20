#ifndef TEST_BUTTON_ARDUINO_DISPLAY_HPP
#define TEST_BUTTON_ARDUINO_DISPLAY_HPP

#include "U8g2lib.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C getDisplay();

void displayBegin();

void displayPrepare();

#endif //TEST_BUTTON_ARDUINO_DISPLAY_HPP
