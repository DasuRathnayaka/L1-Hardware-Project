/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 * 
 */ 

#include "defines.h"



int siren = 0;
void sys_loop(void) {
	
	servo_write(90);
	
	if (siren == 1) {
		digital_write(B0, HIGH);
		siren = 0;
	}
	else {
		digital_write(B0, LOW);
		siren = 1;
	}
	_delay_ms(1000);
}
