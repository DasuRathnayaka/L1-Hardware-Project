/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 *  Author: Hansa Jayathilaka
 */

#include "defines.h"


void sys_init(void) {
	SPI_slave_init();
	
	I2C_init();
	I2C_start();
	I2C_write(0x70);
	LCD_init();
	LCD_cmd(0x80);
	LCD_msg("Slave...");
}
