/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_loop(void) {
	uint8_t siren = btn_siren();
	uint8_t auto_manual_mode = btn_mode();
	
	LCD_line_1();
	if (siren == 1) LCD_msg("Siren ON        "); else LCD_msg("Siren OFF       ");
	
	LCD_line_2();
	if (auto_manual_mode == 1) LCD_msg("Auto Mode       "); else LCD_msg("Manual Mode     ");
}
