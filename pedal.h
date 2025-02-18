typedef struct _drive_command {
  float rpm;
	float current;
	float bus_current;
	unsigned char flags;
	unsigned char state;
  unsigned int  switches;
} drive_command;

extern drive_command drive;

// Error flags
#define FAULT_ACCEL_LOW			    0x01
#define FAULT_ACCEL_HIGH		    0x02
#define FAULT_ACCEL_MISMATCH	  0x04
#define FAULT_REGEN_LOW			    0x10
#define FAULT_REGEN_HIGH		    0x20

// Command parameter limits
#define CURRENT_MAX				      1.0					// %, absolute value
#define REGEN_MAX				        1.0					// %, absolute value
#define RPM_FWD_MAX				      4000				// Forwards max speed, rpm
#define RPM_REV_MAX				      -4000				// Reverse max speed, rpm

// Pedal input scale
// ADC resolution 0-1023
#define PEDAL_TRAVEL_MIN        680
#define PEDAL_TRAVEL_MAX        1003

//analog signal pin for reading from the pedal
#define PEDAL_SIGNAL_PIN        54

//gear selection pins/ toggling
#define GEAR_HIGH_PIN   22
#define GEAR_LOW_PIN    24

//PURPOSE: reads the analog value from the signal pin
//         clamps the analog value inside of pedal travel
//         updates the rpm and current members of the drive command
//         
//NOTE:    In the current state of the implementation we will not check for errors with the pedal travel     
//		   TODO - toggle into cruise control mode when cruise control is active on the switches    
void process_pedal();

//PURPOSE: sets the PEDAL_TRAVEL_MIN define to current pedal value
void calibratePedal();

// Drive command states
#define MODE_OFF			  0
#define MODE_ON				  1
#define MODE_START			2
#define MODE_R				  3
#define MODE_N				  4
#define MODE_BL				  5
#define MODE_DL				  6
#define MODE_CHARGE			7
#define MODE_BH				  8
#define MODE_DH				  9

//All of the modes for the switch bitfield
#define SW_MODE_R		    0x0001
#define SW_MODE_N		    0x0002
#define SW_MODE_B		    0x0004
#define SW_MODE_D		    0x0008
#define SW_IGN_ACC		  0x0010
#define SW_IGN_ON		    0x0020
#define SW_IGN_START	  0x0040
#define SW_BRAKE		    0x0080
#define SW_FUEL			    0x0100
#define SW_SPARE1		    0x0200
#define SW_SPARE2		    0x0400
#define SW_SPARE3		    0x0800
#define SW_ACCEL_FAULT	0x1000
#define SW_CAN_FAULT	  0x2000
#define SW_BRAKE_FAULT	0x4000
#define SW_REV_FAULT	  0x8000

