#include <Arduino.h>

#pragma once

constexpr byte PEDAL_PACKET_ID = 0x13;
constexpr byte CAN_PACKET_ID = 0x01;
constexpr byte LIGHTS_PACKET_ID = 0x02;

// can message id is this + 0x400 (motor controller base address)
constexpr byte VELOCITY_PACKET_ID = 0x03;

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

class CanPacket {
 private:
  byte packet_id;
  int high;
  int low;

 public:
  void send_bytes();
  CanPacket(byte packet_id, int high, int low) {
    this->packet_id = packet_id;
    this->high = high;
    this->low = low;
  }
};