/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 * 
 */ 

#include "defines.h"



void sys_loop(void) {
	int siren = 0;
	
	servo_write(90);
	
	if (siren == 1)
		digital_write(B0, HIGH);
	else
		digital_write(B0, LOW);
}
