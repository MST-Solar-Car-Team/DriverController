/*
* This file is the main program for the electronic control unit for the Missouri S&T Solar Car.
* This program is meant to be run on an Arduino Due board and bootloaded using the Arduino IDE.
*
*////////////////////////////////////////

#include <Arduino.h>
#include <due_can.h>
#include <DueTimer.h>
#include "src/utils.h"

//this will hold all the data relevent to the status of the car
driveState drive;
blinkerState blinkers;

using namespace std;

void handelMessageCAN(CAN_FRAME *frame);
void handelBlinkerLeft();
void handelBlinkerRight();
void sendDriveMessage();
void sendPowerMessage();

//timer settup
DueTimer blinkLeftTimer = Timer.getAvailable().attachInterrupt(handelBlinkerLeft).setFrequency(2);
DueTimer blinkRightTimer = Timer.getAvailable().attachInterrupt(handelBlinkerRight).setFrequency(2);
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
  update_drive_pedal(drive);
  update_drive_blinkers(drive);
  update_drive_frame(drive);

  //check and update Timers
  if(drive.blink_left){
    blinkLeftTimer.start();
  } else {
    blinkLeftTimer.stop();
  }

  if(drive.blink_right){
    blinkRightTimer.start();
  } else {
    blinkRightTimer.stop();
  }

  
  
}

//INTERRUPT SERVICE ROUTINES/////////////////////////
void handelMessageCAN(CAN_FRAME *frame){

  return;
}

void handelBlinkerLeft(){
  blinkers.blink_left != blinkers.blink_left;
  digitalWrite(BLINKER_LEFT, blinkers.blink_left);
}

void handelBlinkerRight(){
  blinkers.blink_right != blinkers.blink_right;
  digitalWrite(BLINKER_RIGHT, blinkers.blink_right);
}

void sendDriveMessage(){
  Can0.sendFrame(drive.driveFrame);
}

void sendPowerMessage(){
  Can0.sendFrame(drive.powerFrame);
}
