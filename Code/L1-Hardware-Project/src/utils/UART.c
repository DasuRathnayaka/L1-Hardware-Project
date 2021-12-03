/*
 * CFile1.c
 *
 * Created: 11/29/2021 5:49:16 AM
 *  Author: Upeksha Herath
 */ 

#include "../defines.h"


#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

long USART_BAUDRATE = 9600;

/*
	To initialize the USART connection between two components
*/
void UART_init(long USART_BAUDRATE)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);						// Turn on transmission and reception 
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);	// Use 8-bit character sizes 
	UBRRL = BAUD_PRESCALE;									// Load lower 8-bits of the baud rate value 
	UBRRH = (BAUD_PRESCALE >> 8);							// Load upper 8-bits
}

/*
	To receive data 
*/
unsigned char UART_RxChar()
{
	while ((UCSRA & (1 << RXC)) == 0);	// Wait till data is received 
	return(UDR);						// Return the byte
}

/*
	To Transmit data
*/
void UART_TxChar(char ch)
{
	while (! (UCSRA & (1<<UDRE)));	// Wait for empty transmit buffer
	UDR = ch ;
}

/*
	To send String data
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