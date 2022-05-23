/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_loop(void) {
	uint8_t up_down = get_joystick_up_down();
	uint8_t left_right = 0;
	uint8_t forward_backward = 0;
	uint8_t siren = 0;
	uint8_t auto_manual_mode = 0;
	nrf_tx_data(up_down, left_right, forward_backward, siren, auto_manual_mode);
}
