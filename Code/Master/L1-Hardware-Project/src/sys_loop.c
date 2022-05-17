/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"

void sys_loop(void) {

	get_latitude();
	LCD_line_1();
	LCD_msg("Lati: ");
	LCD_msg(lati_value);
	LCD_line_2();
	LCD_msg("Longi:");
	LCD_msg(longi_value);									

}
