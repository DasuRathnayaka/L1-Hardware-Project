/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_loop(void) {
	LCD_cmd(0x85);
	LCD_msg("Welcome");
	LCD_cmd(0xC0);
	LCD_msg("Hardware Project");
}

