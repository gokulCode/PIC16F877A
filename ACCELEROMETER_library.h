//#include "I2C_library.h"

////////////////////////////
#define ACCL_DEV_ID 0xD   //
#define ACCL_PID 0x0      //         
////////////////////////////


#define ACCL_X 0
#define ACCL_Y 1
#define ACCL_Z 2
	
void ACCL_UPLOAD(int memoryLoc,int memoryData){
   
	   
	   I2C_START();
	   I2C_ADDRESS(ACCL_DEV_ID,ACCL_PID,WRITE);
	   I2C_WRITE(memoryLoc);
	   I2C_WRITE(memoryData);
	   I2C_STOP();
     I2C_IDLE();
	
}

int ACCL_DOWNLOAD(int memoryLoc){
	
	   int memoryData;

	   I2C_START();
	   I2C_ADDRESS(ACCL_DEV_ID,ACCL_PID,WRITE);
	   I2C_WRITE(memoryLoc);
	   I2C_START();
	   I2C_ADDRESS(ACCL_DEV_ID,ACCL_PID,READ); 
		 memoryData = I2C_READ();
		 I2C_putACK(NACK);
		 I2C_STOP();
	   I2C_IDLE();
	
	   return memoryData;
}

void ACCL_BEGIN(){
	
	  I2C_IDLE();
	  ACCL_UPLOAD(0x6b,0x00);	//PWR_MGMT_1
	  ACCL_UPLOAD(0x6b,0x01);	//
	  ACCL_UPLOAD(0x1a,0x03);	//configuration register
	  ACCL_UPLOAD(0x1b,0x03);	//gyro configuration register
	  ACCL_UPLOAD(0x1c,0xE0);	//accel configuration register
	
}

int ACCL_READ(int axis){
	
	  int ACCL_MSB,ACCL_LSB;
    int ACCL_VALUE;
	  if(axis == ACCL_X){
			  ACCL_MSB = ACCL_DOWNLOAD(0x3B);delay(5);
			  ACCL_LSB = ACCL_DOWNLOAD(0x3C);
		} else if (axis == ACCL_Y){
			  ACCL_MSB = ACCL_DOWNLOAD(0x3D);delay(5);
			  ACCL_LSB = ACCL_DOWNLOAD(0x3E);
		} else if (axis == ACCL_Z){
			  ACCL_MSB = ACCL_DOWNLOAD(0x3F);delay(5);
			  ACCL_LSB = ACCL_DOWNLOAD(0x40);
		}
		
		 ACCL_VALUE = (((ACCL_MSB << 8) | ACCL_LSB ) >> 1 ) & 0x7FFF;
		 return map(ACCL_VALUE,0,32767,-10,10);
}