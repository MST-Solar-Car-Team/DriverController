#include <Arduino.h>
#include "due_can.h"

#pragma once

struct driveState
{
    CAN_FRAME driveFrame;      // contains the current status of the drive frame that is sent to the motor controller
    CAN_FRAME powerFrame;      // contains the current status of the power frame that is sent to the motor controller
    uint32_t busCurrent = 1.0; // drawn current from the power bus according to current limit

    float pedal;   // floating point value between 0 and 1
    bool reversed; // true -> driving in reverse; false -> driving forward
    bool pedalFault = false;
    bool BPSfault; // true -> fault
    bool breaking; // true -> break pedal applied, turn on break lights
};

struct buttonStates
{
    int left_blinker;  // true -> flash left blinker
    int right_blinker; // true -> flash right blinker
    int cruise_control; // true -> enable cruise control
};

extern driveState drive;
extern buttonStates buttons;
