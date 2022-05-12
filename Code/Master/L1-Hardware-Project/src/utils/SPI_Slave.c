/*
 * SPI_Slave.c
 *
 * Created: 5/10/2022 11:40:24 AM
 *  Author: Dasuni Rathnayaka
 */ 

#include "../defines.h"

/*SPI Slave Initialization
PB7 = SCK
PB6 = MISO
PB5 = MOSI
PB4 = SS#
PB3 = OC0/AIN1
PB2 = INT2/AIN0
PB1 = T1
PB0 = XCK/T0
*/

void SPI_Slave_Init()					
{
	pin_mode(B4, INPUT);		// Set SS pin as output
	pin_mode(B5, INPUT);		// Set MOSI pin as output
	pin_mode(B7, INPUT);		// Set SCK pin as output
	pin_mode(B6, OUTPUT);		// Set MISO pin as output

	SPCR = 0;

	SPCR |= (0 << SPIE);		// Disable interrupt
	SPCR |= (1 << SPE);			// Enable SPI
	SPCR |= (0 << DORD);		// Data order list; 0 => MSB transmitted first, 1 => LSB transmitted first
	SPCR |= (0 << MSTR);		// Set as slave; 1 => Master, 0 => Slave
	SPCR |= (0 << CPOL);		// Clock polarity; 1 => Clock start from logical one, 0=> Clock start from logical zero
	SPCR |= (0 << CPHA);		// Clock phase; 1 => Data sample on trailing clock edge, 0 => Data sample on the leading clock edge
	SPCR |= (0 << SPR1) | (1 << SPR0);	// Set clock rate

	SPSR &= ~(1 << SPI2X);		// No double speed clock rate; 1=> Double speed, 0 => Normal speed
}


/*SPI Receive function
Return value = received char data
*/

char SPI_Receive()			// SPI Receive data function
{
	while(!(SPSR & (1<<SPIF)));	// Wait till reception complete
	return(SPDR);			// Return received data
}
