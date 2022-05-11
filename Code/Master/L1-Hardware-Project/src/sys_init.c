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
	SPI_Deselect_Slave(SLAVE_SS_0);
	SPI_Master_Init();
	SPI_Select_Slave(SLAVE_SS_0);
	
	I2C_init();
	I2C_start();
	I2C_write(0x70);
	LCD_init();
	LCD_cmd(0x80);
	LCD_msg("Master...");
}
