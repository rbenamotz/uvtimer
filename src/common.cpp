#include "common.h"


unsigned long timerStartTime = 0;
unsigned long timerEndTime = 0;
bool isDisplayNeedsUpdate = true;
int state = STATE_SETTING;

long encPosition = -999;