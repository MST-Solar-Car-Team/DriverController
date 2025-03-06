#include <Arduino.h>
#include "due_can.h"

#pragma once

struct driveState
{
    CAN_FRAME driveFrame;      // contains the current status of the drive frame that is sent to the motor controller
    CAN_FRAME powerFrame;      // contains the current status of the power frame that is sent to the motor controller
    uint32_t busCurrent = 1.0; // drawn current from the power bus according to current limit

    float pedal;      // floating point value between 0 and 1
    bool reversed;    // true -> driving in reverse; false -> driving forward
    bool BPSfault;    // true -> fault
    bool blink_left;  // true -> flash left blinker
    bool blink_right; // true -> flash right blinker
    bool breaking;    // true -> break pedal applied, turn on break lights
};

struct blinkerState
{
    bool blink_left;  // current state of the left blinker
    bool blink_right; // current state of the right blinker
};

extern driveState drive;
