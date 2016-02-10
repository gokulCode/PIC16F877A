
#define SET_PIN RB0
#define MOV_PIN RB1
#define INC_PIN RB2
#define DEC_PIN RB3
#define ENT_PIN RB4

#define SET_DIR TRISB0
#define MOV_DIR TRISB1
#define INC_DIR TRISB2
#define DEC_DIR TRISB3
#define ENT_DIR TRISB4

int  KP5_MOV = 0 ;
int  KP5_INC_DEC_COUNT = 0 ;
char KP5_FILL[10+1]="0000000000";

char mov_state = -1;

char movCounter(char button,int length){
	  static char lastState=0;

	  if ((button==1) & (lastState==0)){
		   mov_state = mov_state + 1;
			 delay(10);
      }

      if (mov_state >= length){
          mov_state = 0;
      }
		lastState = button;
   
	  return mov_state ;
}

void INC_DEC_Counter (char buttonInc,char buttonDec,char *max_limit){
	  
	  static char lastStateInc = 1;
	  static char lastStateDec = 1;

	  	if ((buttonInc==0) & (lastStateInc==1)){
		   KP5_FILL[KP5_MOV] = KP5_FILL[KP5_MOV]+1;
           if(KP5_FILL[KP5_MOV]>max_limit[KP5_MOV]){
             KP5_FILL[KP5_MOV] = '0' ;
           }
           LCD_WRITE(KP5_FILL[KP5_MOV]);
			 delay(10);
             
    	}
		
		if ((buttonDec==0) & (lastStateDec==1)){
		   KP5_FILL[KP5_MOV] = KP5_FILL[KP5_MOV]-1;
           if(KP5_FILL[KP5_MOV]<'0'){
           KP5_FILL[KP5_MOV] = max_limit[KP5_MOV];
		   }
           LCD_WRITE(KP5_FILL[KP5_MOV]);
			 delay(10);
    	}
		lastStateInc = buttonInc;
		lastStateDec = buttonDec;
}


char* Number2STRING(int num,char len){
	  int i;
	  char BCD[10+1];

	  for(i=0;i<=len;i++){
			 BCD[len-i-1] = num%10;
			   num = num/10;
    }	
		BCD[len] = 0;
		return BCD;
}

void KEYPAD5_BEGIN(){
      SET_DIR = INPUT ;
      MOV_DIR = INPUT ;
      INC_DIR = INPUT ;
      DEC_DIR = INPUT ;
      ENT_DIR = INPUT ;
              
	  SET_PIN = 1;
	  MOV_PIN = 1;
	  INC_PIN = 1;
	  DEC_PIN = 1;
	  ENT_PIN = 1;
}

char* KEYPAD5(int lcd_x,int lcd_y,int length ,char *max_Limit){

	  int i;
	
	  for(i=0;i<length;i++){
			KP5_FILL[i] = '0';
		}			
		KP5_FILL[length] = 0;
		
    LCD_LOC(lcd_x,lcd_y);
    LCD_PRINT(KP5_FILL);
    LCD_COMMEND(CURSOR_ON);
    LCD_COMMEND(AUTO_INC_OFF);
	
    do{
       LCD_LOC(lcd_x,lcd_y+KP5_MOV);
       KP5_MOV = movCounter(MOV_PIN,length) ;
 	   INC_DEC_Counter(INC_PIN,DEC_PIN,max_Limit);
    }while(ENT_PIN==1);
     while(ENT_PIN == 0);
	KP5_FILL[length] = 0 ;
    mov_state = 0;
    LCD_COMMEND(CURSOR_OFF);
    LCD_COMMEND(AUTO_INC_ON);
		return KP5_FILL;

}