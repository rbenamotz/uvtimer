#include <Arduino.h>
#include "rotarybutton.h"
#include "display.h"
#include <Encoder.h>
#include "uvtimer.h"
#include "common.h"

void setup()
{
    Serial.begin(9600);
    Serial.println("Hello from UV Timer");
    pinMode(PIN_STATUS_LED, OUTPUT);
    setupDisplay();
    setupUvTimer();
    setupRotaryButton();
}


void loopBlink() {
    static unsigned long lastBlink = 0;
    static bool b = true;
    unsigned long l = millis() - lastBlink;
    if (l<=500) { 
        return;
    }
    digitalWrite(PIN_STATUS_LED,b);
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
