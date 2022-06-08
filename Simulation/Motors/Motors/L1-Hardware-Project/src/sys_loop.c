/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 * 
 */ 

#include "defines.h"


void sys_loop(void) {
// 	// Forward
// 	LCD_clear_msg("Forward...");
// 	drive(100, 100);
// 	_delay_ms(2000);
// 	
// 	drive(0, 0);
// 	_delay_ms(2000);
// 	
// 	// Backward
// 	LCD_clear_msg("Backward...");
// 	drive(-100, -100);
// 	_delay_ms(2000);
// 	
// 	// Left
// 	LCD_clear_msg("Left...");
// 	drive(-100, 100);
// 	_delay_ms(2000);
// 	
// 	// Right
// 	LCD_clear_msg("Right...");
// 	drive(100, -100);
// 	_delay_ms(2000);
	for (int i = 0; i < 255; i++) {
		drive(i, -i);
		_delay_ms(50);
	}
}
