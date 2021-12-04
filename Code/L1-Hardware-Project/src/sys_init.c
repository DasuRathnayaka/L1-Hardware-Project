/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_init(void) {
	sei();  //Enable global interrupt
	
	pin_mode(A0, INPUT);
	pin_mode(C3, OUTPUT);
	pin_mode(B3, OUTPUT);
	pin_mode(D4, OUTPUT);
	pin_mode(D5, OUTPUT);
	pin_mode(D7, OUTPUT);
	
	ADC_int();
	PWM_init();
	
	LCD_Init();
	LCD_String("Group - 47");
	_delay_ms(50);
}
