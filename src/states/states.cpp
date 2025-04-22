#include "states.h"

bool carState::has_fault() { return this->BPSfault || this->pedalFault || this->braking; }

// this will hold all the data relevent to the status of the car
// blinkerState blinkers;

void do_blinker(carState car) {
  if (car.buttons.left_blinker) {
    // digitalRead();
  }
}
