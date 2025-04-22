#include "pins.h"

#include "../states/states.h"

// Initilize pins
void pinInit() {
  // set input pins
  pinMode(ACC_PEDAL, INPUT);

  pinMode(BLINKER_BACK_LEFT, OUTPUT);
  pinMode(BLINKER_BACK_RIGHT, OUTPUT);
  pinMode(BLINKER_FRONT_LEFT, OUTPUT);
  pinMode(BLINKER_FRONT_RIGHT, OUTPUT);
  pinMode(BRAKE_RIGHT, OUTPUT);
  pinMode(BRAKE_LEFT, OUTPUT);
  pinMode(HEADLIGHTS, OUTPUT);
};

void readButtons(buttonStates &buttons) {
  // buttons.left_blinker = digitalRead(TURN_LEFT_BUTTON);
  // buttons.right_blinker = digitalRead(TURN_RIGHT_BUTTON);
  // buttons.cruise_control = digitalRead(CRUISE_CONTROL_BUTTON);
};
