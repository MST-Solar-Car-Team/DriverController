#include <Arduino.h>

#include "../states/states.h"

#pragma once

/////   PIN DEFINITIONS
#define ACC_PEDAL A7
#define ACC_BASELINE A6

// outputs
#define BLINKER_BACK_LEFT 39
#define BLINKER_BACK_RIGHT 41

#define BLINKER_FRONT_LEFT 36
#define BLINKER_FRONT_RIGHT 35

#define BRAKE_RIGHT 42
#define BRAKE_LEFT 44

#define HEADLIGHTS 38

void pinInit();

void readButtons(buttonStates &buttons);
