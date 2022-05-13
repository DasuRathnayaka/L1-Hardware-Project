/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_loop(void) {
	char data[2];
	I2C_slave_read_buffer(data, 2);
	if (data[0] == 'a') {
		digital_write(B0, HIGH);
	} else {
		digital_write(B0, LOW);
	}
	if (data[1] == 'b') {
		digital_write(B1, HIGH);
		} else {
		digital_write(B1, LOW);
	}
}
