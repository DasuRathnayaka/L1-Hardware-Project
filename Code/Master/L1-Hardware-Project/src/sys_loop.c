/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_loop(void) {
	for(int i = 0; i < 256; i++) {
		PWM_write(B3, i);
		_delay_ms(5);
	}
	for(int i = 0; i < 256; i++) {
		PWM_write(D4, i);
		_delay_ms(5);
	}
	for(int i = 0; i < 256; i++) {
		PWM_write(D5, i);
		_delay_ms(5);
	}
	for(int i = 0; i < 256; i++) {
		PWM_write(D7, i);
		_delay_ms(5);
	}
	
	LCD_clear_msg("Hello World.");
	
	digital_write(B0, HIGH);
	_delay_ms(1000);
	digital_write(B0, LOW);
	_delay_ms(1000);
}
