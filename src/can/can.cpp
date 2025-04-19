#include "can.h"

#include <Arduino.h>
#include <due_can.h>

#include "../pedal/pedal.h"

void handle_can_message(CAN_FRAME *frame) { return; }

// returns a CAN_FRAME for activating the motor in relation to the current pedal value
CAN_FRAME get_drive_frame(carState &car) {
  CAN_FRAME drive_frame;

  float speed = get_pedal_value();

  if (speed == -1) {
    car.pedalFault = true;
  }

  drive_frame.id = DRIVE_FRAME_ID;
  drive_frame.length = 8;

  memcpy(&drive_frame.data.high, &speed, sizeof(drive_frame.data.high));
  memcpy(&drive_frame.data.low, &VELOCITY_MAX, sizeof(drive_frame.data.low));

  return drive_frame;
};

// retruns the power frame
CAN_FRAME get_power_frame() {
  CAN_FRAME power_frame;

  power_frame.id = POWER_FRAME_ID;
  power_frame.length = 8;
  power_frame.data.high = CURRENT_MAX;
  power_frame.data.low = 0;

  return power_frame;
};

// fetches pedal data and sends a drive message over the CAN0 port on the due
void send_drive_message(carState &car) {
  if (!car.has_fault()) {
    CAN_FRAME frame = get_drive_frame(car);
    Can0.sendFrame(frame);
  }
}

// sends a power message over the CAN0 port on the due
void send_power_message() {
  CAN_FRAME frame = get_power_frame();
  Can0.sendFrame(frame);
}
