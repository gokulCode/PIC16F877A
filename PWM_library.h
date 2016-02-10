
// CCP1 and CCP2 module are used here to generate the required PWM
// Timer2 module is used to generate the PWM
// This PWM has 10bit resolution

// Function Name: SetPWMDutyCycle
// You can give a value in between 0 and 255 only for DutyCycle.
// CCP can have a value of 1 or 2 only for CCP1 or CCP2 respectively.
void SetPWMDutyCycle(unsigned char CCP, unsigned int DutyCycle)     
{
	DutyCycle = 4*DutyCycle;    // 1023/255 is 4

	switch(CCP)
	{
	case 1:
	
		CCPR1L   = DutyCycle>>2;        	// Put MSB 8 bits in CCPR1L
		CCP1CON &= 0xCF;                	// Make bit4 and 5 zero
		CCP1CON |= (0x30&(DutyCycle<<4));   // Assign Last 2 LSBs to CCP1CON
		break;
	
	case 2:
	
		CCPR2L   = DutyCycle>>2;        	// Put MSB 8 bits in CCPR1L
		CCP2CON &= 0xCF;                	// Make bit4 and 5 zero
		CCP2CON |= (0x30&(DutyCycle<<4));   // Assign Last 2 LSBs to CCP1CON
		break;
	}
}


void PWM_BEGIN(void)
{
	TRISC1  = 0; 			  // Make CCP2 pin as output
	TRISC2  = 0;              // Make CCP1 pin as output
	CCP1CON = 0x0C;           // Configure CCP1 module in PWM mode
	CCP2CON = 0x0C;           // Configure CCP2 module in PWM mode

	PR2   = 0xFF;             // Configure the Timer2 period
	T2CON = 0x01;             // Set Prescaler to be 4 to make 4.88kHz freq PWM

	SetPWMDutyCycle(1, 0);    // Intialize the CCP1 PWM to 0 duty cycle
	SetPWMDutyCycle(2, 0);    // Intialize the CCP2 PWM to 0 duty cycle

	T2CON |= 0x04;            // Enable the Timer2, hence enable the PWM.
}



