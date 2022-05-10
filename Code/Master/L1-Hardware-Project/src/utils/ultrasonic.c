/*
 * ultrasonic.c
 *
 * Created: 11/1/2021 10:49:53 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "../defines.h"


int ultrazonic_distance(Pin trigPin, Pin echoPin, int timeout) {
	if (timeout == NULL) timeout = 500000;
	pin_mode(trigPin, OUTPUT);
	pin_mode(echoPin, INPUT_PULLUP);
	
	digital_write(trigPin, HIGH);
	_delay_us(10);
	digital_write(trigPin, LOW);
	
	unsigned long duration = pulse_in(echoPin, timeout);
	
	int distance = duration * 0.034 / 2;
	
	return distance;
}


unsigned long pulse_in(Pin pin, unsigned long timeout) {
	unsigned long RC_VALUE;
	if (timeout == NULL) timeout = 500000;
	
	volatile uint8_t *regi = select_register(pin.port, &PINA, &PINB, &PINC, &PIND); // Select DDR according to pin
	char RC_PIN_STATE = (*regi & (1 << pin.pin));
	
	//timeout zone
	unsigned long numloops = 0;
	unsigned long width = 0;
	// wait for any previous pulse to end
	while ( RC_PIN_STATE == 1)
	{
		RC_PIN_STATE = (*regi & (1 << pin.pin)); //keep reading the pin until it changes the state
		if (numloops++ == timeout) break;
	}
	// wait for the pulse to start
	while (RC_PIN_STATE == 0)
	{
		RC_PIN_STATE = (*regi & (1 << pin.pin)); //keep reading the pin until it changes the state
		if (numloops++ == timeout) break;
	}
	
	// wait for the pulse to stop @ here we are measuring the pulse width = incrementing the WIDTH value by one each cycle. atmega328 1 micro second is equal to 16 cycles.
	while (RC_PIN_STATE == 1)
	{
		RC_PIN_STATE = (*regi & (1 << pin.pin));
		if (numloops++ == timeout) break;
		width++;
	}

	RC_VALUE = width / 16;
	return RC_VALUE;
}
