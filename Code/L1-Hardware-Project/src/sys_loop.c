/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"

void sys_loop(void) {
		
	_delay_ms(1000);
	LCD_String_xy(1,0,"UTC Time: ");
	get_gpstime();                   /* Extract Time in UTC */
	LCD_String(Time_Buffer);
	LCD_String("  ");
	
	LCD_String_xy(2,0,"Lat: ");
	get_latitude(GGA_Pointers[0]);   /* Extract Latitude */
	LCD_String(degrees_buffer);      /* display latitude in degree */
	memset(degrees_buffer,0,degrees_buffer_size);
	
	LCD_String_xy(3,0,"Long: ");
	get_longitude(GGA_Pointers[2]);  /* Extract Longitude */
	LCD_String(degrees_buffer);      /* display longitude in degree */
	memset(degrees_buffer,0,degrees_buffer_size);
	
	LCD_String_xy(4,0,"Alt: ");
	get_altitude(GGA_Pointers[7]);   /* Extract Altitude in meters*/
	LCD_String(Altitude_Buffer);

		
	
}
