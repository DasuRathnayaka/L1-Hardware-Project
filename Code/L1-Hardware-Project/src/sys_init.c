/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_init(void) {
	pin_mode(A0, INPUT);
	pin_mode(D5, OUTPUT);
	
	ADC_int();
	PWM_init();
	
	LCD_Init();
	LCD_String("Starting...");
	_delay_ms(50);
}
