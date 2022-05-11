/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 *  Author: Hansa Jayathilaka
 */

#include "defines.h"


void sys_init(void) {
	pin_mode(D3, INPUT_PULLUP);
	pin_mode(B1, OUTPUT);
	
	// SPI_Master_Init();
	// SPI_Select_Slave(SLAVE_SS_0);
	
	pin_mode(SLAVE_SS_0, OUTPUT);		// Set SS pin as output
	pin_mode(MOSI, OUTPUT);		// Set MOSI pin as output
	pin_mode(SCK, OUTPUT);		// Set SCK pin as output
	pin_mode(MISO, INPUT);		// Set MISO pin as output
	
	SPCR = 0;
	
	SPCR |= (0 << SPIE);		// Disable interrupt
	SPCR |= (1 << SPE);			// Enable SPI
	SPCR |= (0 << DORD);		// Data order list; 0 => MSB transmitted first, 1 => LSB transmitted first
	SPCR |= (1 << MSTR);		// Set as master; 1 => Master, 0 => Slave
	SPCR |= (0 << CPOL);		// Clock polarity; 1 => Clock start from logical one, 0=> Clock start from logical zero
	SPCR |= (0 << CPHA);		// Clock phase; 1 => Data sample on trailing clock edge, 0 => Data sample on the leading clock edge
	SPCR |= (0 << SPR1) | (0 << SPR0);	// Set clock rate; Fosc/16
	
	// SPSR &= ~(1 << SPI2X);		// No double speed clock rate; 1=> Double speed, 0 => Normal speed
	SPSR |= (1 << SPI2X);
	
	I2C_init();
	I2C_start();
	I2C_write(0x70);
	LCD_init();
	LCD_cmd(0x80);
	LCD_msg("Master...");
}
