#include "serial_log.h"

char sum_bytes(unsigned char data[16]) {
  char sum = 0;
  for (int i = 1; i < 15; i++) {
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

  data[15] = sum_bytes(data);

  Serial.write(data, 16);
}

void CanPacket::send_bytes() {
  unsigned char data[16] = {0};

  data[0] = packet_id;
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
