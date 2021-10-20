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

volatile uint8_t* selectRegister(char portChar, volatile uint8_t* A, volatile uint8_t* B, volatile uint8_t* C, volatile uint8_t* D) {
	switch(portChar) {
		case 'A':
			// PORT A
			return A;
			break;
		case 'B':
			// PORT B
			return B;
			break;
		case 'C':
			// PORT A
			return C;
			break;
		case 'D':
			// PORT A
			return D;
			break;
		default:
			// Error
			return NULL;
	}
}

int pinMode(char* pin, int mode) {
	volatile uint8_t *regi = selectRegister(pin[0], &DDRA, &DDRB, &DDRC, &DDRD);
	uint8_t pinVal = charToInt(pin[1]);
	
	if (mode == 0) {
		*regi &= ~(1 << pinVal);
	} else {
		*regi |= 1 << pinVal;
	}
	return 0;
}


int digitalWrite(char* pin, int level) {
	volatile uint8_t *regi = selectRegister(pin[0], &PORTA, &PORTB, &PORTC, &PORTD);
	uint8_t pinVal = charToInt(pin[1]);
	
	if (level == 1) {
		*regi |= 1 << pinVal;
	} else {
		*regi &= ~(1 << pinVal);
	}
	return 0;
}

int digitalRead(char* pin) {
	volatile uint8_t *regi = selectRegister(pin[0], &PINA, &PINB, &PINC, &PIND);
	uint8_t pinVal = charToInt(pin[1]);
	
	int val = *regi & (1 << pinVal);
	if (val == 0) {
		return 0;
	} else {
		return 1;
	}
}
