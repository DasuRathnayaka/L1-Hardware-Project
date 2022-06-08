/*
 * button.c
 *
 * Created: 5/18/2022 7:44:59 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "../defines.h"


void btn_init(void) {
	pin_mode(D2, INPUT_PULLUP);	// Mode selection button
	pin_mode(D3, INPUT_PULLUP);	// Siren button
}

/* Get switch status
 * Return
 *	- 0
 *	- 1
 */
uint8_t btn_mode() {
	return digital_read(D2);
}


/* Get switch status
 * Return
 *	- 0
 *	- 1
 */
uint8_t btn_siren() {
	return digital_read(D3);
}

