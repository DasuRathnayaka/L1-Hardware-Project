/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  
 */ 

#include "defines.h"


void sys_loop(void) {
	char text[20];
	
	uint8_t up_down = get_joystick_up_down();
	uint8_t left_right = 0;
	uint8_t forward_backward = 0;
	uint8_t siren = 0;
	uint8_t auto_manual_mode = 0;
	//nrf_tx_data(up_down, left_right, forward_backward, siren, auto_manual_mode);
	
	sprintf(text, "%d", up_down);
	LCD_line_1();
	LCD_msg("Up / Down : ");
	LCD_msg(text);
	LCD_msg("     ");
}
