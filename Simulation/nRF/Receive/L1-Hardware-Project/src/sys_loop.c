/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 * 
 */ 

#include "defines.h"

unsigned char preData = 0x00;
// Receiver
void sys_loop(void) {
	unsigned char data = SPI_tranceiver(0x11);
	
	char dataStr[16];
	sprintf(dataStr, " %d ", data);
	UART_SendString(dataStr);
	
}
