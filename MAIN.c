#include <pic.h>
#include "math.h"
#include "utility.h"
#include "LCD_library.h"
#include "ADC_library.h"

#define _XTAL_FREQ   4000000 


void main(){
 
    ADC_config(0x00);
    LCD_BEGIN();
    LCD_LOC(1,1);LCD_PRINT("    PROJECT     ");
    LCD_LOC(2,1);LCD_PRINT("     TITLE      ");
    delay(1000);
    
	while(1){
		
	}
}