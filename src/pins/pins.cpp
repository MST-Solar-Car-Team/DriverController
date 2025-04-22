#include "pins.h"

#include "../states/states.h"

// Initilize pins
void pinInit() {
  // set input pins
  pinMode(A7, INPUT);  // CANNOT BE DEFINED AS A #define -- Will break shit
  pinMode(A6, INPUT);  // CANNOT BE DEFINED AS A #define -- Will break shit

  pinMode(BLINKER_BACK_LEFT, OUTPUT);
  pinMode(BLINKER_BACK_RIGHT, OUTPUT);
  pinMode(BLINKER_FRONT_LEFT, OUTPUT);
  pinMode(BLINKER_FRONT_RIGHT, OUTPUT);
  pinMode(BRAKE_RIGHT, OUTPUT);
  pinMode(BRAKE_LEFT, OUTPUT);
  pinMode(HEADLIGHTS, OUTPUT);

  pinMode(CRUISE_CONTROL, INPUT);
  pinMode(RIGHT_TURN_SIGNAL_BUTTON, INPUT);
  pinMode(LEFT_TURN_SIGNAL_BUTTON, INPUT);
  pinMode(BLACK_BUTTON, INPUT);
  pinMode(HORN_BUTTON, INPUT);
};

void readButtons(buttonStates &buttons) {
  // buttons.left_blinker = digitalRead(TURN_LEFT_BUTTON);
  // buttons.right_blinker = digitalRead(TURN_RIGHT_BUTTON);
  // buttons.cruise_control = digitalRead(CRUISE_CONTROL_BUTTON);
};
