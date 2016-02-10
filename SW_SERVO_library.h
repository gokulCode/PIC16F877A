

#define SERVO_pin RB0
#define SERVO_dir TRISB0

void SERVO_MOTOR(int angle){
	int angleToDelay;
	int smooth;
    SERVO_dir = 0;
	angleToDelay = map(angle,0,179,0,48);
	for(smooth=0;smooth<30;smooth++){
		SERVO_pin = 1;              
		delay_us(44);
		delay_us(angleToDelay);
		SERVO_pin = 0;
		delay(20);
	}
}