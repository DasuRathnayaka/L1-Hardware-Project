/*
 * I2C.c
 *
 * Created: 5/10/2022 8:59:24 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "../defines.h"


void I2C_wait_to_process() {
	while ((TWCR & (1 << TWINT)) == 0);
}


/************************************************************************/
/* Master                                                               */
/************************************************************************/

void I2C_master_init() {
	TWBR = 0x62;		// Baud rate is set by calculating
	TWCR = (1 << TWEN);	// Enable I2C
	TWSR = 0x00;		// Pre-scaler set to 1
}

//Start condition
void I2C_start() {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);	//start condition
	I2C_wait_to_process();
}

//I2C stop condition
void I2C_write(unsigned char x) {
	TWDR = x;						//Move value to I2C
	TWCR = (1 << TWINT) | (1 << TWEN);	//Enable I2C and clear interrupt
	I2C_wait_to_process();
}

void I2C_select_slave(unsigned char address, int mode) {
	I2C_write(address + mode);
}

void I2C_stop() {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	// while((TWCR & (1<<TWSTO)) == 1);		// No need to wait
}

void I2C_master_write_buffer(unsigned char address, char* buffer, int length) {
	I2C_start();
	I2C_select_slave(address, WRITE);
	for(char* i = buffer; i < buffer + length; i++) {
		I2C_write(*i);
	}
	I2C_stop();
}

/************************************************************************/
/* End Master                                                           */
/************************************************************************/


/************************************************************************/
/* Slave                                                                */
/************************************************************************/

void I2C_slave_init(unsigned char address) {
	TWAR = address;		// Set slave address
}

void I2C_listen(void) {
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);	// Enable; Interrupt; Acknowledgment;
	I2C_wait_to_process();
}

// Read byte with NACK
unsigned char I2C_read() {
	TWCR  = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);	// Enable; Interrupt; Acknowledgment;
	I2C_wait_to_process();
	return TWDR;
}

void I2C_slave_read_buffer(char* buffer, int length) {
	I2C_listen();
	for(char* i = buffer; i < buffer + length; i++) {
		*i = I2C_read();
	}
	I2C_listen();
}

/************************************************************************/
/* End Slave                                                            */
/************************************************************************/
