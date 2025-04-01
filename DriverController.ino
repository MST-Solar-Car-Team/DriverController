/*
 * This file is the main program for the electronic control unit for the
 * Missouri S&T Solar Car. This program is meant to be run on an Arduino Due
 * board and bootloaded using the Arduino IDE.
 *
 *////////////////////////////////////////

#include "src/can/can.h"
#include "src/pedal/pedal.h"
#include "src/pins/pins.h"
#include <Arduino.h>
#include <DueTimer.h>
#include <due_can.h>

using namespace std;

driveState drive;
buttonStates buttons;

// timer settup
DueTimer driveTimer = Timer.getAvailable()
                          .attachInterrupt([]() { sendDriveMessage(drive); })
                          .start(100000);
DueTimer powerTimer = Timer.getAvailable()
                          .attachInterrupt([]() { sendPowerMessage(drive); })
                          .start(100000);

void setup() {
  // setup the CAN bus interface
  Can0.begin(500000, 255);
  Can1.begin(500000, 255);

  Can0.watchFor(); // allows all canbus traffic through

  Can0.setGeneralCallback(handelMessageCAN); // receive CAN callback

  pinInit();

  Serial.begin(9600);
}

void loop() {

  // update statuses
  update_drive_pedal(drive);
  // update_drive_blinkers(drive);
  update_drive_frame(drive);

  readButtons(buttons);
  // Serial.println(drive.driveFrame.data.high);

  // Serial.println(buttons.left_blinker);

  // flashBlinkers(drive);
}
