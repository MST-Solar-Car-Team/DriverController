#include <Arduino.h>

#include "../states/states.h"

#pragma once

/////   PIN DEFINITIONS
#define ACC_PEDAL A7
#define ACC_BASELINE A6
// outputs
#define BLINKER_BACK_LEFT 35 //60 //39
#define BLINKER_BACK_RIGHT 33 //55 //41

#define BLINKER_FRONT_LEFT 27 //15 //36
#define BLINKER_FRONT_RIGHT 23 //19 //35

#define HEADLIGHTS 30

#define BRAKE_RIGHT 36 //116 //42
#define BRAKE_LEFT  36 //116 //44

#define CRUISE_CONTROL 8
#define LEFT_TURN_SIGNAL_BUTTON   6
#define RIGHT_TURN_SIGNAL_BUTTON  5
#define HEADLIGHTS_BUTTON 2 //6
#define HORN_BUTTON 2
#define BRAKE_SWITCH 7 //9
#define REVERSE_SWITCH 11

#define LEFT_INTERNAL_SIGNAL 29
#define RIGHT_INTERNAL_SIGNAL 32

void pinInit();
