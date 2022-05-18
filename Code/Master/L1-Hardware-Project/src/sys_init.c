/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 *  Author: Hansa Jayathilaka
 */

#include "defines.h"


void sys_init(void) {
	pin_mode(B0, OUTPUT);
	pin_mode(B4, OUTPUT);
	pin_mode(D4, OUTPUT);
	pin_mode(D5, OUTPUT);
	pin_mode(D7, OUTPUT);
	
	PWM_init();
	ADC_int();
	SPI_master_init();
	motor_init();
	
	I2C_master_init();
	LCD_init();
	LCD_clear_msg("Hello World");
	_delay_ms(10);
}
