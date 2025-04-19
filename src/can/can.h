#include <Arduino.h>

#include "../states/states.h"

#pragma once

// CAN addresses
#define DRIVE_FRAME_ID 0x501
#define POWER_FRAME_ID 0x502

const float VELOCITY_MAX = 9000;
const uint32_t CURRENT_MAX = 1;

void handle_can_message(CAN_FRAME *frame);

CAN_FRAME get_drive_frame(carState &car);

CAN_FRAME get_power_frame();

void send_drive_message(carState &car);

void send_power_message();
