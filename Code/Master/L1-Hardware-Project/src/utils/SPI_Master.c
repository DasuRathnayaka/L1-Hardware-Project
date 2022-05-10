/*
 * SPI_Master.c
 *
 * Created: 5/10/2022 11:40:23 AM
 *  Author: Binari Dissanayake
 */ 

#include "../defines.h"

/* SPI Master Initialization
PB7 = SCK
PB6 = MISO
PB5 = MOSI
PB4 = SS#
PB3 = OC0/AIN1
PB2 = INT2/AIN0
PB1 = T1
PB0 = XCK/T0*/

void SPI_Master_Init()
{
	DDRB |= (1<<PB5) | (1<< PB7) | (1<<PB4); // Make MOSI, SCK, SS as output pin
    DDRB &= ~(1<<PB6); //Make MISO pin as input pin
	PORTB |= (1<<PB4); //Make high on SS pin
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0); // Enable SPI , Select Master Mode and clock Rate Select as Fosc/16
	SPSR &= ~(1<<SPI2X); //Disable speed doubler
}

/* SPI write data function
Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read 
 */

void SPI_Write(char data)		
{
	char flush_buffer;
	SPDR = data;			/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));	/* Wait till transmission complete */
	flush_buffer = SPDR;		/* Flush received data */
}
	
/* SPI Read Function*/ 
	
char SPI_Read()				/* SPI read data function */
{
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}
