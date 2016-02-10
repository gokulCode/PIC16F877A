#include <stdlib.h> 

#define OUTPUT 0
#define INPUT  1

#define RELAY_ON   0
#define RELAY_OFF  1

#define Nop() {_asm nop _endasm}
//////////////////////////////////////////
#define OP_FREQ 4000000              //
//////////////////////////////////////////        
#define MS_PERIODE OP_FREQ/60000      //
#define US_PERIODE MS_PERIODE/1000        //
//////////////////////////////////////////

// Delay Function
void delay(int periode_MS){
	
	int i,j;
	for(j=0;j<periode_MS;j++)
    for(i=0;i<MS_PERIODE;i++){
   }
}

void delay_us(int periode_US){

// 1us -> 63 ms
    	int i,j;
	for(j=0;j<periode_US;j++)
    for(i=0;i<=US_PERIODE;i++){
   }
}
///*
// Random Number Generator with in range
unsigned int random(unsigned int min, unsigned int max)
{
    int r;
     unsigned int range = 1 + max - min;
     unsigned int buckets = RAND_MAX / range;
     unsigned int limit = buckets * range;

    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}


// Push Button Switch Latch
int button (int button){
	  static int lastState=0;
	  static int state = 0 ;

	  if ((button==1) & (lastState==0)){
		   state = ~state;
			 delay(10);
    }
		lastState = button;
	  return state ;
}

// Push Button counter
int CounterUPDOWN (int buttonInc,int buttonDec){
	  
	  static int lastStateInc = 0;
	  static int lastStateDec = 0;
	  
	  static int state = 0 ;

	  if ((buttonInc==1) & (lastStateInc==0)){
		   state = state+1;
			 delay(10);
    }
		
		if ((buttonDec==1) & (lastStateDec==0)){
		   state = state-1;
			 delay(10);
    }
		
		lastStateInc = buttonInc;
		lastStateDec = buttonDec;
		
	  return state ;
}

// Adjestment of variable Range
int map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// variable Limiting in Range
int constrain(int value,int minVal, int maxVal){

      int limitRange ;
	
	    if (value < minVal) {
			    limitRange = minVal;
      }
		  else if (value > maxVal) {
			    limitRange = maxVal;
      }
			else {
				  limitRange = value;
			}
		
			return limitRange;

}

int STRING2Number(char a[]) {
  int c, sign, offset, n;
 
  if (a[0] == '-') {  // Handle negative integers
    sign = -1;
  }
 
  if (sign == -1) {  // Set starting position to convert
    offset = 1;
  }
  else {
    offset = 0;
  }
 
  n = 0;
 
  for (c = offset; a[c] != '\0'; c++) {
    n = n * 10 + a[c] - '0';
  }
 
  if (sign == -1) {
    n = -n;
  }
 
  return n;
}

//*/
