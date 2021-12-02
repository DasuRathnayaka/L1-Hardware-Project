/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_loop(void) {
	int val = ADC_read(A0);
	LCD_Int(val);
	PWM_write(D5, val);
	
	//Upeksha's practice code
	
	
	/*
	 *This is just for the practice sake
	 */
	
	
	
	_delay_ms(25);
}
