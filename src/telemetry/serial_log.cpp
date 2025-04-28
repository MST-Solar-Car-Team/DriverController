#include "serial_log.h"

void PedalPacket::send_bytes() {
  unsigned char data[6];

  data[0] = PEDAL_PACKET_ID;

  data[2] = uint8_t(baseline & 0xFF);
  data[1] = uint8_t((baseline >> 8) & 0xFF);

  data[4] = uint8_t(pedal & 0xFF);
  data[3] = uint8_t((pedal >> 8) & 0xFF);

  data[5] = END_BYTE;

  Serial.write(data, 6);
}
