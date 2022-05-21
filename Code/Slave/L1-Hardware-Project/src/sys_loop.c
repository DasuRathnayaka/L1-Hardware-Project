/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


int kp = 5, kq = 5, base_speed = 100, kr = 30;


void sys_loop(void) {
	uint8_t cam_angle, right, forward, siren, auto_mode;
	nrf_rx_data(&cam_angle, &right, &forward, &siren, &auto_mode);
	
	if (auto_mode == 1) {
		// Auto Mode
		int error = ultrazonic_error();
		int angle_error = 0;
		
		int rPower = base_speed + error + angle_error * kr;
		int lPower = base_speed - error - angle_error * kr;
		
		drive(lPower, rPower);
		servo_write(0);
	} else {
		// Manual Mode
		int rPower = forward * kp - right * kq;
		int lPower = forward * kp + right * kq;
		
		drive(lPower, rPower);
		servo_write(cam_angle);
	}
	
	if (siren == 1)
		digital_write(B0, HIGH);
	else
		digital_write(B0, LOW);
}
