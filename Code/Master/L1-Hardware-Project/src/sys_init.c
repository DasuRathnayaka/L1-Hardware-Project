/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 *  Author: Hansa Jayathilaka
 */

#include "defines.h"

void sys_init(void) {
	sei();  //Enable global interrupt
	
	pin_mode(D0, INPUT);
	pin_mode(C6, OUTPUT);
	
	PWM_init();
	ADC_int();
	I2C_master_init();
	LCD_init();
	LCD_msg("Group - 47");
	_delay_ms(50);
	
	LCD_init();
	//_delay_ms(3000);         /* wait for GPS receiver to initialize */
	UART_init(9600);        /* initialize USART with 9600 baud rate */
	LCD_clear();
	
	DDRD = 0xFF;
	DDRC = 0xFF;	
	
	GGA_Index=0;
	memset(GGA_Buffer, 0, Buffer_Size);
	memset(degrees_buffer,0,degrees_buffer_size);
	
	//GPS 2
	_delay_ms(3000);         /* wait for GPS receiver to initialize */
	sei();
}



