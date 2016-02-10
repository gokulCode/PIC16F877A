#define RF0_pin RC0 
#define RF1_pin RC1 
#define RF2_pin RC2 
#define RF3_pin RC3 

#define RF0_dir TRISC0 
#define RF1_dir TRISC1 
#define RF2_dir TRISC2 
#define RF3_dir TRISC3

void RFTX_BEGIN(){
    RF0_dir = OUTPUT;
    RF1_dir = OUTPUT;
    RF2_dir = OUTPUT;
    RF3_dir = OUTPUT;
}

void RF_SEND(unsigned char chr){
		
	RF0_pin = chr      & 1 ;
	RF1_pin = chr >> 1 & 1 ;
	RF2_pin = chr >> 2 & 1 ;
	RF3_pin = chr >> 3 & 1 ;

}