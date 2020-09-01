#include "common.h"


volatile unsigned int secondsLeft = 0;
volatile bool isDisplayNeedsUpdate = true;
int state = STATE_SETTING;

long encPosition = -999;