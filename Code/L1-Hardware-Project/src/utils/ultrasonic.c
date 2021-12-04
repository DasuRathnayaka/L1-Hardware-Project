/*
 * ultrasonic.c
 *
 * Created: 11/1/2021 10:49:53 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "../defines.h"


float ultrazonic_distance(Pin trigPin, Pin echoPin) {
	pin_mode(trigPin, OUTPUT);
	pin_mode(echoPin, INPUT_PULLUP);
	
	TIMSK = (1 << TOIE2); // Set timer2 to 
	digital_write(trigPin, HIGH);
	_delay_us(10);
	digital_write(trigPin, LOW);
	unsigned long curr_time = time_us();
	
	return 0.0;
}
