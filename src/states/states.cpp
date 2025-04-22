#include "states.h"

#include "../pins/pins.h"

bool carState::has_fault() { return this->BPSfault || this->pedalFault || this->braking; }

// this will hold all the data relevent to the status of the car
// blinkerState blinkers;

void carState::toggle_flasher() { this->flasher_state = !this->flasher_state; }

void carState::readButtons() {
  static bool prev_left = true;
  static bool prev_right = true;
  static bool prev_cruise = true;
  static bool prev_headlights = true;

  bool input_left = digitalRead(LEFT_TURN_SIGNAL_BUTTON);
  bool input_right = digitalRead(RIGHT_TURN_SIGNAL_BUTTON);
  bool input_cruise = digitalRead(CRUISE_CONTROL);
  bool input_headlights = digitalRead(HEADLIGHTS_BUTTON);
  bool input_horn = digitalRead(HORN_BUTTON);

  // Toggle states on falling edges high->low
  if (!input_left && prev_left) {
    this->buttons.left_blinker = !this->buttons.left_blinker;
  }
  prev_left = input_left;

  if (!input_right && prev_right) {
    this->buttons.right_blinker = !this->buttons.right_blinker;
  }
  prev_right = input_right;

  if (!input_headlights && prev_headlights) {
    this->buttons.headlights = !this->buttons.headlights;
  }
  prev_headlights = input_headlights;

  if (!input_cruise && prev_cruise) {
    this->buttons.cruise_control = !this->buttons.cruise_control;
  }
  prev_cruise = input_cruise;

  this->buttons.horn = (input_horn == LOW);

  // perform actions

  if (this->buttons.left_blinker && this->flasher_state) {
    digitalWrite(BLINKER_BACK_LEFT, HIGH);
    digitalWrite(BLINKER_FRONT_LEFT, HIGH);
  } else {
    digitalWrite(BLINKER_BACK_LEFT, LOW);
    digitalWrite(BLINKER_FRONT_LEFT, LOW);
  }

  if (this->buttons.right_blinker && this->flasher_state) {
    digitalWrite(BLINKER_BACK_RIGHT, HIGH);
    digitalWrite(BLINKER_FRONT_RIGHT, HIGH);
  } else {
    digitalWrite(BLINKER_BACK_RIGHT, LOW);
    digitalWrite(BLINKER_FRONT_RIGHT, LOW);
  }

  if (this->buttons.headlights) {
    digitalWrite(HEADLIGHTS, HIGH);
  } else {
    digitalWrite(HEADLIGHTS, LOW);
  }

  // TODO: horn
}
