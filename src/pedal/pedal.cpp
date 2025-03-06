#include <Arduino.h>
#include "pedal.h"


//DESC:     updates the pedal value in the drive object
//INPUT:    pass by reference the drive object
//OUT:      the pedal member of drive will be written to,
//          the reversed member of drive will be read from
void update_drive_pedal(driveState &drive){

    int max = ACC_PEDAL_MAX;
    int min = ACC_PEDAL_MIN;

    float pedalValue = analogRead(ACC_PEDAL);
    //Serial.println(pedalValue);   //DEBUG

    //scale down to between 0 and 1
    pedalValue -= min;
    pedalValue /= max-min;

    Serial.print(analogRead(ACC_PEDAL));
    Serial.print(" | ");
    Serial.println(1-pedalValue);

    if(pedalValue < 0){
      pedalValue = 0;
    }

    //check for reverse
    if(drive.reversed){
      pedalValue *= -1;
    }

    //update pedal value
    drive.pedal = 1-pedalValue;
    return;
};

