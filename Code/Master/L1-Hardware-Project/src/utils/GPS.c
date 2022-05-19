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

// unsigned char i;		//Max width of the LCD Display.
// #define RATE 250					//Rate of scrolling.
// void WaitMs(unsigned int ms);		//Declaration of delay routine used.
// void usart_init();
// unsigned int usart_getch();
// unsigned char value,i,lati_value[15],lati_dir, longi_value[15], longi_dir ;

bool IsItGGAString = false;bool flag1 = false;bool flag2 = false;

void convert_time_to_UTC();

void display_latitude_longitude() {
	value=UART_RxChar();
	if(value=='$') {
		value=UART_RxChar();
		if(value=='G') {
			value=UART_RxChar();
			if(value=='P') {
				value=UART_RxChar();
				if(value=='G') {
					value=UART_RxChar();
					if(value=='G') {
						value=UART_RxChar();
						if(value=='A') {
							value=UART_RxChar();
							if(value==',') {
								value=UART_RxChar();
								while(value!=',') {
									value=UART_RxChar();
								}
								lati_value[0]=UART_RxChar();
								value=lati_value[0];
								for(i=1;value!=',';i++) {
									lati_value[i]=UART_RxChar();
									value=lati_value[i];
								}
								lati_dir=UART_RxChar();
								value=UART_RxChar();
								while(value!=',') {
									value=UART_RxChar();
								}
								longi_value[0]=UART_RxChar();
								value=longi_value[0];
								for(i=1;value!=',';i++) {
									longi_value[i]=UART_RxChar();
									value=longi_value[i];
								}
								longi_dir=UART_RxChar();

							}
						}
					}
				}
			}
		}
	}
}




void get_gpstime() {
	cli();
	uint8_t time_index=0;

	/* parse Time in GGA string stored in buffer */
	for(uint8_t index = 0;GGA_Buffer[index]!=','; index++){
		
		Time_Buffer[time_index] = GGA_Buffer[index];
		time_index++;
	}
	convert_time_to_UTC();
	sei();
}

void get_latitude(uint16_t lat_pointer){
	cli();
	uint8_t lat_index;
	uint8_t index = lat_pointer+1;
	lat_index=0;
	
	/* parse Latitude in GGA string stored in buffer */
	for(;GGA_Buffer[index]!=',';index++){
		Latitude_Buffer[lat_index]= GGA_Buffer[index];
		lat_index++;
	}
	
	Latitude_Buffer[lat_index++] = GGA_Buffer[index++];
	Latitude_Buffer[lat_index]   = GGA_Buffer[index];  /* get direction */
	convert_to_degrees(Latitude_Buffer);
	sei();
}

void get_longitude(uint16_t long_pointer){
	cli();
	uint8_t long_index;
	uint8_t index = long_pointer+1;
	long_index=0;
	
	/* parse Longitude in GGA string stored in buffer */
	for( ; GGA_Buffer[index]!=','; index++){
		Longitude_Buffer[long_index]= GGA_Buffer[index];
		long_index++;
	}
	
	Longitude_Buffer[long_index++] = GGA_Buffer[index++];
	Longitude_Buffer[long_index]   = GGA_Buffer[index]; /* get direction */
	convert_to_degrees(Longitude_Buffer);
	sei();
}

void get_altitude(uint16_t alt_pointer){
	cli();
	uint8_t alt_index;
	uint8_t index = alt_pointer+1;
	alt_index=0;
	/* parse Altitude in GGA string stored in buffer */
	for( ; GGA_Buffer[index]!=','; index++){
		Altitude_Buffer[alt_index]= GGA_Buffer[index];
		alt_index++;
	}
	
	Altitude_Buffer[alt_index] = GGA_Buffer[index+1];
	sei();
}
void convert_time_to_UTC()
{
	unsigned int hour, min, sec;
	uint32_t Time_value;
	
	Time_value = atol(Time_Buffer);       /* convert string to integer */
	hour = (Time_value / 10000);          /* extract hour from integer */
	min  = (Time_value % 10000) / 100;    /* extract minute from integer */
	sec  = (Time_value % 10000) % 100;    /* extract second from integer*/

	sprintf(Time_Buffer, "%d:%d:%d", hour,min,sec);
	
}

void convert_to_degrees(char *raw){
	
	double value;
	float decimal_value,temp;
	
	int32_t degrees;
	
	float position;
	value = atof(raw);    /* convert string into float for conversion */
	
	/* convert raw latitude/longitude into degree format */
	decimal_value = (value/100);
	degrees       = (int)(decimal_value);
	temp          = (decimal_value - (int)decimal_value)/0.6;
	position      = (float)degrees + temp;
	
	dtostrf(position, 6, 4, degrees_buffer);  /* convert float value into string */
}


ISR (USART_RXC_vect)
{
	uint8_t oldsrg = SREG;
	cli();
	char received_char = UDR;
	
	if(received_char =='$'){                 /* check for '$' */
		GGA_Index = 0;
		CommaCounter = 0;
		IsItGGAString = false;
	}
	else if(IsItGGAString == true){          /* if true save GGA info. into buffer */
		if(received_char == ',' ) GGA_Pointers[CommaCounter++] = GGA_Index;     /* store instances of ',' in buffer */
		GGA_Buffer[GGA_Index++] = received_char;
	}
	else if(GGA_CODE[0] == 'G' && GGA_CODE[1] == 'G' && GGA_CODE[2] == 'A'){    /* check for GGA string */
		IsItGGAString = true;
		GGA_CODE[0] = 0; GGA_CODE[1] = 0; GGA_CODE[2] = 0;
	}
	else{
		GGA_CODE[0] = GGA_CODE[1];  GGA_CODE[1] = GGA_CODE[2]; GGA_CODE[2] = received_char;
	}
	SREG = oldsrg;
}










