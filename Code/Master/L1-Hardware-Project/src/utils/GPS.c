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

void convert_time_to_UTC();
void convert_to_degrees(char *);


void get_gpstime(){
	cli();
	uint8_t time_index=0;

	/* parse Time in GGA string stored in buffer */
	for(uint8_t index = 0;GGA_Buffer[index]!=','; index++) {
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

