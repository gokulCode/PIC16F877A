
#define CLEAR_ALL 0x01

#define SHIFT_RIGHT  0x1C
#define SHIFT_LEFT   0x18

#define CURSOR_ON    0x0E
#define CURSOR_OFF   0x0C
#define AUTO_INC_ON  0x06
#define AUTO_INC_OFF 0x04

//////////////////////
#define LCD_RS  RC4 //
#define LCD_EN  RC5 //
//////////////////////
#define LCD_D4  RD4 //
#define LCD_D5  RD5 //
#define LCD_D6  RD6 //
#define LCD_D7  RD7 //
//////////////////////

// library Functions
/*
	LCD_BEGIN()        
	LCD_LOC(x,y)
	LCD_COMMEND(CMD)
	LCD_PRINT()
  LCD_PRINT_Number()
*/

void DATA_PIN_ASSIGN(unsigned char chr){
		
	LCD_D4 = chr      & 1 ;
	LCD_D5 = chr >> 1 & 1 ;
	LCD_D6 = chr >> 2 & 1 ;
	LCD_D7 = chr >> 3 & 1 ;

}

void LCD_COMMEND (unsigned char CMD){
		
	unsigned char CMD_LSB,CMD_MSB;
	
	CMD_LSB = 0x0F & CMD ;
	CMD_MSB = 0x0F & (CMD >> 4) ;
	
	LCD_RS = 0 ;  LCD_EN = 0 ; 
  
	DATA_PIN_ASSIGN( CMD_MSB ) ;
	
	LCD_EN = 1 ; delay_us(1) ; LCD_EN = 0 ; // Enable LCD port
	
	DATA_PIN_ASSIGN( CMD_LSB ) ;
	
	LCD_EN = 1 ; delay_us(1) ; LCD_EN = 0 ; // Enable LCD port
	
	delay_us(2);
}

void LCD_WRITE (unsigned char DATA){
		
	unsigned char DATA_LSB,DATA_MSB;
	
	DATA_LSB = 0x0F &  DATA ;
	DATA_MSB = 0x0F & (DATA >> 4) ;
	
	LCD_RS = 1 ;  LCD_EN = 0 ; 
  
	DATA_PIN_ASSIGN( DATA_MSB ) ;
	
	LCD_EN = 1 ; delay_us(1) ; LCD_EN = 0 ; // Enable LCD port
	
	DATA_PIN_ASSIGN( DATA_LSB ) ;
	
	LCD_EN = 1 ; delay_us(1) ; LCD_EN = 0 ; // Enable LCD port
	
	LCD_RS = 0 ;
	
	delay_us(2);
}

void LCD_LOC(unsigned int x,unsigned int y){
			
	if (x==1) {
	      LCD_COMMEND(0x80+y-1) ;
  }
	else if (x==2) {
	      LCD_COMMEND(0xC0+y-1) ;
  }

}

void LCD_PRINT(unsigned char *STRING){
        
	   int i=0;
	 for(i=0;STRING[i]!='\0';i++){
	    LCD_WRITE(STRING[i]);
	 }
}
///*
void LCD_PRINT_Number(int num){
	
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
			LCD_WRITE('-');			
		 }

		 for(i=0;i<=len;i++){
				LCD_WRITE(BCD[len-i]+0x30);
			}	
       LCD_WRITE(' ');
    }
	
void LCD_PRINT_Fraction(float number){
    int integer,fraction;
	  
	  integer = number ;
	  fraction = abs((number-integer) * 10) ;
		
	  LCD_PRINT_Number(integer) ;
	  LCD_WRITE('.');
	  LCD_PRINT_Number(fraction);
}

void LCD_DECIMAL3(unsigned int num)
{
	unsigned char _100s,_10s,_1s;
	_100s=((num%1000))/100;
	 _10s=((num%100))/10;
	  _1s=num%10;
	LCD_WRITE(_100s+0x30);
	LCD_WRITE(_10s+0x30);
	LCD_WRITE(_1s+0x30);
} 
//*/

void LCD_BEGIN(){
	
	TRISD  = TRISD & 0X0F ;
	TRISC4 = 0;
	TRISC5 = 0;
    DATA_PIN_ASSIGN(0x00);

	LCD_COMMEND(0x33);		
	LCD_COMMEND(0x32);		
	LCD_COMMEND(0x28);		
	LCD_COMMEND(0x0c);		
	LCD_COMMEND(0x06);
    
}

void LCD_CLEAR(){
    LCD_COMMEND(CLEAR_ALL);
    delay(10);
}

void LCD_LINE_CLEAR(int line){
	LCD_LOC(line,1);
	LCD_PRINT("                ");
}