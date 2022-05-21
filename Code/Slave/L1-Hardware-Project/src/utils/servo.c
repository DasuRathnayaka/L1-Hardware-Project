/*
 * servo.c
 *
 * Created: 5/21/2022 8:55:11 PM
 *  Author: Sadini Pathirana
 */ 

#include "../defines.h"


/*
 * -90 - 14
 *  90 - 31
 */

void servo_init() {
	pin_mode(B3, OUTPUT);
}


void servo_write(int angle) {
	angle += 90;
	float val = angle / 180;
	
}
