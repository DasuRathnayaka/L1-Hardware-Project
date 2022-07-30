/*
 * joystick.c
 *
 * Created: 5/18/2022 7:53:34 PM
 *  Author: Binari Dissanayake
 */ 

#include "../defines.h"


void joystick_init(void) {
	pin_mode(A0, INPUT);	// Up / Down

}

/* 
 * Get angle for camera
 */
uint8_t get_joystick_up_down() {
	return ADC_read(A0);
}

