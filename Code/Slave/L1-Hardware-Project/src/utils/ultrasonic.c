/*
 * ultrasonic.c
 *
 * Created: 11/1/2021 10:49:53 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "../defines.h"

#define trigPin C6
#define echoPin D3

#define mux1 C4
#define mux2 C5

int found = 0;
int kp = 10;


void ultrazonic_init() {
	pin_mode(trigPin, OUTPUT);
	pin_mode(echoPin, INPUT_PULLUP);
	
	pin_mode(mux1, OUTPUT);
	pin_mode(mux2, OUTPUT);
}


int ultrazonic_error() {
	digital_write(mux1, LOW);
	digital_write(mux2, LOW);
	int left = ultrazonic_distance(trigPin, echoPin, NULL);
	
	digital_write(mux1, LOW);
	digital_write(mux2, HIGH);
	int right = ultrazonic_distance(trigPin, echoPin, NULL);
	
	digital_write(mux1, LOW);
	digital_write(mux2, LOW);
	
	int error = (right - left) * kp;
	
	return error;
}


ISR(INT0_vect) {
	if (digital_read(D3) == 0) {
		// Falling edge
		ultrazonic_pulse -= time_us();
		found = 1;
	} else {
		// Ricing Edge
		ultrazonic_pulse = time_us();
		found = 0;
	}
}


int ultrazonic_distance(Pin _trigPin, Pin _echoPin, unsigned long timeout) {
	if (timeout == NULL) timeout = 500000;
	
	digital_write(_trigPin, HIGH);
	_delay_us(10);
	digital_write(_trigPin, LOW);
	
	// Enable Interrupt
	GICR |= (1 << INT0);
	MCUCR |= (0 << ISC01) | (1 << ISC00);
	
	unsigned long temp_time = time_us();
	while(found == 0 || temp_time - time_us() > 50000);
	unsigned long duration = 0;
	if (found == 1) {
		duration = ultrazonic_pulse;
	}
	
	GICR &= ~(1 << INT0);
	
	int distance = duration * 0.034 / 2;
	
	return distance;
}
