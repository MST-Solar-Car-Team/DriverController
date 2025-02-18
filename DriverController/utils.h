#include <Arduino.h>
#include "due_can.h"

#define ACC_PEDAL_MIN 510
#define ACC_PEDAL_MAX 950
#define VELOCITY_MAX  9000

//inputs
#define ACC_PEDAL              A0
#define BREAK_PEDAL            84
#define DRIVE_DIRECTION_SWITCH 21  //High for reverse, Low for forward
#define TURN_LEFT_BUTTON       20
#define TURN_RIGHT_BUTTON      132

//outputs
#define HEADLIGHTS          65
#define BLINKER_LEFT        67
#define BLINKER_RIGHT       71
#define BREAKLIGHT          101
#define STROBELIGHT         55

//CAN addresses
#define DRIVE_FRAME_ID      0x501
#define POWER_FRAME_ID      0x502

struct driveState {
    CAN_FRAME driveFrame; //contains the current status of the drive frame that is sent to the motor controller
    CAN_FRAME powerFrame; //contains the current status of the power frame that is sent to the motor controller
    uint32_t busCurrent = 1.0;  //drawn current from the power bus according to current limit
    
    float pedal;       //floating point value between 0 and 1
    bool reversed;        //true -> driving in reverse; false -> driving forward
    bool BPSfault;        //true -> fault
    bool blink_left;      //true -> flash left blinker
    bool blink_right;     //true -> flash right blinker
    bool breaking;        //true -> break pedal applied, turn on break lights
    
};

struct blinkerState {
  bool blink_left;      //current state of the left blinker
  bool blink_right;     //current state of the right blinker
};

void pinInit() {

    //set input pins
    pinMode(ACC_PEDAL, INPUT);
    pinMode(BREAK_PEDAL, INPUT);
    pinMode(TURN_LEFT_BUTTON, INPUT);
    pinMode(TURN_RIGHT_BUTTON, INPUT);
    pinMode(DRIVE_DIRECTION_SWITCH, INPUT);

    //set output pins
    pinMode(HEADLIGHTS, OUTPUT);
    pinMode(BLINKER_LEFT, OUTPUT);
    pinMode(BLINKER_RIGHT, OUTPUT);
    pinMode(BREAKLIGHT, OUTPUT);
    pinMode(STROBELIGHT, OUTPUT);

};

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

//DESC:     updates the blinker states in the drive struct
void update_drive_blinkers(driveState &drive){
   if(digitalRead(TURN_LEFT_BUTTON)){
    drive.blink_left = true;
   } else {
    drive.blink_left = false;
   }

   if(digitalRead(TURN_RIGHT_BUTTON)){
    drive.blink_right = true;
   } else {
    drive.blink_right = false;
   }
};

void update_drive_frame(driveState &drive) {
  drive.driveFrame.id = DRIVE_FRAME_ID;
  drive.driveFrame.length = 8;
  drive.driveFrame.data.high = drive.pedal;
  drive.driveFrame.data.low = VELOCITY_MAX;
};

void update_power_frame(driveState &drive) {
  drive.driveFrame.id = POWER_FRAME_ID;
  drive.driveFrame.length = 8;
  drive.driveFrame.data.high = drive.busCurrent;
  drive.driveFrame.data.low  = 0;
};
