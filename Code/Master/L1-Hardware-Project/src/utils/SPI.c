/*
 * SPI.c
 *
 * Created: 5/11/2022 6:53:26 PM
 *  Author: Binari, Dasuni
 */ 


#include "../defines.h"



/*
 * Initialize SPI for master device
 *
 * Parameter
 *	- None
 * Return
 *	- None
 */
void SPI_master_init() {
	pin_mode(SLAVE_SS_0, OUTPUT);		// Set SS pin as output
	pin_mode(MOSI, OUTPUT);		// Set MOSI pin as output
	pin_mode(SCK, OUTPUT);		// Set SCK pin as output
	pin_mode(MISO, INPUT);		// Set MISO pin as output
	
	SPCR = 0x00;
	
	SPCR |= (0 << SPIE);		// Disable interrupt
	SPCR |= (0 << DORD);		// Data order list; 0 => MSB transmitted first, 1 => LSB transmitted first
	SPCR |= (1 << MSTR);		// Set as master; 1 => Master, 0 => Slave
	SPCR |= (0 << CPOL);		// Clock polarity; 1 => Clock start from logical one, 0=> Clock start from logical zero
	SPCR |= (0 << CPHA);		// Clock phase; 1 => Data sample on trailing clock edge, 0 => Data sample on the leading clock edge
	SPCR |= (0 << SPR1) | (1 << SPR0);	// Set clock rate; Fosc/16
	SPCR |= (1 << SPE);			// Enable SPI (After configure everything, you can enable SPI. If you try to enable SPI before the configurations, you have to face some errors.)
	
	SPSR &= ~(1 << SPI2X);		// No double speed clock rate; 1=> Double speed, 0 => Normal speed
}


/*
 * Initialize SPI for slave device
 *
 * Parameter
 *	- None
 * Return
 *	- None
 */
void SPI_slave_init() {
	pin_mode(SLAVE_SS_0, INPUT);		// Set SS pin as output
	pin_mode(MOSI, INPUT);		// Set MOSI pin as output
	pin_mode(SCK, INPUT);		// Set SCK pin as output
	pin_mode(MISO, OUTPUT);		// Set MISO pin as output
	
	SPCR = 0;
	
	SPCR |= (0 << SPIE);		// Disable interrupt
	SPCR |= (0 << DORD);		// Data order list; 0 => MSB transmitted first, 1 => LSB transmitted first
	SPCR |= (0 << MSTR);		// Set as slave; 1 => Master, 0 => Slave
	SPCR |= (0 << CPOL);		// Clock polarity; 1 => Clock start from logical one, 0=> Clock start from logical zero
	SPCR |= (0 << CPHA);		// Clock phase; 1 => Data sample on trailing clock edge, 0 => Data sample on the leading clock edge
	SPCR |= (0 << SPR1) | (1 << SPR0);	// Set clock rate
	SPCR |= (1 << SPE);			// Enable SPI
	
	SPSR &= ~(1 << SPI2X);		// No double speed clock rate; 1=> Double speed, 0 => Normal speed
}


/*
 * Transfer and receive data
 *
 * Parameter
 *	- data (unsigned char) - Data to send
 * Return
 *	- (unsigned char) - Data to receive
 */
unsigned char SPI_tranceiver(unsigned char data) {
	SPDR = data;					// Load data into the buffer
	while(!(SPSR & (1<<SPIF)))		// Wait until transmission complete
	return SPDR;					// Returned received data
}


/*
 * Select the slave by set corresponding SS pin as HIGH.
 *
 * Parameter
 *	- SS (Pin) - Slave select pin; eg: B4
 * Return
 *	- None
 */
void SPI_select_slave(Pin SS) {
	digital_write(SS, LOW);
}


/*
 * De-select the slave by set corresponding SS pin as LOW.
 *
 * Parameter
 *	- SS (Pin) - Slave select pin; eg: B4
 * Return
 *	- None
 */
void SPI_deselect_slave(Pin SS) {
	digital_write(SS, HIGH);
}


int SPI_check_available() {
	return (SPSR & (1<<SPIF)) == 1
}

unsigned char SPI_read() {
	return SPDR;	// Returned received data
}


void SPI_write(unsigned char data) {
	char flush_buffer;
	SPDR = data;					// Load data into the buffer
	while(!(SPSR & (1<<SPIF)))		// Wait until transmission complete
	flush_buffer = SPDR;			// Returned received data
}
