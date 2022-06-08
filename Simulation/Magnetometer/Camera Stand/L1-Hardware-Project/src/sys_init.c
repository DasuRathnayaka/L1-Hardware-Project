/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 * 
 */

#include "defines.h"


void sys_init(void) {
	I2C_slave_init(0x22);
	UART_init(9600);
// 	LCD_init();
// 	
// 	LCD_clear_msg("Group 47 Slave");
// 	LCD_line_2();
// 	LCD_msg("Initializing....");
// 	_delay_ms(10);
}
