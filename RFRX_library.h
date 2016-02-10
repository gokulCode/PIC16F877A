#define RF0_pin RC3 
#define RF1_pin RC2 
#define RF2_pin RC1 
#define RF3_pin RC0 

#define RF0_dir TRISC3 
#define RF1_dir TRISC2 
#define RF2_dir TRISC1 
#define RF3_dir TRISC0

void RFRX_BEGIN(){
    RF0_dir = INPUT;
    RF1_dir = INPUT;
    RF2_dir = INPUT;
    RF3_dir = INPUT;
}

char RF_RECEIVE(){
	unsigned char chr;	
    
	chr = RF0_pin ;
	chr |= (RF1_pin << 1) ;
    chr |= (RF2_pin << 2) ;
    chr |= (RF3_pin << 3) ;
    
    return chr;
}