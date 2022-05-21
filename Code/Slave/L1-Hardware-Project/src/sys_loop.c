/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 * 
 */ 

#include "defines.h"


int kp = 5, kq = 5, kr = 30, ks = 10, base_speed = 100;


void sys_loop(void) {
	uint8_t cam_angle, right, forward, siren, auto_mode;
	
	// Get values from nRF
	nrf_rx_data(&cam_angle, &right, &forward, &siren, &auto_mode);
	
	if (auto_mode == 1) {
		// Auto Mode
		
		// Get GPS coordinates
		GPS_init();
		
		// Calculate angle error from facing direction
		int angle_error = angle_from_north(destination) - Magneto_GetHeading();
		
		// Get the direction change occurred by obstacles
		int error = ultrazonic_error();
		
		// Calculate motor speeds with all parameters
		int rPower = base_speed + error * ks + angle_error * kr;
		int lPower = base_speed - error * ks - angle_error * kr;
		
		drive(lPower, rPower);
		servo_write(0);
	} else {
		// Manual Mode
		
		// Calculate motor speeds according to the signals of remote control
		int rPower = forward * kp - right * kq;
		int lPower = forward * kp + right * kq;
		
		// Write speed to motors
		drive(lPower, rPower);
		
		// Rotate servo according to 
		servo_write(cam_angle);
	}
	
	// Start siren when remote siren button pressed
	if (siren == 1)
		digital_write(B0, HIGH);
	else
		digital_write(B0, LOW);
}
