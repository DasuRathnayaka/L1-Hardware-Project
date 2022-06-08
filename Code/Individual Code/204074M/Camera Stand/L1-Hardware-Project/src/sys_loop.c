/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 * 
 */ 

#include "defines.h"

void sys_loop(void) {
	GPS_init();
	
	LCD_clear();
	LCD_line_1();
	LCD_msg("Longi ");
	LCD_msg(get_longi_str());
	LCD_line_2();
	LCD_msg("Lati  ");
	LCD_msg(get_lati_str());
	_delay_ms(1000);
	
	// Calculate angle error from facing direction
	int angle_error = angle_from_north(destination.latitude, destination.longitude) - Magneto_GetHeading();
	
}
