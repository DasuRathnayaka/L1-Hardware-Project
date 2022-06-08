/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 * 
 */ 

#include "defines.h"

void sys_loop(void) {
	char temp[1];
	I2C_slave_read_buffer(temp, 1);
	
	char val[16];
	sprintf(val, " %d ", temp[0]);
	
	UART_SendString(val);
	_delay_ms(1000);
}
