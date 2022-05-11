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
void SPI_Master_Init() {
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
void SPI_Slave_Init() {
	pin_mode(SLAVE_SS_0, INPUT);		// Set SS pin as output
	pin_mode(MOSI, INPUT);		// Set MOSI pin as output
	pin_mode(SCK, INPUT);		// Set SCK pin as output
	pin_mode(MISO, OUTPUT);		// Set MISO pin as output
	
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


/*
 * Transfer and receive data
 *
 * Parameter
 *	- data (unsigned char) - Data to send
 * Return
 *	- (unsigned char) - Data to receive
 */
unsigned char SPI_Tranceiver(unsigned char data) {
	SPDR = data;					// Load data into the buffer
	LCD_cmd(0xC2);
	LCD_msg("Running...");
	while(!(SPSR & (1<<SPIF)))		// Wait until transmission complete
	LCD_cmd(0xC2);
	LCD_msg("          ");
	return(SPDR);					// Returned received data
}


/*
 * Select the slave by set corresponding SS pin as HIGH.
 *
 * Parameter
 *	- SS (Pin) - Slave select pin; eg: B4
 * Return
 *	- None
 */
void SPI_Select_Slave(Pin SS) {
	digital_write(SS, HIGH);
}


/*
 * De-select the slave by set corresponding SS pin as LOW.
 *
 * Parameter
 *	- SS (Pin) - Slave select pin; eg: B4
 * Return
 *	- None
 */
void SPI_Deselect_Slave(Pin SS) {
	digital_write(SS, LOW);
}
