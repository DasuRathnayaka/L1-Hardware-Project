/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_init(void) {
	sei();  //Enable global interrupt
	
	pin_mode(D0, INPUT);
	pin_mode(C6, OUTPUT);
	
	PWM_init();
	ADC_int();
	
	LCD_Init();
	LCD_String("Group - 47");
	_delay_ms(50);
}
