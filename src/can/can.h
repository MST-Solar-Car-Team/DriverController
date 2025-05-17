#include <Arduino.h>

#include "../states/states.h"

#pragma once

// CAN addresses
constexpr short DRIVE_FRAME_ID = 0x501;
constexpr short POWER_FRAME_ID = 0x502;

constexpr short MOTOR_STATUS_FRAME_ID = 0x401;
constexpr short MOTOR_HEAT_FRAME_ID = 0x40B;
constexpr short MOTOR_VELOCITY_FRAME_ID = 0x403;

constexpr float VELOCITY_MAX = 9000;
constexpr float CURRENT_MAX = 1;

void handle_can_message(CAN_FRAME *frame);

CAN_FRAME get_drive_frame(carState &car);

CAN_FRAME get_power_frame();

void send_drive_message(carState &car);

void send_power_message();
