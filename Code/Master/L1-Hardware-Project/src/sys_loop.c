/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"

void sys_loop(void) {

// 	get_latitude();
// 	LCD_line_1();
// 	LCD_msg("Lati: ");
// 	LCD_msg(lati_value);
// 	LCD_line_2();
// 	LCD_msg("Longi:");
// 	LCD_msg(longi_value);									
	
	value=UART_RxChar();
	if(value=='$')
	{
		value=UART_RxChar();
		if(value=='G')
		{
			value=UART_RxChar();
			if(value=='P')
			{
				value=UART_RxChar();
				if(value=='G')
				{
					value=UART_RxChar();
					if(value=='G')
					{
						value=UART_RxChar();
						if(value=='A')
						{
							value=UART_RxChar();
							if(value==',')
							{
								value=UART_RxChar();
								while(value!=',')
								{
									value=UART_RxChar();
								}
								lati_value[0]=UART_RxChar();
								value=lati_value[0];
								for(i=1;value!=',';i++)
								{
									lati_value[i]=UART_RxChar();
									value=lati_value[i];
								}
								lati_dir=UART_RxChar();
								value=UART_RxChar();
								while(value!=',')
								{
									value=UART_RxChar();
								}
								longi_value[0]=UART_RxChar();
								value=longi_value[0];
								for(i=1;value!=',';i++)
								{
									longi_value[i]=UART_RxChar();
									value=longi_value[i];
								}
								longi_dir=UART_RxChar();
											
											
								LCD_line_1();
								LCD_msg("Lati: ");
								LCD_msg(lati_value);
								LCD_line_2();
								LCD_msg("Longi:");
								LCD_msg(longi_value);
							}
						}
					}
				}
			}
		}
	}

}
