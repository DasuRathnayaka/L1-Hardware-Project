/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_loop(void) {
	LCD_Init();
	LCD_String("Upeksha Dilshan");
	LCD_Clear();
	UART_init(9600);
}
