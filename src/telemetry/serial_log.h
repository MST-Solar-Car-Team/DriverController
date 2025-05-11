#include <Arduino.h>

#pragma once

constexpr byte PEDAL_PACKET_ID = 0x13;
constexpr byte CAN_PACKET_ID = 0x01;
constexpr byte LIGHTS_PACKET_ID = 0x02;

class PedalPacket {
 private:
  short baseline;
  short pedal;

 public:
  void send_bytes();
  PedalPacket(uint16_t baseline, uint16_t pedal) {
    this->baseline = baseline;
    this->pedal = pedal;
  }
};
