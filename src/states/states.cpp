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

  static unsigned long last_left = 0;
  static unsigned long last_right = 0;
  static unsigned long last_cruise = 0;
  static unsigned long last_headlights = 0;

  const unsigned long debounce_time = DEBOUNCE_TIME; // 0.5 seconds
  
  
  bool input_left = digitalRead(LEFT_TURN_SIGNAL_BUTTON);
  bool input_right = digitalRead(RIGHT_TURN_SIGNAL_BUTTON);
  bool input_cruise = digitalRead(CRUISE_CONTROL);
  bool input_headlights = digitalRead(HEADLIGHTS_BUTTON);
  bool input_horn = digitalRead(HORN_BUTTON);
  bool input_brake = digitalRead(BRAKE_SWITCH);

  unsigned long now = millis();

  // Toggle states on falling edges high->low, with debounce
  if (!input_left && prev_left && (now - last_left > debounce_time)) {
    this->buttons.left_blinker = !this->buttons.left_blinker;
    last_left = now;
    if (this->buttons.left_blinker) {
      this->flasher_state = true; // for more responsiveness
    }
  }
  prev_left = input_left;

  if (!input_right && prev_right && (now - last_right > debounce_time)) {
    this->buttons.right_blinker = !this->buttons.right_blinker;
    last_right = now;
    if (this->buttons.right_blinker) {
      this->flasher_state = true;
    }
  }
  prev_right = input_right;

  if (!input_headlights && prev_headlights && (now - last_headlights > debounce_time)) {
    this->buttons.headlights = !this->buttons.headlights;
    last_headlights = now;
  }
  prev_headlights = input_headlights;

  if (!input_cruise && prev_cruise && (now - last_cruise > debounce_time)) {
    this->buttons.cruise_control = !this->buttons.cruise_control;
    last_cruise = now;
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

  if (!input_brake) {
    digitalWrite(BRAKE_LEFT, HIGH);
    digitalWrite(BRAKE_RIGHT, HIGH);
    this->braking = true;
  } else {
    digitalWrite(BRAKE_LEFT, LOW);
    digitalWrite(BRAKE_RIGHT, LOW);
    this->braking = false;
  }
  // TODO: horn
}
