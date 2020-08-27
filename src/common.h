#define STATE_SETTING 0
#define STATE_RUNNING 1

#ifdef ENV_PROD
#define PIN_BTN PD6
#define PIN_RELAY PD7
#define PIN_ENC_1 PD2
#define PIN_ENC_2 PD3
#define PIN_STATUS_LED PD5
#else
#define PIN_BTN 8
#define PIN_RELAY 9
#define PIN_ENC_1 2
#define PIN_ENC_2 3
#define PIN_STATUS_LED LED_BUILTIN
#endif

extern unsigned long timerStartTime;
extern unsigned long timerEndTime;
extern bool isDisplayNeedsUpdate;
extern int state;
extern long encPosition;
