#include <Arduino.h>

#include "../states/states.h"

#pragma once

/////   PIN DEFINITIONS
#define ACC_PEDAL A7
#define ACC_BASELINE A6
#define BRAKE_PEDAL 84
#define DRIVE_DIRECTION_SWITCH 21  // High for reverse, Low for forward
#define TURN_LEFT_BUTTON 52        // 20
#define TURN_RIGHT_BUTTON 132
#define CRUISE_CONTROL_BUTTON 133

// outputs
#define HEADLIGHTS 65
#define BLINKER_LEFT 67
#define BLINKER_RIGHT 71
#define BRAKELIGHT 101
#define STROBELIGHT 55

void pinInit();

void readButtons(buttonStates &buttons);
