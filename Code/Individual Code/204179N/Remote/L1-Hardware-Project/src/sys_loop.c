/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  
 */ 

#include "defines.h"


void sys_loop(void) {
	char text[20];
	
	uint8_t left_right = get_joystick_left_right();
	uint8_t forward_backward = get_joystick_forward_backward();
	
	LCD_line_1();
	LCD_msg("Forward : ");
	sprintf(text, "%d", forward_backward);
	LCD_msg(text);
	LCD_msg("           ");
	
	LCD_line_2();
	LCD_msg("Right   : ");
	sprintf(text, "%d", left_right);
	LCD_msg(text);
	LCD_msg("           ");
}
