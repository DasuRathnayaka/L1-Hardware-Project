/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"


void sys_loop(void) {
	char B = SPI_Tranceiver(0x10000001);
	LCD_cmd(0x80);
	LCD_msg("Temp");
	
	if (B == 0)
	{
		digital_write(B0,LOW);
		digital_write(B1,HIGH);
		digital_write(B2,LOW);
	}
	
	else if (B == 1)
	{
		digital_write(B0,LOW);
		digital_write(B1,LOW);
		digital_write(B2,HIGH);
	} else {
		
		digital_write(B0,HIGH);
		digital_write(B1,LOW);
		digital_write(B2,LOW);
		char temp[] = "temp";
		temp[0] = B;
		LCD_cmd(0x01);
		LCD_cmd(0x80);
		LCD_msg("Temp");
	}
}
