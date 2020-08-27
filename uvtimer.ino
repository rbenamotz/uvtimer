#include <Encoder.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define STATE_SETTING 0
#define STATE_RUNNING 1
#define PIN_BTN 8
#define PIN_RELAY 9
#define FONT_SIZE 3


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 4);

int state = STATE_SETTING;
Encoder myEnc(2, 3);

void setup() {
  Serial.begin(9600);
  Serial.println("UV Timer");
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.setTextSize(FONT_SIZE);
  display.setTextColor(SSD1306_WHITE);
  display.display();
  display.clearDisplay();
  pinMode(PIN_BTN, INPUT_PULLUP);
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, false);
}

long oldPosition  = -999;
unsigned long timerStartTime = 0;
unsigned long timerEndTime = 0;
bool isDisplayNeedsUpdate = true;

void startTimer() {
  timerStartTime = millis();
  timerEndTime = timerStartTime + oldPosition * 1000 * 60;
  digitalWrite(PIN_RELAY, true);
  state = STATE_RUNNING;
  Serial.println("Timer started");
}

void stopTimer() {
  digitalWrite(PIN_RELAY, false);
  state = STATE_SETTING;
  myEnc.write(oldPosition * 4);
  Serial.print("Timer stopped. Writing ");
  Serial.print(oldPosition * 4);
  Serial.println(" to MyEnc");
  isDisplayNeedsUpdate = true;

}

void loopTimer() {
  static unsigned long lastDisplayUpdate = 0;
  if (state != STATE_RUNNING) {
    return;
  }
  if (millis() >= timerEndTime) {
    Serial.print(millis());
    Serial.print(" - ");
    Serial.println(timerEndTime);
    stopTimer();
  }
  unsigned long l = millis() - lastDisplayUpdate;
  if (l>10) {
    isDisplayNeedsUpdate = true;
    lastDisplayUpdate = millis();
  }
}

void loopButton()
{
  static unsigned long lastButtonDownEvent = 0;
  static bool lastRead = false;
  bool b = !digitalRead(PIN_BTN);
  if (!lastRead && b) {
    unsigned long l = millis() - lastButtonDownEvent;
    if (l<500) {
      return;
    }
    if (state == STATE_SETTING) {
      startTimer();
    }
    else if (state == STATE_RUNNING) {
      stopTimer();
    }
    lastButtonDownEvent = millis();
  }
  lastRead = b;
}

void loopEncoder() {
  if (state != STATE_SETTING) {
    return;
  }
  long newPosition = myEnc.read() / 4;
  if (newPosition <0) {
    myEnc.write(0);
    return;
  }
  if (newPosition == oldPosition) {
    return;
  }
  Serial.print("New position: ");
  Serial.print(newPosition);
  Serial.println(".");
  oldPosition = newPosition;
  isDisplayNeedsUpdate = true;
}



void loop() {
  loopEncoder();
  loopButton();
  loopTimer();
  loopDisplay();
}

String formatInt(unsigned int v) {
  String output = String(v);
  if (v < 10) {
    output = "0" + output;
  }
  return output;
}

void loopDisplay() {
//  static bool b = true;/
  if (!isDisplayNeedsUpdate) {
    return;
  }
  display.clearDisplay();
//  display.setCursor(0, 2);  /   // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  String str = "";
  if (state == STATE_SETTING) {
    str = formatInt(oldPosition) + ":00";
  }
  if (state == STATE_RUNNING) {
    unsigned long l = timerEndTime - millis();
    l = l / 1000 + 1;
    unsigned int m = l / 60;
    unsigned int s = l - (m * 60);
    bool b = (millis() % 500) > 250;
    str = formatInt(m);
    str = str + (b? ":" : " ");
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
