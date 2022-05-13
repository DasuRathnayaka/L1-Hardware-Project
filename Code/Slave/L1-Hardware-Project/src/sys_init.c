/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 *  Author: Hansa Jayathilaka
 */

#include "defines.h"


void sys_init(void) {
	pin_mode(B0, OUTPUT);
	pin_mode(B1, OUTPUT);
	
	SPI_slave_init();
	
	I2C_slave_init(MY_ADDRESS);
	// I2C_start();
	
	// LCD_init();
	// LCD_clear_msg("Slave...");
}
