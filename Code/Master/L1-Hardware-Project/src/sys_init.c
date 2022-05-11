/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 *  Author: Hansa Jayathilaka
 */

#include "defines.h"


void sys_init(void) {
	pin_mode(D3, INPUT_PULLUP);
	pin_mode(B1, OUTPUT);
	
	SPI_deselect_slave(SLAVE_SS_0);
	SPI_master_init();
	SPI_select_slave(SLAVE_SS_0);
	
	I2C_init();
	I2C_start();
	I2C_write(0x70);
	LCD_init();
	LCD_cmd(0x80);
	LCD_msg("Master...");
}
