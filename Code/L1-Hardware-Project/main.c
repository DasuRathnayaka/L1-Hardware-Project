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

int main(void) {
	pinMode(A0, INPUT);
	
	ADC_int();
	
	LCD_Init();
	LCD_String("Starting...");
	_delay_ms(50);
	
	while(1) {
		int val = analogRead(A0);
		
		LCD_Int(val);
		
		_delay_ms(25);
	}
	return 0;
}
