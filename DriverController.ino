/*
 * This file is the main program for the electronic control unit for the
 * Missouri S&T Solar Car. This program is meant to be run on an Arduino Due
 * board and bootloaded using the Arduino IDE.
 *
*/

#include <Arduino.h>
#include <DueTimer.h>
#include <due_can.h>

#include "src/can/can.h"
#include "src/pedal/pedal.h"
#include "src/pins/pins.h"

using namespace std;

carState car_state;

DueTimer driveTimer =
    Timer.getAvailable().attachInterrupt([]() { send_drive_message(car_state); }).start(100000);
DueTimer powerTimer =
    Timer.getAvailable().attachInterrupt([]() { send_power_message(); }).start(100000);


void setup() {
  // setup the CAN bus interface
  Can0.begin(500000, 255);

  Can0.watchFor();  // allows all canbus traffic through

  Can0.setGeneralCallback(handle_can_message);  // receive CAN callback

  pinInit();

  Serial.begin(9600);
}

void loop() {

  readButtons(car_state.buttons);

  Serial.println(digitalRead(CRUISE_CONTROL));

}
