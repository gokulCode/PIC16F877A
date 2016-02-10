#define BUFFER_SIZE 15
#define SERIAL_TIMEOUT 0

#define NEW_LINE        0x0A
#define CARRIAGE_RETRUN 0x0D
#define HARZ_TAB        0x09
#define VERT_TAB        0x0B
#define BACKSPACE       0x08
#define CTRL_Z          0x1A

#define ENABLE          1
#define DISABLE         0

int fifo=0;

void SERIAL_RECEIVE(char enable){
     RCIE = enable;			 
}

void BAUDRATE(unsigned long int baud){

	if(baud==110)			  //*Crystal Freq 1 Mhz*
	{                         //
		SPBRG = 141;          // for 110 baud rate
		BRGH = 0;		      // baud rate low		
	}                         //
	else if(baud==1200)		  //*Crystal Freq 4 Mhz*
	{                         //
		SPBRG = 51;           // for 1200 baud rate
		BRGH = 0;		      // baud rate high		
	}                         //
	else if(baud==2400)       //
	{                         //
		SPBRG = 25;           // for 2400 baud rate
		BRGH = 0;		      // baud rate high		
	}                         //
	else if(baud==4800)       //
	{                         //
		SPBRG = 12;           // for 4800 baud rate
		BRGH = 0;		      // baud rate high		
	}                         //
	else if(baud==9600)       //
	{                         //
		SPBRG = 25;           // for 9600 baud rate
		BRGH = 1;		      // baud rate high		
	}                         //
	else if(baud==57600)      //
	{                         //
		SPBRG = 20;           // for 57600 baud rate
		BRGH = 1;		      // baud rate high		
	}                         //
	else if(baud==115200)     //
	{                         //
		SPBRG = 10;           // for 115200 baud rate
		BRGH = 1;		      // baud rate high		
	}	
}

void SERIAL_BEGIN(unsigned long int baudRate){
    BAUDRATE(baudRate);
	SYNC = 0;		     // asynchronous mode
	SPEN = 1;		     // serial port enable
	TXEN = 1;		     // tx enable
	GIE=1;
	PEIE=1;
    CREN = 1;
	SERIAL_RECEIVE(ENABLE);
}

void SERIAL_WRITE(char CMD){
     	   
	      	TXREG = CMD;
			while(!TXIF);
			TXIF = 0;
	       
}

void SERIAL_PRINT(char *STRING){
     	
	     int i;
	 for(i=0;STRING[i]!='\0';i++){
         SERIAL_WRITE(STRING[i]);
	 }	 
}


void SERIAL_PRINT_Number(int num){
	
	int i;
	char BCD[5];
	unsigned int len;
	
	len = log10(num);
	for(i=0;i<=len;i++){
	     BCD[i] = num%10;
	     num = num/10;
    }

	if(num<0){
		num = abs(num);
	    SERIAL_WRITE('-');			
	}

    for(i=0;i<=len;i++){
		SERIAL_WRITE(BCD[len-i]+0x30);
    }	
}     

void SERIAL_DECIMAL3(unsigned int num)
{
	unsigned char _100s,_10s,_1s;
	_100s=((num%1000))/100;
	 _10s=((num%100))/10;
	  _1s=num%10;
	SERIAL_WRITE(_100s+0x30);
	SERIAL_WRITE(_10s+0x30);
	SERIAL_WRITE(_1s+0x30);
}   
    
/*
char* SERIAL_READ_REQ(int requied){
  
	//char *recData = malloc(sizeof(char) * requied);
	static char recData[5];
	RI = 0;
	for(fifo=0;fifo<requied;fifo++){
	       while(!RI);
		     recData[fifo]=SBUF;
		     RI = 0 ;
		     
	}

		return recData;
}
*/
static char SERIAL_REC[BUFFER_SIZE];
short int SERIAL_AVAILABLE = 0 ;

void serialInterrupt() {

	SERIAL_RECEIVE(ENABLE);
	
	if (SERIAL_AVAILABLE<=0){
       for(fifo=0;fifo<BUFFER_SIZE;fifo++){
          SERIAL_REC[fifo]=0;
       }
    }

	do{
	    SERIAL_REC[SERIAL_AVAILABLE]=RCREG;
		SERIAL_AVAILABLE ++ ;
		delay_us(SERIAL_TIMEOUT);
      }while(RCIF==1);
		 //while(SERIAL_REC[i-1]!=13);

	SERIAL_RECEIVE(ENABLE);
 
}

char SERIAL_READ(){
	
  char popData;
	while(SERIAL_AVAILABLE==0);
	popData = SERIAL_REC[0];
    
	for(fifo=0;fifo<SERIAL_AVAILABLE;fifo++){
		SERIAL_REC[fifo-1] = SERIAL_REC[fifo];
	}
	
	SERIAL_AVAILABLE-- ;
	if (SERIAL_AVAILABLE<=0){
		  SERIAL_AVAILABLE=0;
  }
	
	return popData;
}

//void interrupt ISR(){
/////// SERIAL RECEIVER ///////
//    if(RCIF==1){           //
//       RCIF = 0;           //
//       serialInterrupt();  //
//    }                      //
///////////////////////////////
//}

/* Document
   
   Function :
   
   1.SERIAL_BEGIN()               // initialize serial communication
   2.SERIAL_WRITE(char CMD)       // send single char
   3.SERIAL_PRINT(char *STRING)   // send char array (string)
   4.SERIAL_PRINT_Number(int num) // send signed number  
   5.SERIAL_READ_REQ(int requied) // requied-no.of requst char | return char array 
   6.SERIAL_READ()                // return last serial buffer value(single char)
   7.SERIAL_AVAILABLE             // no.of serial received stack buffer size 
   8.BUFFER_SIZE                  // serial buffer size

*/