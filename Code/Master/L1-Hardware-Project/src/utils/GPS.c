/*
    GPS Information extraction using ATmega16/32 
	Author : Upeksha Herath
*/

#include "../defines.h"

#define BAUD 9600       //BAUDRATE = 9600

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*This will initialize the gps values according to the current GPS cordinates*/
void GPS_init() {
	int flag = 0;
	while (flag != 1) {
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
									flag = 1;
									
								} else {
									continue;
								}
							} else {
								continue;
							}
						} else {
							continue;
						}
					} else {
						continue;
					}
				} else {
					continue;
				}
			} else {
				continue;
			}
		} else {
			continue;
		}
	}
}

char* get_lati() {
	return lati_value;//lati_value;
}

char* get_longitude() {
	return longi_value;//longi_value;
}



