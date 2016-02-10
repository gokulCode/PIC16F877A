#define WRITE 0
#define READ  1
///////////////////////
#define RTC_ID  0xD  //
#define RTC_PID 0x0  //         // Assign time in 24 hours mode
////////////////////////////////////////////////////////////////////////////////////////////
//char clock[]={ char sec,char min,char hour,char day,char date,char month,char year } ;  //
//                      |        |        |        |        |         |         |         //
  char clock[]={        0,      46,      12,       7,       19,       12,       15 } ;    // 
  unsigned int RTC_TIME[6];    // <= Downloaded time                                      //
  bit PM_AM      ;             // <= PM -> 1   |   AM  -> 0                               //
////////////////////////////////////////////////////////////////////////////////////////////

	
unsigned short int addr_ptr;

char BCDToDecimal (char bcdByte)
{
  return (((bcdByte & 0xF0) >> 4) * 10) + (bcdByte & 0x0F);
}
 
char DecimalToBCD (char decimalByte)
{
  return (((decimalByte / 10) << 4) | (decimalByte % 10));
}
	

	
void RTC_TIME_UPLOAD(unsigned char *clock){

	   SW_I2C_START();
	   SW_I2C_ADDRESS(RTC_ID,RTC_PID,WRITE);  
	   SW_I2C_WRITE(0x00);
	   for(addr_ptr=0;addr_ptr<7;addr_ptr++){
		     SW_I2C_WRITE(DecimalToBCD(clock[addr_ptr]));
		 }
	   SW_I2C_STOP();
	   SW_I2C_IDLE();
}

void RTC_TIME_DOWNLOAD(){
	
	   SW_I2C_START();
	   SW_I2C_ADDRESS(RTC_ID,RTC_PID,WRITE);  
	   SW_I2C_WRITE(0x00);
	   SW_I2C_START();
	   SW_I2C_ADDRESS(RTC_ID,RTC_PID,READ); 
	   for(addr_ptr=0;addr_ptr<7;addr_ptr++){
		     RTC_TIME[addr_ptr]=BCDToDecimal(SW_I2C_READ());
			   SW_I2C_putACK(addr_ptr == 0x06);
		 }
		 SW_I2C_STOP();
	     SW_I2C_IDLE();
		 
		     if (RTC_TIME[2]>=12){
					 if (RTC_TIME[2]>12){
						RTC_TIME[2] = RTC_TIME[2] - 12 ;
					 }
					  PM_AM = 1 ;
         }else{
					  PM_AM = 0 ;
				 }
}


void RTC_DISPLAY(){
    
        LCD_COMMEND(CLEAR_ALL);
        delay(10);
		LCD_LOC(1,1);
        delay(1);
		LCD_PRINT_Number(RTC_TIME[2]);
        delay(1);
		LCD_LOC(1,3);
        delay(1);
		LCD_PRINT(":");
        delay(1);
		LCD_LOC(1,4);
		LCD_PRINT_Number(RTC_TIME[1]);
        delay(1);
		LCD_LOC(1,6);
        delay(1);
		LCD_PRINT(":");
        delay(1);
		LCD_LOC(1,7);
        delay(1);
		LCD_PRINT_Number(RTC_TIME[0]);
        delay(1);
		
		LCD_LOC(1,10);
        delay(1);
		if (PM_AM == 1){
		LCD_PRINT("PM");
        delay(1);
        } else {
	     LCD_PRINT("AM");
         delay(1);
		}
		
		LCD_LOC(2,1);
        delay(1);
		LCD_PRINT_Number(RTC_TIME[4]);
        delay(1);
		LCD_LOC(2,3);
        delay(1);
		LCD_PRINT("/");
        delay(1);
		LCD_LOC(2,4);
        delay(1);
		LCD_PRINT_Number(RTC_TIME[5]);
        delay(1);
		LCD_LOC(2,6);
        delay(1);
		LCD_PRINT("/");
        delay(1);
		LCD_LOC(2,7);
        delay(1);
		LCD_PRINT_Number(RTC_TIME[6]);
        delay(1);
		
		LCD_LOC(2,10);
        delay(1);
		switch (RTC_TIME[3]) {
			case 1 :
				LCD_PRINT("SUN");
			  break;
			case 2 :
				LCD_PRINT("MON");
			  break;
			case 3 :
				LCD_PRINT("TUE");
			  break;
			case 4 :
				LCD_PRINT("WED");
			  break;
			case 5 :
				LCD_PRINT("THU");
			  break;
			case 6 :
				LCD_PRINT("FRI");
			  break;
			case 7 :
				LCD_PRINT("SAT");
			  break;
		}
}

/*
#include <pic.h>
#include <math.h>
#include "utility.h"
#include "LCD_library.h"
#include "I2C_library.h"
#include "RTC_library.h"

int s;
void main(){
   	SW_I2C_IDLE();
	
	LCD_BEGIN();
	LCD_COMMEND(CLEAR_ALL);
	
	LCD_LOC(1,1);
	LCD_PRINT(" ");
	LCD_LOC(1,1);
	LCD_PRINT("UPLOARDING DATE");
	
	delay(1000);
   RTC_TIME_UPLOAD(clock);
	
	while(1){
		
    RTC_TIME_DOWNLOAD();

        LCD_COMMEND(CLEAR_ALL);
        delay(10);
		LCD_LOC(1,1);
        delay(1);
		LCD_PRINT_Number(RTC_TIME[2]);
        delay(1);
		LCD_LOC(1,3);
        delay(1);
		LCD_PRINT(":");
        delay(1);
		LCD_LOC(1,4);
		LCD_PRINT_Number(RTC_TIME[1]);
        delay(1);
		LCD_LOC(1,6);
        delay(1);
		LCD_PRINT(":");
        delay(1);
		LCD_LOC(1,7);
        delay(1);
		LCD_PRINT_Number(RTC_TIME[0]);
        delay(1);
		
		LCD_LOC(1,10);
        delay(1);
		if (PM_AM == 1){
		LCD_PRINT("PM");
        delay(1);
        } else {
	     LCD_PRINT("AM");
         delay(1);
		}
		
		LCD_LOC(2,1);
        delay(1);
		LCD_PRINT_Number(RTC_TIME[4]);
        delay(1);
		LCD_LOC(2,3);
        delay(1);
		LCD_PRINT("/");
        delay(1);
		LCD_LOC(2,4);
        delay(1);
		LCD_PRINT_Number(RTC_TIME[5]);
        delay(1);
		LCD_LOC(2,6);
        delay(1);
		LCD_PRINT("/");
        delay(1);
		LCD_LOC(2,7);
        delay(1);
		LCD_PRINT_Number(RTC_TIME[6]);
        delay(1);
		
		LCD_LOC(2,10);
        delay(1);
		switch (RTC_TIME[3]) {
			case 1 :
				LCD_PRINT("SUN");
			  break;
			case 2 :
				LCD_PRINT("MON");
			  break;
			case 3 :
				LCD_PRINT("TUE");
			  break;
			case 4 :
				LCD_PRINT("WED");
			  break;
			case 5 :
				LCD_PRINT("THU");
			  break;
			case 6 :
				LCD_PRINT("FRI");
			  break;
			case 7 :
				LCD_PRINT("SAT");
			  break;
		}
		
		delay(1000);

	}
}
 */
