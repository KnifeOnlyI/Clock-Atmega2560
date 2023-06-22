#include <SevSeg.h>

#include "header/time.hpp"

SevSeg sevSegSeconds;
SevSeg sevSegMinutes;
SevSeg sevSegHours;

const int resetButtonPin = A0;
const int timeButtonPin = A1;

bool resetButtonPressed = false;
bool resetButtonReleased = true;
bool resetButtonJustPressed = false;

bool timeButtonPressed = false;
bool timeButtonReleased = true;
bool timeButtonJustPressed = false;

int adjustMode = 0;

void setup()
{
    pinMode(resetButtonPin, INPUT_PULLUP);
    pinMode(timeButtonPin, INPUT_PULLUP);

    bool resistorsOnSegments = true;
    byte hardwareConfig = COMMON_ANODE;

    byte secondsNumDigits = 2;
    byte secondsDigitPins[] = {22, 23};
    byte secondsSegmentPins[] = {28, 29, 30, 31, 32, 33, 34, 35};

    byte minutesNumDigits = 2;
    byte minutesDigitPins[] = {24, 25};
    byte minutesSegmentPins[] = {36, 37, 38, 39, 40, 41, 42, 43};

    byte hoursNumDigits = 2;
    byte hoursDigitPins[] = {26, 27};
    byte hoursSegmentPins[] = {44, 45, 46, 47, 48, 49, 50, 51};

    sevSegSeconds.begin(
        hardwareConfig,
        secondsNumDigits,
        secondsDigitPins,
        secondsSegmentPins,
        resistorsOnSegments
    );

    sevSegMinutes.begin(
        hardwareConfig,
        minutesNumDigits,
        minutesDigitPins,
        minutesSegmentPins,
        resistorsOnSegments
    );

    sevSegHours.begin(
        hardwareConfig,
        hoursNumDigits,
        hoursDigitPins,
        hoursSegmentPins,
        resistorsOnSegments
    );

    sevSegSeconds.setBrightness(100);
    sevSegMinutes.setBrightness(100);
    sevSegHours.setBrightness(100);
}

void draw()
{
    sevSegSeconds.setChars((getTimeElementString(seconds)).c_str());
    sevSegMinutes.setChars(getTimeElementString(minutes).c_str());
    sevSegHours.setChars(getTimeElementString(hours).c_str());

    if (adjustMode == 1)
    {
        sevSegSeconds.blank();
        sevSegMinutes.blank();
    }
    else if (adjustMode == 2)
    {
        sevSegHours.blank();
        sevSegSeconds.blank();
    }
    else if (adjustMode == 3)
    {
        sevSegHours.blank();
        sevSegMinutes.blank();
    }

    sevSegSeconds.refreshDisplay();
    sevSegMinutes.refreshDisplay();
    sevSegHours.refreshDisplay();
}

void loop()
{
    updateTime(adjustMode > 0);
    unsigned long beginTime = millis();

    int resetDigitalValue = digitalRead(resetButtonPin);
    int timeDigitalValue = digitalRead(timeButtonPin);

    resetButtonPressed = resetDigitalValue == LOW;
    resetButtonJustPressed = resetButtonPressed && resetButtonReleased;
    resetButtonReleased = resetDigitalValue == HIGH;;

    if (resetButtonJustPressed && adjustMode == 0)
    {
        adjustMode = 1;
    }
    else if (resetButtonJustPressed && adjustMode > 0)
    {
        if (adjustMode == 1)
        {
            adjustMode = 2;
        }
        else if (adjustMode == 2)
        {
            adjustMode = 3;
        }
        else
        {
            adjustMode = 0;
        }
    }

    timeButtonPressed = timeDigitalValue == LOW;
    timeButtonJustPressed = timeButtonPressed && timeButtonReleased;
    timeButtonReleased = timeDigitalValue == HIGH;;

    if (timeButtonJustPressed && adjustMode > 0)
    {
        if (adjustMode == 1)
        {
            hours++;

            if (hours > 23)
            {
                hours = 0;
            }
        }
        else if (adjustMode == 2)
        {
            minutes++;

            if (minutes > 59)
            {
                minutes = 0;
            }
        }
        else if (adjustMode == 3)
        {
            seconds++;

            if (seconds > 59)
            {
                seconds = 0;
            }
        }

    }

    draw();

    elapsedTime = millis() - beginTime;
}