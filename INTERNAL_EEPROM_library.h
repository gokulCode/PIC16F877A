void INTERNAL_EEPROM_WRITE(char address, char data)
{
	WREN=1;        
	EEADR=address; 
	EEDATA=data; 
	EEPGD=0;
	GIE=0; 
 //---------------
	EECON2=0x55;  
	EECON2=0xAA;  
 //---------------
	 WR=1;
	 GIE=1;
	 while (WR==1); 
     WREN=0; 
} 

char INTERNAL_EEPROM_READ(char address)
{
	EEADR=address; 
	EEPGD=0; 
	RD=1; 
	while(RD==1);
	return EEDATA;
}

// referance - http://www.microchip.com/forums/m103053.aspx