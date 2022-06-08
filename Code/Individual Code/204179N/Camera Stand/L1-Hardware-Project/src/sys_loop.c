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
}
