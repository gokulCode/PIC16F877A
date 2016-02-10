#define SDA RB2
#define SCL RB3

#define SDA_DIR TRISB2
#define SCL_DIR TRISB3

#define CLK_DELAY 1   // SCL clk delay

int i;

void SW_I2C_IDLE(){

      SDA_DIR = 0;
      SCL_DIR = 0;

	  SDA = 1 ;
	  SCL = 1 ;
}

void SW_I2C_START(){

      SDA_DIR = 0;
	  SDA = 1 ;
	  SCL = 1 ;
      delay(CLK_DELAY);
	  SDA = 0 ;
	  SCL = 0 ;
      delay(CLK_DELAY);
}

void SW_I2C_STOP(){

      SDA_DIR = 0;
	  SDA = 0 ;
	  SCL = 1 ;
      delay(CLK_DELAY);
	  SDA = 1 ;
}

void SW_I2C_CLK(){
	  SCL = 1 ;
	  delay(CLK_DELAY);
	  SCL = 0 ;
	  delay(CLK_DELAY);
}

void SW_I2C_putACK(char ack){ 
       
       SDA_DIR = 0;
       delay(CLK_DELAY);
	   SDA = ack ;
	   SW_I2C_CLK();
      

		 
}


void SW_I2C_WRITE(char frame){

	    SDA_DIR = 0;
	do{
	  for(i=7;i>=0;i--){
			SDA = ( frame >> i ) & 1;
			SW_I2C_CLK();
		}
//// ACK CHECK ////////
		  SDA = 1 ;  //
          SDA_DIR = 1 ;
		  SCL = 1 ;  //
	    delay(CLK_DELAY);    //
	}while(SDA == 1);//
        SCL = 0 ;    //
	    delay(5);    //
///////////////////////
}

char SW_I2C_READ(){
	
	static char frame = 0 ;
    SDA_DIR = 0;
	SDA = 1 ;
    SDA_DIR = 1;
	frame = 0 ;
	
		for(i=7;i>=0;i--){
	
     			SCL = 1 ;      
	            delay(CLK_DELAY);       
			
				if (SDA == 1){                 
					frame = frame | ( 1 << i );   
				}                              
				                               
  				SCL = 0 ;      
			  	delay(CLK_DELAY);  
		}
		SDA_DIR = 0;
		return frame;
}

void SW_I2C_ADDRESS(char DEVICE_ADDR ,char SPECIFIC_ADDR,char WR) {
		
		char addr_frame;

    addr_frame = ( DEVICE_ADDR << 4 ) | ( SPECIFIC_ADDR << 1) | WR ;
		
	  SW_I2C_WRITE(addr_frame);
}