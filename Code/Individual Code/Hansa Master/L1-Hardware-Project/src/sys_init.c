/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 *  Author: Hansa Jayathilaka
 */

#include "defines.h"


void sys_init(void) {
	I2C_master_init();
	LCD_init();

	LCD_clear_msg("Group 47 Master");
	LCD_line_2();
	LCD_msg("Initializing....");
	_delay_ms(10);

	btn_init();
	
	LCD_line_2();
	LCD_msg("Init Completed.");
	_delay_ms(500);

	LCD_line_2();
	LCD_msg("Running         ");
}
