/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 * 
 */

#include "defines.h"


void sys_init(void) {
	SPI_slave_init();
	pin_mode(B4, INPUT);
	
	UART_init(9600);
}
