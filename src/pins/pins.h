#include <Arduino.h>

#include "../states/states.h"

#pragma once

/////   PIN DEFINITIONS
#define ACC_PEDAL A7
#define ACC_BASELINE A6
// outputs
#define BLINKER_BACK_LEFT 60 //39
#define BLINKER_BACK_RIGHT 55 //41

#define BLINKER_FRONT_LEFT 15 //36
#define BLINKER_FRONT_RIGHT 19 //35

#define BRAKE_RIGHT 116 //42
#define BRAKE_LEFT 116 //44

#define HEADLIGHTS 38
#define HORN_RELAY 400 //TODO: assaign real number

#define CRUISE_CONTROL 7
#define LEFT_TURN_SIGNAL_BUTTON  A2   //3 //TODO: reassign pin numbers gotten from jake
#define RIGHT_TURN_SIGNAL_BUTTON A3   //5
#define HEADLIGHTS_BUTTON 6
#define HORN_BUTTON 2
#define BRAKE_SWITCH A1 //9
#define REVERSE_SWITCH 11
#define HAZARDS_SWITCH 40 //TODO: actual pin number

void pinInit();
