#define OPEN    1
#define CLOSE   0

#ifndef FORWARD
#define FORWARD 0
#define REVERSE 1
#define STOP    2
#define LEFT    3
#define RIGHT   4
#endif

#define GATE_MOTOR_P RB5
#define GATE_MOTOR_N RB6

#define GATE_TOP_LIMIT    RD0
#define GATE_BUTTOM_LIMIT RD1
///////////////////////////////
#define GATE_MOTOR_P_DIR TRISB5
#define GATE_MOTOR_N_DIR TRISB6

#define GATE_TOP_LIMIT_DIR    TRISD0
#define GATE_BUTTOM_LIMIT_DIR TRISD1


void GATE_MOTOR_OPERATION(int oper){
		if (oper == FORWARD){
			GATE_MOTOR_P = 0;
			GATE_MOTOR_N = 1;
		}else if (oper == REVERSE){
			GATE_MOTOR_P = 1;
			GATE_MOTOR_N = 0;
		}else{
			GATE_MOTOR_P = 1;
			GATE_MOTOR_N = 1;
	  }	
}

void GATE_OPERATION(int oper){
	  if(oper == OPEN){
			GATE_MOTOR_OPERATION(FORWARD);
			while(GATE_TOP_LIMIT == 1);
			GATE_MOTOR_OPERATION(STOP);
		}else{
			GATE_MOTOR_OPERATION(REVERSE);
			while(GATE_BUTTOM_LIMIT == 1);
			GATE_MOTOR_OPERATION(STOP);
		}
}

void GATE_MODEL_BEGIN(){
    GATE_MOTOR_P_DIR = OUTPUT ;
    GATE_MOTOR_N_DIR = OUTPUT ;
    
    GATE_TOP_LIMIT_DIR = INPUT;
    GATE_BUTTOM_LIMIT_DIR = INPUT;
}

void GATE_MODEL_OPEN_CLOSE(){
      LCD_CLEAR();
      LCD_LOC(1,1);LCD_PRINT("   GATE OPEN    ");
      GATE_OPERATION(OPEN);
      LCD_LOC(1,1);LCD_PRINT("  * WELCOMES *  ");
      delay(2000);
      LCD_LOC(1,1);LCD_PRINT("   GATE CLOSE    ");
      GATE_OPERATION(CLOSE);
}