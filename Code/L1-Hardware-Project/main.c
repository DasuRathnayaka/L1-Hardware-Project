/*
 * L1-Hardware-Project.c
 *
 * Created: 10/19/2021 10:07:30 AM
 * Author : Hansa Jayathilaka
 */ 

// #ifdef F_CPU
#define F_CPU 16000000L
// #endif

#include <avr/io.h>
#include <util/delay.h>
#include "defines.h"

int main(void)
{
	pinMode(A1, OUTPUT);
	
	while(1) {
		digitalWrite(A1, LOW);
		_delay_ms(1000);
		digitalWrite(A1, HIGH);
		_delay_ms(1000);
	}
	return 0;
}
