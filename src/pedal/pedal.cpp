#include <Arduino.h>
#include "pedal.h"


//DESC:     updates the pedal value in the drive object
//INPUT:    pass by reference the drive object
//OUT:      the pedal member of drive will be written to,
//          the reversed member of drive will be read from
void update_drive_pedal(){

    int max = analogRead(ACC_BASELINE) * 0.9;
    int min = ACC_PEDAL_MIN;

    float pedalValue = analogRead(ACC_PEDAL);
    //Serial.println(pedalValue);   //DEBUG

    //scale down to between 0 and 1
    pedalValue -= min;
    pedalValue /= max-min;

    Serial.print(analogRead(ACC_PEDAL));
    Serial.print(" | ");
    Serial.print(analogRead(ACC_BASELINE));
    Serial.print(" | ");
  

    pedalValue = 1 - pedalValue;
    pedalValue = constrain(pedalValue, 0, 1) * 0.6;

    Serial.println(pedalValue);

    //update pedal value
    drive.pedal = pedalValue;
    return;
};

