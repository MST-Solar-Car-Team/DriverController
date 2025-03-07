#include "pins.h"
#include "../states/states.h"

// Initilize pins
void pinInit()
{

    // set input pins
    pinMode(ACC_PEDAL, INPUT);
    pinMode(BREAK_PEDAL, INPUT);
    pinMode(TURN_LEFT_BUTTON, INPUT);
    pinMode(TURN_RIGHT_BUTTON, INPUT);
    pinMode(DRIVE_DIRECTION_SWITCH, INPUT);

    // set output pins
    pinMode(HEADLIGHTS, OUTPUT);
    pinMode(BLINKER_LEFT, OUTPUT);
    pinMode(BLINKER_RIGHT, OUTPUT);
    pinMode(BREAKLIGHT, OUTPUT);
    pinMode(STROBELIGHT, OUTPUT);
};

void readButtons() {
    buttons.left_blinker = digitalRead(TURN_LEFT_BUTTON);
    buttons.right_blinker = digitalRead(TURN_RIGHT_BUTTON);
    buttons.cruise_control = digitalRead(CRUISE__CONTROL_BUTTON);
};