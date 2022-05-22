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
#include <math.h>

//This will initialize the GPS values according to the current GPS coordinates
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

//give latitude value as a string
char* get_lati_str() {
	return lati_value;	//lati_value;
}

//give longitude value as a string 
char* get_longi_str() {
	return longi_value;	//longi_value;
}

//give latitude value as a double 
float get_lati_float() {
	for (int i = 0; i < 15; i++) {
		if (lati_value[i] == ',') {
			lati_value[i] = '0';
		}
	}
	float correct_lati_value =  atof(lati_value) / 100;
	return correct_lati_value;
}

//give longitude value as a double
float get_longi_float() {
	for (int i = 0; i < 15; i++) {
		if (longi_value[i] == ',') {
			longi_value[i] = '0';
		}
	}
	/*how to convert a latitude value to degrees*/
	float correct_longi_value = atof(longi_value) / 100;
	return correct_longi_value;
}

/* take the inputed GPS coordinate and value and compare with inputted*/
int angle_from_north(float lati_input, float longi_input) {
	float dy = lati_input - get_lati_float();
	float dx = cos(PI / 180 * get_lati_float()) * (longi_input - get_longi_float());
	float angle = dy / dx;
	int temp = angle;
	return angle;
}




