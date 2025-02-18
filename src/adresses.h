/*
*
*   This file includes all of the can addresses needed for can
*   commucation with prohelion devices
*
*/

// Driver controls CAN base address and packet offsets
#define DC_CAN_BASE		              0x500
#define DC_DRIVE		                1
#define DC_POWER		                2
#define DC_RESET		                3
#define DC_SWITCH		                5
#define DC_BOOTLOAD		              22    

// Device serial number
#define DEVICE_ID		                0x1002

// Motor controller CAN base address and packet offsets
#define	MC_CAN_BASE		              0x400		// High = Serial Number             Low = "TRIa" string
#define MC_LIMITS		                0x01		// High = Active Motor/CAN counts   Low = Error & Limit flags
#define	MC_BUS			                0x02		// High = Bus Current               Low = Bus Voltage
#define MC_VELOCITY		              0x03		// High = Velocity (m/s)            Low = Velocity (rpm)
#define MC_PHASE		                0x04		// High = Phase A Current           Low = Phase B Current
#define MC_V_VECTOR		              0x05		// High = Vd vector                 Low = Vq vector
#define MC_I_VECTOR		              0x06		// High = Id vector                 Low = Iq vector
#define MC_BEMF_VECTOR	            0x07		// High = BEMFd vector              Low = BEMFq vector
#define MC_RAIL1		                0x08		// High = 15V                       Low = Unused
#define MC_RAIL2		                0x09		// High = 3.3V                      Low = 1.9V
#define MC_FAN			                0x0A		// High = Reserved                  Low = Reserved
#define MC_TEMP1		                0x0B		// High = Heatsink Phase C Temp     Low = Motor Temp
#define MC_TEMP2		                0x0C		// High = Heatsink Phase B Temp     Low = CPU Temp
#define MC_TEMP3		                0x0D		// High = Heatsink Phase A Temp     Low = Unused
#define MC_CUMULATIVE	              0x0E		// High = DC Bus AmpHours           Low = Odometer

//BMU Addresses
#define BMU_BASE                    0x600
#define PACK_SOC                    (BMU_BASE + 0x0F4)
#define BALANCE_SOC                 (BMU_BASE + 0x0F5)
#define PACK_STATUS                 (BMU_BASE + 0x0FB)
#define PRECHARGE_STATUS            (BMU_BASE + 0x6f7)

//BMU Pins
#define BMU_FAULTLED_PIN            53
