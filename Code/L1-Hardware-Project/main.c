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
	pin_mode(A0, INPUT);
	pin_mode(D5, OUTPUT);
	
	ADC_int();
	PWM_init();
	
	LCD_Init();
	LCD_String("Starting...");
	_delay_ms(50);
	
	while(1) {
		int val = ADC_read(A0);
		LCD_Int(val);
		PWM_write(D5, val);
		
		_delay_ms(25);
	}
	return 0;
}
