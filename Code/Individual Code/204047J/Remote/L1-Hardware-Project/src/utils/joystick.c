/*
 * joystick.c
 *
 * Created: 5/18/2022 7:53:34 PM
 *  Author: Binari Dissanayake
 */ 

#include "../defines.h"


void joystick_init(void) {
	pin_mode(A0, INPUT);	// Up / Down
	pin_mode(A1, INPUT);	// Left / Right
	pin_mode(A2, INPUT);	// Forward / Backward
}

/* 
 * Get angle for camera
 */
uint8_t get_joystick_up_down() {
	return ADC_read(A0);
}

/* 
 * Get turn
 */
uint8_t get_joystick_left_right() {
	return ADC_read(A1);
}

/* 
 * Get forward and backward speed
 */
uint8_t get_joystick_forward_backward() {
	return ADC_read(A2);
}
