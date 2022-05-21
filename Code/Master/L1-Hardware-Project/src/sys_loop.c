/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"

void sys_loop(void) {

// 	get_latitude();
// 	LCD_line_1();
// 	LCD_msg("Lati: ");
// 	LCD_msg(lati_value);
// 	LCD_line_2();
// 	LCD_msg("Longi:");
// 	LCD_msg(longi_value);									
	GPS_init();
	LCD_line_1();
	LCD_msg("Angle:");
	sprintf(c, "%d", angle_from_north(8.3114, 80.4037));
	LCD_msg(c);
	LCD_msg(output);
	
	//LCD_msg(get_lati_str());
// 	LCD_line_2();
// 	LCD_msg("Lon:");
// 	LCD_msg(get_longi_str());
}
