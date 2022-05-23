/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 * 
 */ 

#include "defines.h"

void sys_loop(void) {
		GPS_init();
		
		// Calculate angle error from facing direction
		int angle_error = angle_from_north(destination.latitude, destination.longitude) - Magneto_GetHeading();
		
}
