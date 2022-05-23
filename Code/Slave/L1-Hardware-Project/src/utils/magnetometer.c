/*
 * magnetometer.c
 *
 * Created: 4/20/2022 9:53:22 AM
 *  Author: Upeksha Herath
 */ 

#include "../defines.h"

#define PI	3.14159265359	/* Define Pi value */
#define Declination	-0.00669/* Define declination of location from where measurement going to be done.*/


void Magneto_init()		/* Magneto initialize function */
{
	I2C_select_slave(0x3C, WRITE);	/* Start and write SLA+W */
	
	I2C_write(0x00);	/* Write memory location address */
	I2C_write(0x70);	/* Configure register A as 8-average, 15 Hz default, normal measurement */
	I2C_write(0xA0);	/* Configure register B for gain */
	I2C_write(0x00);	/* Configure continuous measurement mode in mode register */
	I2C_stop();		/* Stop I2C */
}


int Magneto_GetHeading()
{
	int x, y, z;
	double Heading;
	I2C_start();
	I2C_select_slave(0x3C, WRITE);
	
	I2C_write(0x3C);	/* Start and wait for acknowledgment */
	I2C_write(0x03);	/* Write memory location address */
	
	/* Read 16 bit x,y,z value (2's complement form) */
	x = (((int)I2C_read()<<8) | (int)I2C_read());
	z = (((int)I2C_read()<<8) | (int)I2C_read());
	y = (((int)I2C_read()<<8) | (int)I2C_read());
	I2C_stop();		/* Stop I2C */
	Heading = atan2((double)y,(double)x) + Declination;
	if (Heading>2*PI)	/* Due to declination check for >360 degree */
	Heading = Heading - 2*PI;
	if (Heading<0)		/* Check for sign */
	Heading = Heading + 2*PI;
	return (Heading* 180 / PI);/* Convert into angle and return */
}
