#include "due_can.h"
#include <Arduino.h>
#include "pedal.h"
#include "can.h"
#include <cstdint>
#include <cstring>

using namespace std;

//GETS THE DRIVE COMMAND OBJECT FROM SOLAR_DRIVER
extern _drive_command drive;

//function declarations
void pinInit();
void send_can();
void driveToFrame(CAN_FRAME& frame);
void receiveCAN();
void updateSwitches();

void setup() {
  
  Serial.begin(250000);

  //begins both of the CanBus connections
  Can0.begin(CAN_BPS_500K, 255);
  Can1.begin(CAN_BPS_500K, 255);

  //will accept frames with any id through
  Can0.watchFor();
  Can0.setWriteID(0x500);
  Can0.setBigEndian(true);

  pinInit();

  //initialize drive
  drive.state = MODE_OFF;
  drive.bus_current = 1;
  drive.flags = 0x00;
  drive.rpm = 0;
  drive.current = 0;

  calibratePedal();

}

void pinInit(){
  //pedal initialization
  pinMode(PEDAL_SIGNAL_PIN, INPUT);

  //gear Buttons
  //due has pullup resistor on digital input, INPUT_PULLUP is for capatability with future boards
  pinMode(GEAR_HIGH_PIN, INPUT_PULLUP);
  pinMode(GEAR_LOW_PIN, INPUT_PULLUP);

  //BMS FAULT INDICATOR LIGHT
  pinMode(BMU_FAULTLED_PIN, OUTPUT);
}


//RTR Packets:
//  CAN_BASE: device ID 
//  DRIVE:    drive command
//  POWER:    bus current
//  SWITCH:   switch state

void loop() {

  drive.state = MODE_DH;
  process_pedal();

  //DEBUG
  Serial.print("CURRENT: ");
  Serial.println(drive.current);

  //update mode
  if(!digitalRead(GEAR_HIGH_PIN)){
    drive.state = MODE_DH;
  }
  if(!digitalRead(GEAR_LOW_PIN)){
    drive.state = MODE_DL;
  }

  //call can communications every 100ms
  if(millis()%100 == 0){
    //TODO: check that the canbus is ok
    send_can();
  }

  //handle CAN messages received on the bus if there are any
  if(Can0.rx_avail()){
    receiveCAN();
  }


}

//send following frames onto the canbus @ 10hz:
//  drive command         
//  bus current           
//  switches - 
//      command.state
//      command.flags
//  ID @ 1hz
int IdCommCount = 0;
void send_can(){

  CAN_FRAME frame;
  
  if(IdCommCount >= 10){
    //Send ID Frame
    frame.id = DC_CAN_BASE;
    frame.length = 8;
    frame.extended = false;
    frame.data.bytes[7] = 'T';
    frame.data.bytes[6] = '0';
    frame.data.bytes[5] = '8';
    frame.data.bytes[4] = '6';
    frame.data.bytes[3] = 0;
    frame.data.bytes[2] = 0;
    frame.data.bytes[1] = 0;
    frame.data.bytes[0] = DEVICE_ID;

    Can0.sendFrame(frame);

    IdCommCount = 0;
  } else {
    IdCommCount++;
  }
 


  //send drive command
  driveToFrame(frame);
  Can0.sendFrame(frame);

  //send bus command frame 
  
  frame.id = DC_CAN_BASE + DC_POWER;
  frame.length = 8;
  frame.extended = false;

  frame.data.bytes[0] = 0;
  frame.data.bytes[1] = 0;
  frame.data.bytes[2] = 0;
  frame.data.bytes[3] = 0;
  frame.data.bytes[4] = 0;
  frame.data.bytes[5] = 0;
  frame.data.bytes[6] = 0;
  frame.data.bytes[7] = 0;

  float currValue = 1.0;

  memcpy(&frame.data.high, &currValue, sizeof(currValue));

  Can0.sendFrame(frame);

  //send switch state
  
  frame.id = DC_CAN_BASE + DC_SWITCH;
  frame.length = 8;
  frame.extended = false;

  frame.data.bytes[0] = drive.switches;
  frame.data.bytes[1] = 0;
  frame.data.bytes[2] = 0;
  frame.data.bytes[3] = 0;
  frame.data.bytes[4] = 0;
  frame.data.bytes[5] = 0;
  frame.data.bytes[6] = drive.flags;
  frame.data.bytes[7] = drive.state;
  Can0.sendFrame(frame);
 
}

//Purpose:    inputs the drive command members into
//            the CAN_FRAME argument.
void driveToFrame(CAN_FRAME& frame){

  frame.id = (DC_CAN_BASE + DC_DRIVE);
  frame.length = 8;
  frame.extended = false;

  frame.data.bytes[0] = 0;
  frame.data.bytes[1] = 0;
  frame.data.bytes[2] = 0;
  frame.data.bytes[3] = 0;
  frame.data.bytes[4] = 0;
  frame.data.bytes[5] = 0;
  frame.data.bytes[6] = 0;
  frame.data.bytes[7] = 0;

  //using memcpy to convert and input the RPM and Current into frame data
  memcpy(&frame.data.high, &drive.current, sizeof(drive.current));
  memcpy(&frame.data.low, &drive.rpm, sizeof(drive.current));
  
  return;

}

void receiveCAN(){
  CAN_FRAME received;
  Can0.read(received);

  switch(received.id){
    case PRECHARGE_STATUS:
      if(received.data.bytes[1] == 0){
        //BMS ERROR/FAULT
        digitalWrite(BMU_FAULTLED_PIN, HIGH);
      } else {
        digitalWrite(BMU_FAULTLED_PIN, LOW);
      }
      break;
  }

}

//PURPOSE:  update the switches bitfeild
//
//TODO:     currently just setting switches to run
//          update switches to current mode 
void updateSwitches(){
  drive.switches = 0x0070;
}


