#include <Arduino.h>

#include "due_can.h"

#pragma once

struct buttonStates {
  bool left_blinker = false;    // true -> flash left blinker
  bool right_blinker = false;   // true -> flash right blinker
  bool cruise_control = false;  // true -> enable cruise control
};

class carState {
 public:
  bool reversed = false;  // true -> driving in reverse; false -> driving forward
  bool pedalFault = false;
  bool BPSfault = false;  // true -> fault
  bool braking = false;   // true -> break pedal applied, turn on break lights
  buttonStates buttons;
  bool has_fault();
};
