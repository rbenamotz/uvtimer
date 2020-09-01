#include <Arduino.h>
#include "common.h"
#include "uvtimer.h"
unsigned volatile int counter = 0;
#ifdef ENV_DEV
#define CLOCK_BLINK_INTERVAL 100
#define ONE_SEC_COUNT 1000
#else
#define CLOCK_BLINK_INTERVAL 50
#define ONE_SEC_COUNT 500
#endif

void setupUvTimer()
{
    pinMode(PIN_RELAY, OUTPUT);
    digitalWrite(PIN_RELAY, false);
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
}

SIGNAL(TIMER0_COMPA_vect)
{
    counter++;
    if (counter % CLOCK_BLINK_INTERVAL == 0)
    {
        isDisplayNeedsUpdate = true;
    }
    if (counter < ONE_SEC_COUNT)
    {
        return;
    }
    secondsLeft--;
    isDisplayNeedsUpdate = true;
    if (secondsLeft == 0)
    {
        stopTimer();
    }
    counter = 0;
}

void loopUvTimer()
{
}

void startTimer()
{
    digitalWrite(PIN_RELAY, true);
    secondsLeft = encPosition * 60;
    counter = 0;
    state = STATE_RUNNING;
    Serial.print("Starting timer for ");
    Serial.print(secondsLeft);
    Serial.println(" seconds");
    isDisplayNeedsUpdate = true;
}

void stopTimer()
{
    digitalWrite(PIN_RELAY, false);
    state = STATE_SETTING;
    Serial.print("Timer stopped with ");
    Serial.print(secondsLeft);
    Serial.println(" seconds left");
    isDisplayNeedsUpdate = true;
}