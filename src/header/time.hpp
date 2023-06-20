#ifndef TEST_BUTTON_ARDUINO_TIME_HPP
#define TEST_BUTTON_ARDUINO_TIME_HPP

#include "Arduino.h"

extern unsigned long elapsedTime;
extern unsigned long milliseconds;

extern int hours;
extern int minutes;
extern int seconds;

String getTimeElementString(int value);

String getTimeString();

void updateTime(boolean pause);

#endif //TEST_BUTTON_ARDUINO_TIME_HPP
