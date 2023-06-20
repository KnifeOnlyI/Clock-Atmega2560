#include "header/time.hpp"
#include "header/display.hpp"

const int resetButtonPin = 13;
const int timeButtonPin = 12;

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

    displayBegin();
    displayPrepare();
}

void draw()
{
    String mode = adjustMode > 0 ? "R" : "T";
    String unitAdjustment = "0";

    if (adjustMode == 1)
    {
        unitAdjustment = "H";
    }
    else if (adjustMode == 2)
    {
        unitAdjustment = "M";
    }
    else if (adjustMode == 3)
    {
        unitAdjustment = "S";
    }

    getDisplay().drawStr(0, 0, getTimeString().c_str());
    getDisplay().drawStr(0, 8, String(mode + String(" - ") + unitAdjustment).c_str());

    getDisplay().sendBuffer();
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

    delay(10);
}