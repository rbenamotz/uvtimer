#include <Arduino.h>
#include "rotarybutton.h"
#include "display.h"
#include <Encoder.h>
#include "uvtimer.h"
#include "common.h"

void setup()
{
#ifdef ENV_DEV
    Serial.begin(9600);
#endif
    Serial.println("Hello from UV Timer");
    pinMode(PIN_STATUS_LED, OUTPUT);
    setupDisplay();
    setupUvTimer();
    setupRotaryButton();
    sei();
}


void loopBlink()
{
    static unsigned long lastBlink = 0;
    static bool b = true;
    unsigned long l = millis() - lastBlink;
    unsigned long delay = state == STATE_RUNNING ? 100 : 1000;
    if (l <= delay)
    {
        return;
    }
    digitalWrite(PIN_STATUS_LED, b);
    b = !b;
    lastBlink = millis();
}
void loop()
{
    loopBlink();
    loopRotaryButton();
    loopUvTimer();
    loopDisplay();
}
