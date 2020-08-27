#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "common.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 4);

String formatInt(unsigned int v)
{
    String output = String(v);
    if (v < 10)
    {
        output = "0" + output;
    }
    return output;
}

void setupDisplay()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    { // Address 0x3C for 128x32
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    display.setTextSize(FONT_SIZE);
    display.setTextColor(SSD1306_WHITE);
    display.display();
    display.clearDisplay();
}

void loopDisplay()
{
    if (!isDisplayNeedsUpdate)
    {
        return;
    }
    display.clearDisplay();
    display.cp437(true); // Use full 256 char 'Code Page 437' font
    String str = "";
    if (state == STATE_SETTING)
    {
        str = formatInt(encPosition) + ":00";
    }
    if (state == STATE_RUNNING)
    {
        unsigned long l = timerEndTime - millis();
        l = l / 1000 + 1;
        unsigned int m = l / 60;
        unsigned int s = l - (m * 60);
        bool b = (millis() % 500) > 250;
        str = formatInt(m);
        str = str + (b ? ":" : " ");
        str = str + formatInt(s);
        b = !b;
    }
    int x = (display.width() - str.length() * 6 * FONT_SIZE) / 2;
    int y = (display.height() - FONT_SIZE * 6) / 2;
    display.setCursor(x, y);
    display.print(str);
    display.display();
    isDisplayNeedsUpdate = false;
}
