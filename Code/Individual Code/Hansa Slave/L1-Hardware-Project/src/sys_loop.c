/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 * 
 */ 

#include "defines.h"


void sys_loop(void) {
	LCD_clear_msg("Welcome...");
	
	// Forward
	drive(255, 255);
	_delay_ms(1000);
	
	// Backward
	drive(-255, -255);
	_delay_ms(1000);
	
	// Left
	drive(-255, 255);
	_delay_ms(1000);
	
	// Right
	drive(255, -255);
	_delay_ms(1000);
}
