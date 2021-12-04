/*
 * CFile1.c
 *
 * Created: 11/29/2021 5:49:16 AM
 *  Author: Upeksha Herath
 */ 

#include "../defines.h"


#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

const long USART_BAUDRATE = 9600;

/*
	To initialize the USART connection between two components
	=========================================================
	
	UCSRB register the most used bits are the RXEN and TXEN
	UCSRC and the UBRRH share same address. To select the UCSRC we have to give 1 to URSEL else it will write in UBRRH register (because default value is 0).
	UCSZ0 and UCSZ1 sets the frame size. We have set that to 8 bits in this function 2nd line.
*/
void UART_init(long USART_BAUDRATE)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);						// Enable USART transmission (of transmitter) and reception (of receiver) 
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);	// Use 8-bit character sizes 
	UBRRL = BAUD_PRESCALE;									// Load lower 8-bits of the baud rate value 
	UBRRH = (BAUD_PRESCALE >> 8);							// Load upper 8-bits
}

/*
	To receive data 
	===============
*/
unsigned char UART_RxChar()
{
	while ((UCSRA & (1 << RXC)) == 0);	// Wait till data is received 
	return(UDR);						// Return the byte
}

/*
	To Transmit data
	=================
*/
void UART_TxChar(char ch)
{
	while (! (UCSRA & (1<<UDRE)));	// Wait for empty transmit buffer
	UDR = ch ;
}

/*
	To send String data
	===================
*/
void UART_SendString(char *str)
{
	unsigned char j=0;		//because int allocate more memory unsigned char can be used to store the int values
	
	while (str[j]!=0)		// Send string till null 
	{
		UART_TxChar(str[j]);
		j++;
	}
}