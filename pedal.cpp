#include "pedal.h"
#include <Arduino.h>

// PUBLIC GLOBAL VARIABLE FOR THE DRIVE COMMAND
_drive_command drive;

void process_pedal(){

    //TODO: process error flags

    //if there are no error flags, get and set current and rpm
    if(drive.flags == 0x00){

      //get analog value of the potentiometer
      float pedal = analogRead(PEDAL_SIGNAL_PIN);

      //scale pedal backwards, because potentiometer is on the pedal backwards
      pedal *= -1;
      pedal += PEDAL_TRAVEL_MAX;

      //scale down pedal to 0 - 1
      pedal -= PEDAL_TRAVEL_MIN;
      pedal /= 428;

      switch(drive.state){
        case MODE_R:
          drive.current = pedal;
          drive.rpm = RPM_REV_MAX;
          break;
        case MODE_DL:
          //scale down to 0 - 0.5
          pedal /= 2;
        case MODE_DH:
          if(pedal <= 0.01){
            pedal = 0;
          }

          drive.current = pedal;
          drive.rpm = RPM_FWD_MAX;
          break;
        case MODE_CHARGE:
        case MODE_N:
        case MODE_START:
        case MODE_ON:
        case MODE_OFF:
        default:
          drive.current = 0.0;
          drive.rpm = 0.0;
          break;
      }

    } else {
        //a pedal fault was detected
        Serial.println("PEDAL FAULT DETECTED");
        drive.current = 0.0;
        drive.rpm = 0.0;
    }
}

//Purpose: zeros the pedal to whatever is currently being read.
//
//Pre:     Foot must be completly off the pedal when pedal is calibrated.
void calibratePedal() {

  float pedal = analogRead(PEDAL_SIGNAL_PIN);
  #define PEDAL_TRAVEL_MIN  pedal;

}