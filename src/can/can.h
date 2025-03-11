#include <Arduino.h>
#include "../states/states.h"

#pragma once

// CAN addresses
#define DRIVE_FRAME_ID 0x501
#define POWER_FRAME_ID 0x502
// #define VELOCITY_MAX  3000//9000

const float VELOCITY_MAX = 3000;  

void handelMessageCAN(CAN_FRAME *frame);

void update_drive_frame();

void update_power_frame();

void sendDriveMessage();

void sendPowerMessage();