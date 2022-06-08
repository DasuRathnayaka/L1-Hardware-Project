/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  
 */ 

#include "defines.h"


void sys_loop(void) {
	uint8_t up_down = get_joystick_up_down();
	uint8_t left_right = get_joystick_left_right();
	uint8_t forward_backward = get_joystick_forward_backward();
	uint8_t siren = btn_siren();
	uint8_t auto_manual_mode = btn_mode();
	if (auto_manual_mode == 0) {
		LCD_line_1();
		LCD_msg("Auto Mode       ");
	} else {
		LCD_line_1();
		LCD_msg("Manual Mode     ");
	}
	nrf_tx_data(up_down, left_right, forward_backward, siren, auto_manual_mode);
}
