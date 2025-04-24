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

  static int debounce_left = 0;
  static int debounce_right = 0;
  static int debounce_cruise = 0;
  static int debounce_headlights = 0;

  bool input_left = digitalRead(LEFT_TURN_SIGNAL_BUTTON);
  bool input_right = digitalRead(RIGHT_TURN_SIGNAL_BUTTON);
  bool input_cruise = digitalRead(CRUISE_CONTROL);
  bool input_headlights = digitalRead(HEADLIGHTS_BUTTON);
  bool input_horn = digitalRead(HORN_BUTTON);
  bool input_brake = digitalRead(BRAKE_SWITCH);

  // Toggle states on falling edges high->low, with debounce
  if (!input_left && prev_left && debounce_left == 0) {
    this->buttons.left_blinker = !this->buttons.left_blinker;
    debounce_left = DEBOUNCE_THRESHOLD;
  }
  if (debounce_left > 0) debounce_left--;
  prev_left = input_left;

  if (!input_right && prev_right && debounce_right == 0) {
    this->buttons.right_blinker = !this->buttons.right_blinker;
    debounce_right = DEBOUNCE_THRESHOLD;
  }
  if (debounce_right > 0) debounce_right--;
  prev_right = input_right;

  if (!input_headlights && prev_headlights && debounce_headlights == 0) {
    this->buttons.headlights = !this->buttons.headlights;
    debounce_headlights = DEBOUNCE_THRESHOLD;
  }
  if (debounce_headlights > 0) debounce_headlights--;
  prev_headlights = input_headlights;

  if (!input_cruise && prev_cruise && debounce_cruise == 0) {
    this->buttons.cruise_control = !this->buttons.cruise_control;
    debounce_cruise = DEBOUNCE_THRESHOLD;
  }
  if (debounce_cruise > 0) debounce_cruise--;
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

  if (!input_brake) {
    digitalWrite(BRAKE_LEFT, HIGH);
    digitalWrite(BRAKE_RIGHT, HIGH);
  } else {
    digitalWrite(BRAKE_LEFT, LOW);
    digitalWrite(BRAKE_RIGHT, LOW);
  }
  // TODO: horn
}
