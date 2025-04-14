#include "can.h"

#include <Arduino.h>

#pragma once

void handelMessageCAN(CAN_FRAME *frame) { return; };

void update_drive_frame(driveState &drive)

{
  drive.driveFrame.id = DRIVE_FRAME_ID;
  drive.driveFrame.length = 8;
  // drive.driveFrame.data.high = drive.pedal;
  // drive.driveFrame.data.low = VELOCITY_MAX;
  memcpy(&drive.driveFrame.data.high, &drive.pedal, sizeof(drive.pedal));
  memcpy(&drive.driveFrame.data.low, &VELOCITY_MAX, sizeof(VELOCITY_MAX));
};

void update_power_frame(driveState &drive) {
  drive.driveFrame.id = POWER_FRAME_ID;
  drive.driveFrame.length = 8;
  drive.driveFrame.data.high = drive.busCurrent;
  drive.driveFrame.data.low = 0;
};

void sendDriveMessage(driveState &drive) {
  if (!drive.pedalFault) {
    Can0.sendFrame(drive.driveFrame);
  }
}

void sendPowerMessage(driveState &drive) { Can0.sendFrame(drive.powerFrame); }
