#include "pedal.h"

#include <Arduino.h>

// Gets the current value of the cars pedal
// return a number between 0 and 1 or -1 in the event of an error
float get_pedal_value() {
  int base_raw = analogRead(ACC_BASELINE);
  int pedal_raw = analogRead(ACC_PEDAL);

  int max = analogRead(ACC_BASELINE) * 0.9;  // makes a 10% dead-zone on the acceleration pedal
  int min = ACC_PEDAL_MIN;

  float pedal_value = pedal_raw;

  // Checks if the pedal value is greater than the baseline, in which the pedal is definitly
  // shorting
  if ((base_raw < (pedal_value - 50)) || (pedal_raw < min)) {
    return -1;
  }

  pedal_value -= min;
  pedal_value /= max - min;
  pedal_value = 1 - pedal_value;
  // forces the value to fall between 0 and 1, multiplies by 0.6 to limit max acceleration.
  // This is a bandaid fix to a bigger problem, see issue #5
  pedal_value = constrain(pedal_value, 0, 1) * 0.6;

  return pedal_value;
};
