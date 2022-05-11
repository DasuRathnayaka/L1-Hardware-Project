/*
 * I2C.c
 *
 * Created: 5/10/2022 8:59:24 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "../defines.h"


void I2C_init() {
	TWBR = 0x62;		// Baud rate is set by calculating
	TWCR = (1 << TWEN);	// Enable I2C
	TWSR = 0x00;		// Pre-scaler set to 1
}


//Start condition
void I2C_start() {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);	//start condition
	while ((TWCR & (1 << TWINT)) == 0);				//check for start condition
}


void I2C_stop() {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	while((TWCR & (1<<TWSTO)) == 1);
}


//I2C stop condition
void I2C_write(char x) {				//Cpn esta funcion se escribe en el bus de TWDR
	TWDR = x;						//Move value to I2C
	TWCR = (1 << TWINT) | (1 << TWEN);	//Enable I2C and clear interrupt
	while  ((TWCR &(1 << TWINT)) == 0);
}


// Read byte with NACK
char I2C_read() {
	TWCR  = (1 << TWEN) | (1 << TWINT);	//Enable I2C and clear interrupt
	while ((TWCR & (1 << TWINT)) == 0);	//Read successful with all data received in TWDR
	return TWDR;
}
