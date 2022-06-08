/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 * 
 */ 

#include "defines.h"


void sys_loop(void) {
	// Forward
	LCD_clear_msg("Forward...");
	drive(255, 255);
	_delay_ms(2000);
	
	// Backward
	LCD_clear_msg("Backward...");
	drive(-255, -255);
	_delay_ms(2000);
	
	// Left
	LCD_clear_msg("Left...");
	drive(-255, 255);
	_delay_ms(2000);
	
	// Right
	LCD_clear_msg("Right...");
	drive(255, -255);
	_delay_ms(2000);
}
