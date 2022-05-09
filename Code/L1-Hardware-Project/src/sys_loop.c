/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_loop(void) {
	LCD_Int(ultrazonic_distance(C6, D0, NULL));
	
	// PWM_write_reg(&OCR1A, val);


	/*digital_write(C3, HIGH);
	_delay_ms(500);
	digital_write(C3, LOW);*/
	_delay_ms(500);
}
