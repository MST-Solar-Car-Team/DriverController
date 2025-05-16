#include <Arduino.h>

#pragma once

constexpr byte CAN_PACKET_ID = 0x01;
constexpr byte LIGHTS_PACKET_ID = 0x02;
constexpr byte VELOCITY_PACKET_ID = 0x03;
constexpr byte PEDAL_PACKET_ID = 0x04;

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

class LightsPacket {
 private:
  uint8_t headlights;
  uint8_t right_blinkers;
  uint8_t left_blinkers;
  uint8_t brake_lights;

 public:
  void send_bytes();
  LightsPacket(uint8_t headlight, uint8_t right_blinkers, uint8_t left_blinkers,
               uint8_t brake_lights) {
    this->headlights = headlight;
    this->right_blinkers = right_blinkers;
    this->left_blinkers = left_blinkers;
    this->brake_lights = brake_lights;
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
