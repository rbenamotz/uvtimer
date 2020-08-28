#include <Arduino.h>
#include "common.h"
#include "uvtimer.h"

void setupUvTimer()
{
    pinMode(PIN_RELAY, OUTPUT);
    digitalWrite(PIN_RELAY, false);
}

void loopUvTimer()
{
    static unsigned long lastDisplayUpdate = 0;
    if (state != STATE_RUNNING)
    {
        return;
    }
    if (millis() >= timerEndTime)
    {
        Serial.print(millis());
        Serial.print(" - ");
        Serial.println(timerEndTime);
        stopTimer();
    }
    unsigned long l = millis() - lastDisplayUpdate;
    if (l > 10)
    {
        isDisplayNeedsUpdate = true;
        lastDisplayUpdate = millis();
    }
}

void startTimer()
{
    timerStartTime = millis();
    timerEndTime = timerStartTime + encPosition * 1000 * 60;
    digitalWrite(PIN_RELAY, true);
    state = STATE_RUNNING;
    Serial.println("Timer started");
}

void stopTimer()
{
    digitalWrite(PIN_RELAY, false);
    state = STATE_SETTING;
    Serial.print("Timer stopped.");
    isDisplayNeedsUpdate = true;
}