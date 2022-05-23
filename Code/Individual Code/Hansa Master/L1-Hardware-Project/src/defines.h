/*
 * pins.h
 *
 * Created: 10/19/2021 2:04:21 PM
 *  Author: Hansa Jayathilaka
 */ 

#ifndef DEFINES_H
#define DEFINES_H

#define F_CPU 8000000UL

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>


typedef struct Pin {
	uint8_t pin;
	char port;
} Pin;

#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

#define HIGH 1
#define LOW 0

// I2C
#define MY_ADDRESS 0xCC
#define READ 1
#define WRITE 0

unsigned long timer0_overflow;


const Pin A0;
const Pin A1;
const Pin A2;
const Pin A3;
const Pin A4;
const Pin A5;
const Pin A6;
const Pin A7;

const Pin B0;
const Pin B1;
const Pin B2;
const Pin B3;
const Pin B4;
const Pin B5;
const Pin B6;
const Pin B7;

const Pin C0;
const Pin C1;
const Pin C2;
const Pin C3;
const Pin C4;
const Pin C5;
const Pin C6;
const Pin C7;

const Pin D0;
const Pin D1;
const Pin D2;
const Pin D3;
const Pin D4;
const Pin D5;
const Pin D6;
const Pin D7;

// Main initialization and loop
void sys_init(void);
void sys_loop(void);

// Basic definitions
uint8_t char_to_int(char val);
volatile uint8_t* select_register(char portChar, volatile uint8_t* A, volatile uint8_t* B, volatile uint8_t* C, volatile uint8_t* D);
int pin_mode(Pin pin, int mode);
unsigned long time_ms();
unsigned long time_us();

// Digital utilities
int digital_write(Pin pin, int level);
int digital_read(Pin pin);

// Display
void LCD_init();
void LCD_msg(char *c);
void LCD_clear_msg(char* c);
void LCD_clear();
void LCD_line_1();
void LCD_line_2();

// I2C
void I2C_master_init();
void I2C_slave_init(unsigned char address);
void I2C_start();
void I2C_stop();
void I2C_write(unsigned char x);
void I2C_select_slave(unsigned char address, int mode);
void I2C_listen(void);
unsigned char I2C_read();
void I2C_slave_read_buffer(char* buffer, int length);
void I2C_master_write_buffer(unsigned char address, char* buffer, int length);

// Button
void btn_init(void);
uint8_t btn_mode();
uint8_t btn_siren();

#endif
