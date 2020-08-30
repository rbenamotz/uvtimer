#include <Arduino.h>
#include "uvtimer.h"
#include "common.h"
#include "Encoder.h"
#include <EEPROM.h>
Encoder myEnc(PIN_ENC_2, PIN_ENC_1);

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
            EEPROM.write(EEPROM_ADDR_ENC, encPosition);
            Serial.print("Wrote ");
            Serial.print(encPosition);
            Serial.println(" from EEPROM");
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
    long newPosition = myEnc.read() / ENC_STEPS;
    if (state != STATE_SETTING)
    {
        myEnc.write(encPosition * ENC_STEPS);
        return;
    }
    if (newPosition < MIN_TIMER_VALUE)
    {
        myEnc.write(MIN_TIMER_VALUE * ENC_STEPS);
        return;
    }
    if (newPosition > MAX_TIMER_VALUE)
    {
        myEnc.write(MAX_TIMER_VALUE * ENC_STEPS);
        return;
    }
    if (newPosition == encPosition)
    {
        return;
    }
    encPosition = newPosition;
    isDisplayNeedsUpdate = true;
}

void setupRotaryButton()
{
    pinMode(PIN_BTN, INPUT_PULLUP);
    long l = EEPROM.read(EEPROM_ADDR_ENC);
    Serial.print("Read ");
    Serial.print(l);
    Serial.println(" from EEPROM");
    if (l < MIN_TIMER_VALUE || l > MAX_TIMER_VALUE)
    {
        l = DEFAULT_TIMER_VALUE;
    }
    myEnc.write(l * ENC_STEPS);
}
void loopRotaryButton()
{
    loopEncoder();
    loopButton();
}
