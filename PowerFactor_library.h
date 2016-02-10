#define PF_pin   RB3
#define FREQ_pin RB2

#define PF_dir   TRISB3
#define FREQ_dir TRISB2

int powerFactor(){
    int count,b,d;
    
        TMR1L=0X00;
		TMR1H=0X00;
		while(PF_pin==1);
		while(PF_pin==0);
		TMR1ON=1; // TIMER ON
		while(PF_pin==1);
		TMR1ON=0; // TIMER OFF
		count=((TMR1H*256)+TMR1L);
		b=((count/230.0));	
		d=(b*0.0174532925); 
		d=cos(d)*100.0;
        return d;
}

int frequncy(){
    int count,b,d;
    
        TMR1L=0X00;
		TMR1H=0X00;
		while(FREQ_pin==1);
		while(FREQ_pin==0);
		TMR1ON=1; // TIMER ON
		while(FREQ_pin==1);
		TMR1ON=0; // TIMER OFF
		count=((TMR1H*256)+TMR1L);
		b=((count/230.0));	
		d=(b*0.0174532925); 
		d=cos(d)*100.0;
        return d;
}