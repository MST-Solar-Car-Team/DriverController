#include <Arduino.h>
#include "due_can.h"
#include "../states/states.h"
#include "../pins/pins.h"

#pragma once

// Variables
#define ACC_PEDAL_MIN 600
//#define VELOCITY_MAX 3000 // 9000

// DESC:     updates the pedal value in the drive object
// INPUT:    pass by reference the drive object
// OUT:      the pedal member of drive will be written to,
//           the reversed member of drive will be read from
void update_drive_pedal(driveState &drive);