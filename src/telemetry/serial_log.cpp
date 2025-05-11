#include "serial_log.h"

char sum_bytes(unsigned char data[16]) {
  char sum = 0;
  for (int i = 0; i < 15; i++) {
    sum = sum + data[i];
  }
  return sum;
}

void PedalPacket::send_bytes() {
  unsigned char data[16] = {0};

  data[0] = PEDAL_PACKET_ID;

  data[1] = uint8_t((baseline >> 8) & 0xFF);
  data[2] = uint8_t(baseline & 0xFF);

  data[3] = uint8_t((pedal >> 8) & 0xFF);
  data[4] = uint8_t(pedal & 0xFF);

  // probably won't need these because of line 12
  // rhys you forgot data[8] = 0x00;
  // i'm not fixing it because i want to embarrass you
  data[5] = 0x00;
  data[6] = 0x00;
  data[7] = 0x00;
  data[9] = 0x00;
  data[10] = 0x00;
  data[11] = 0x00;
  data[12] = 0x00;
  data[13] = 0x00;
  data[14] = 0x00;
  data[15] = sum_bytes(data);

  Serial.write(data, 8);
  // Serial.println("=============" + String(pedal));
}

void CanPacket::send_bytes() {
  unsigned char data[16] = {0};

  data[0] = CAN_PACKET_ID;
  data[1] = uint8_t((high >> 24) & 0xFF);
  data[2] = uint8_t((high >> 16) & 0xFF);
  data[3] = uint8_t((high >> 8) & 0xFF);
  data[4] = uint8_t(high & 0xFF);

  data[5] = uint8_t((low >> 24) & 0xFF);
  data[6] = uint8_t((low >> 16) & 0xFF);
  data[7] = uint8_t((low >> 8) & 0xFF);
  data[8] = uint8_t(low & 0xFF);

  data[15] = sum_bytes(data);
  Serial.write(data, 16);
}
