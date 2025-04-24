#include <Arduino.h>

#include "due_can.h"

#pragma once

#define DEBOUNCE_THRESHOLD 5 // how many loops to wait before registering a button press

struct buttonStates {
  bool left_blinker = false;    // true -> flash left blinker
  bool right_blinker = false;   // true -> flash right blinker
  bool cruise_control = false;  // true -> enable cruise control
  bool headlights = false;      // true -> turn on headlights
  bool horn = false;            // true -> honk horn
};

class carState {
 public:
  bool reversed = false;  // true -> driving in reverse; false -> driving forward
  bool pedalFault = false;
  bool BPSfault = false;  // true -> fault
  bool braking = false;   // true -> break pedal applied, turn on break lights
  buttonStates buttons;
  bool has_fault();
  bool flasher_state = false;  // true -> flashers on, false -> flashers off

  void toggle_flasher();
  void readButtons();
};