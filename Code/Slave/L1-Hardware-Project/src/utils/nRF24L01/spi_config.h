/* 
 * 	SPI configuration for AVR project 
 *
 *	This file define SPI configuration specific to the project. 
 *	The definitions are:
 *		SPI_DDR: 	Direction register of the AVR I/O port which contains the SPI signals (eg: DDRB)
 *		SPI_PORT:	Port register corresponding to SPI_DDR (eg: PORTB)
 *		MOSI_BIT:	Bit number of MOSI signal in SPI_PORT (eg: 5)
 *		SCK_BIT:	Bit number of SCK signal in SPI_PORT (eg: 7)
 *		SS_BIT:		Bit number of SS signal in SPI_PORT (eg: 4)
 */
 
 
 #ifndef SPI_CONFIG_H
 #define SPI_CONFIG_H
 
/* SPI Port and Pin definitions */
#define SPI_DDR		DDRB
#define SPI_PORT	PORTB
#define MOSI_BIT	5 
#define SCK_BIT		7 
#define SS_BIT		4
 
#endif
