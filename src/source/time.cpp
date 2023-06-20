#include "header/time.hpp"

unsigned long elapsedTime = 0;
unsigned long milliseconds = 0;

int hours = 0;
int minutes = 0;
int seconds = 0;

String getTimeElementString(int value)
{
    return value < 10
           ? "0" + String(value)
           : String(value);
}

String getTimeString()
{
    String hoursStr = getTimeElementString(hours);
    String minutesStr = getTimeElementString(minutes);
    String secondsStr = getTimeElementString(seconds);

    return hoursStr + ":" + minutesStr + ":" + secondsStr;
}

void updateTime(boolean pause)
{
    if (pause)
    {
        return;
    }

    milliseconds += elapsedTime;

    if (milliseconds < 1000)
    {
        return;
    }

    milliseconds -= 1000;
    seconds++;

    if (seconds < 60)
    {
        return;
    }

    seconds = 0;
    minutes++;

    if (minutes < 60)
    {
        return;
    }

    minutes = 0;
    hours++;

    if (hours < 24)
    {
        return;
    }

    hours = 0;
}