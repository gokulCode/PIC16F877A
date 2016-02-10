#define DAC_0 RB0
#define DAC_1 RB1
#define DAC_2 RB2
#define DAC_3 RB3
#define DAC_4 RB4
#define DAC_5 RB5
#define DAC_6 RB6
#define DAC_7 RB7

#define DAC_0_dir TRISB0
#define DAC_1_dir TRISB1
#define DAC_2_dir TRISB2
#define DAC_3_dir TRISB3
#define DAC_4_dir TRISB4
#define DAC_5_dir TRISB5
#define DAC_6_dir TRISB6
#define DAC_7_dir TRISB7

void DAC_BEGIN(){
    DAC_0_dir = OUTPUT;
    DAC_1_dir = OUTPUT;
    DAC_2_dir = OUTPUT;
    DAC_3_dir = OUTPUT;
    DAC_4_dir = OUTPUT;
    DAC_5_dir = OUTPUT;
    DAC_6_dir = OUTPUT;
    DAC_7_dir = OUTPUT;
}

void DAC_WRITE(char value){
    
    DAC_0  =  (value     ) & 1;
    DAC_1  =  (value >> 1) & 1;
    DAC_2  =  (value >> 2) & 1;
    DAC_3  =  (value >> 3) & 1;
    DAC_4  =  (value >> 4) & 1;
    DAC_5  =  (value >> 5) & 1;
    DAC_6  =  (value >> 6) & 1;
    DAC_7  =  (value >> 7) & 1;
  
}