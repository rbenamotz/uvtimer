#define STATE_SETTING 0
#define STATE_RUNNING 1



#define PIN_BTN 8
#define PIN_RELAY 9
#define PIN_ENC_1 2
#define PIN_ENC_2 3
#define FONT_SIZE 3


extern unsigned long timerStartTime;
extern unsigned long timerEndTime;
extern bool isDisplayNeedsUpdate;
extern int state;
extern long encPosition;
