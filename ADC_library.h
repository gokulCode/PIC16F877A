void ADC_config(char config_code){
	
	TRISA  = 0xFF ; 
    TRISE  = 0x07 ;
    ADCON1 = config_code;

}

int ADC_READ(char chennal){
    
    int analogValue ;
    ADFM = 1;
	ADCON0 = 0x80 | chennal << 3 ;
    ADON = 1 ;
    ADCON0 |= 1 << 2;
    while(ADCON0>>2 & 1);
    analogValue = (ADRESH << 8 | ADRESL) ;
    return analogValue; 
}

int ADC_FILTER(int channel){
    int sample;
    int cumulat=0;
    cumulat = 0;
    for(sample = 0; sample < 10;sample++){
        cumulat += ADC_READ(channel);
        delay(10);
    }
    return cumulat/10;
    
}