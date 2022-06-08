/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 * 
 */

#include "defines.h"


void sys_init(void) {
	SPI_master_init();
	pin_mode(B4, OUTPUT);
	
	SPI_select_slave(B4);
}
