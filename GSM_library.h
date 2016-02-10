void GSM_BEGIN(){
	SERIAL_PRINT("ATE1");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(100);
    SERIAL_AVAILABLE = 0;
}

char GSM_CONNECTION(){
	SERIAL_PRINT("AT");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(100);
    if(SERIAL_REC[2]=='O' && SERIAL_REC[3]=='K'){
       SERIAL_AVAILABLE = 0;
       return 1;
    }else{
       SERIAL_AVAILABLE = 0;
       return 0;
    } 
}

void GSM_MAKE_CALL(char *mobileNo){
    SERIAL_PRINT("ATD ");
    SERIAL_PRINT(mobileNo);
    SERIAL_PRINT(";");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(100);
    SERIAL_AVAILABLE = 0;
}


        
void GSM_DETELE_ALL_SMS(){
    SERIAL_PRINT("AT+CMGDA=\"DEL ALL\"");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(1000);
    SERIAL_AVAILABLE = 0;
}

void GSM_AUTOMATIC_SMS_READ(){
    SERIAL_PRINT("AT+CMGF=1");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(100);
    SERIAL_PRINT("AT+CNMI=2,2,0,0,0");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(100);
}

void GSM_SEND_SMS(char *mobileNo,char *massage){
    SERIAL_PRINT("AT+CMGF=1");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(1000);
    SERIAL_PRINT("AT+CMGS=\"");
    delay(100);
    SERIAL_PRINT(mobileNo);
    delay(100);
    SERIAL_PRINT("\"");
    SERIAL_WRITE(CARRIAGE_RETRUN);
    delay(1000);
    SERIAL_PRINT(massage);
    SERIAL_WRITE(CARRIAGE_RETRUN);
    SERIAL_WRITE(CTRL_Z);
    delay(1000);
    SERIAL_AVAILABLE = 0;
}

char* DOWNLOAD_MOBILE_No(int addr){
    int i;
    char numbr[11];
    
    for(i=0;i<10;i++){
        numbr[i] = INTERNAL_EEPROM_READ(addr+i);
    }
    numbr[10]='\0';
    LCD_LOC(1,1);
    LCD_PRINT(numbr);
    return numbr;
}

void UPLOAD_MOBILE_No(int addr,char *numbr){
    int i;
    for(i=0;i<10;i++){
        INTERNAL_EEPROM_WRITE(addr+i,numbr[i]);
    }
}