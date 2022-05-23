/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 * 
 */

#include "defines.h"


void sys_init(void) {
	I2C_master_init();
	LCD_init();
	
	LCD_clear_msg("Group 47 Slave");
	LCD_line_2();
	LCD_msg("Initializing....");
	_delay_ms(10);
	
	// Siren
	pin_mode(B0, OUTPUT);
	
	Magneto_init();
	
	UART_init(9600);
	UART_SendString("Starting...");
	
	LCD_line_2();
	LCD_msg("Init Completed.");
	_delay_ms(500);
	
	LCD_line_1();
	LCD_msg("Enter Location");
	_delay_ms(500);
	
	destination.longitude = 80.04396927295906;
	destination.latitude = 7.4702462076787315;
}
