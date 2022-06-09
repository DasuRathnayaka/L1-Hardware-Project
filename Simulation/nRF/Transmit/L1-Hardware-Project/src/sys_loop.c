/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 * 
 */ 

#include "defines.h"

unsigned char preData = 0x00;
// Transmeter
void sys_loop(void) {
	int read = ADC_read(A2);
	unsigned char data = SPI_tranceiver(read);
	_delay_ms(500);
}
