/*
 * SPI_Master.c
 *
 * Created: 5/10/2022 11:40:23 AM
 *  Author: Binari Dissanayake
 */ 

#include "../defines.h"



void SPI_Master_Init()
{
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
	SPCR |= (0 << SPR1) | (1 << SPR0);	// Set clock rate
	
	SPSR &= ~(1 << SPI2X);		// No double speed clock rate; 1=> Double speed, 0 => Normal speed
}


/* 
 * SPI write data
 * Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read 
 */
void SPI_Write(char data)		
{
	char flush_buffer;
	SPDR = data;						// Set data to data register
	while((SPSR & (1 << SPIF)) == 0);	// Wait until interrupt flag
	flush_buffer = SPDR;				// Flush received data
}


/*
 * SPI read data
 */ 
char SPI_Read()				/* SPI read data function */
{
	SPDR = 0xFF;
	while((SPSR & (1 << SPIF)) == 0);	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}


