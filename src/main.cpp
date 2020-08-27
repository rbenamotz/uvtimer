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
    setupDisplay();
    setupUvTimer();
    setupRotaryButton();
}

void loop()
{
    loopRotaryButton();
    loopUvTimer();
    loopDisplay();
}
