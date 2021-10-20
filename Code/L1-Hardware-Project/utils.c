/*
 * utils.c
 *
 * Created: 10/19/2021 10:10:07 AM
 *  Author: Hansa Jayathilaka
 */ 

#include <avr/io.h>
#include <stdio.h>


uint8_t charToInt(char val){
	return (uint8_t)(val - '0');
}

int pinMode(char* pin, int mode) {
	volatile uint8_t *regi;
	switch(pin[0]) {
		case 'A':
			// PORT A
			regi = &DDRA;
			break;
		case 'B':
			// PORT B
			regi = &DDRB;
			break;
		case 'C':
			// PORT A
			regi = &DDRC;
			break;
		case 'D':
			// PORT A
			regi = &DDRD;
			break;
		default:
			// Error
			return -1;
	}
	
	uint8_t pinVal = charToInt(pin[1]);
	if (mode == 0) {
		*regi &= ~(1 << pinVal);
	} else {
		*regi |= 1 << pinVal;
	}
	return 0;
}


int digitalWrite(char* pin, int level) {
	volatile uint8_t *regi;
	switch(pin[0]) {
		case 'A':
			// PORT A
			regi = &PORTA;
			break;
		case 'B':
			// PORT B
			regi = &PORTB;
			break;
		case 'C':
			// PORT A
			regi = &PORTC;
			break;
		case 'D':
			// PORT A
			regi = &PORTD;
			break;
		default:
			// Error
			return -1;
	}
	
	uint8_t pinVal = charToInt(pin[1]);
	if (level == 1) {
		*regi |= 1 << pinVal;
	} else {
		*regi &= ~(1 << pinVal);
	}
	return 0;
}
