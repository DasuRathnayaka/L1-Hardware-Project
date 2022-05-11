/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_loop(void) {
	if (digital_read(D3) == HIGH) {
		SPDR = 0xFF;
		while(!(SPSR & (1<<SPIF)));
		// char a = (signed char)SPI_Tranceiver(1);
		// LCD_cmd(0xC0);
		// LCD_dwr(a);
	} else {
		// char a = (signed char)SPI_Tranceiver(0);
		// LCD_cmd(0xC0);
		// LCD_dwr(a);
		SPDR = 0x00;
		while(!(SPSR & (1<<SPIF)));
	}
	
	_delay_ms(500);
	digital_write(B1, HIGH);
	_delay_ms(500);
	digital_write(B1, LOW);
}
