/*
* This file is the main program for the electronic control unit for the Missouri S&T Solar Car.
* This program is meant to be run on an Arduino Due board and bootloaded using the Arduino IDE.
*
*////////////////////////////////////////

#include <Arduino.h>
#include <due_can.h>
#include <DueTimer.h>
#include "src/pedal/pedal.h"
#include "src/can/can.h"
#include "src/pins/pins.h"



using namespace std;

//timer settup
DueTimer driveTimer = Timer.getAvailable().attachInterrupt(sendDriveMessage).start(100000);
DueTimer powerTimer = Timer.getAvailable().attachInterrupt(sendPowerMessage).start(100000);

void setup() {
  //setup the CAN bus interface
  Can0.begin(500000, 255);
  Can1.begin(500000, 255);

  Can0.watchFor();  //allows all canbus traffic through

  Can0.setGeneralCallback(handelMessageCAN); //receive CAN callback

  pinInit();

  Serial.begin(9600);
}

void loop() {

  //update statuses
  update_drive_pedal();
  // update_drive_blinkers(drive);
  update_drive_frame();

  readButtons();
  Serial.println(drive.driveFrame.data.high);
  // Serial.println(buttons.left_blinker);

  // flashBlinkers(drive);
  
}

