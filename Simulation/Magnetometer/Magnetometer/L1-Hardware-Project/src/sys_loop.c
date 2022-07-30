/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 * 
 */ 

#include "defines.h"

char address = 0x22;

void sys_loop(void) {
	char val = ADC_read(A2);
	char temp[] = { val };
	I2C_master_write_buffer(address, temp, 1);
	_delay_ms(1000);
}
