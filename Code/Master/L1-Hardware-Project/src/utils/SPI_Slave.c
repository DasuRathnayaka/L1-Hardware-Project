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
	DDRB &= ~((1<<PB5)|(1<<PB7)|(1<<PB4));  // Make MOSI, SCK, SS as input pins 
	DDRB |= (1<<PB6);			// Make MISO pin as output pin 
	SPCR = (1<<SPE);			// Enable SPI in slave mode 
	
}


/*SPI Receive function
Return value = received char data
*/

char SPI_Receive()			// SPI Receive data function 
{
	while(!(SPSR & (1<<SPIF)));	// Wait till reception complete 
	return(SPDR);			// Return received data 
}


