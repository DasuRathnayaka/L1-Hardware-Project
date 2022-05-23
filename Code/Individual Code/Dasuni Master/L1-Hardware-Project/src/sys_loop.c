/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_loop(void) {
	uint8_t left_right = get_joystick_left_right();
	uint8_t forward_backward = get_joystick_forward_backward();
}
