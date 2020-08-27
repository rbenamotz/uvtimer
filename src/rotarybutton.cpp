#include <Arduino.h>
#include "uvtimer.h"
#include "common.h"
#include "Encoder.h"
Encoder myEnc(PIN_ENC_1, PIN_ENC_2);

void loopButton()
{
    static unsigned long lastButtonDownEvent = 0;
    static bool lastRead = false;
    bool b = !digitalRead(PIN_BTN);
    if (!lastRead && b)
    {
        unsigned long l = millis() - lastButtonDownEvent;
        if (l < 500)
        {
            return;
        }
        if (state == STATE_SETTING)
        {
            startTimer();
        }
        else if (state == STATE_RUNNING)
        {
            stopTimer();
        }
        lastButtonDownEvent = millis();
    }
    lastRead = b;
}

void loopEncoder()
{
    long newPosition = myEnc.read() / 4;
    if (state != STATE_SETTING)
    {
        myEnc.write(encPosition * 4);
        return;
    }
    if (newPosition < 0)
    {
        myEnc.write(0);
        return;
    }
    if (newPosition == encPosition)
    {
        return;
    }
    Serial.print("New position: ");
    Serial.print(newPosition);
    Serial.println(".");
    encPosition = newPosition;
    isDisplayNeedsUpdate = true;
}

void setupRotaryButton()
{
    pinMode(PIN_BTN, INPUT_PULLUP);
}
void loopRotaryButton()
{
    loopEncoder();
    loopButton();
}
