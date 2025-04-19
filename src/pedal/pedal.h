#include <Arduino.h>

#include "../pins/pins.h"
#include "../states/states.h"
#include "due_can.h"

#pragma once

// Variables
#define ACC_PEDAL_MIN 600

float get_pedal_value();
