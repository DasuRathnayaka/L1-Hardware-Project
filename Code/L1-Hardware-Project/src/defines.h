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


typedef struct Pin {
	uint8_t pin;
	char port;
} Pin;

#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

#define HIGH 1
#define LOW 0

#define PWM0A   9    // Left Forward
#define PWM0B   11   // Right Forward
#define DIRA    8    // Left Backward
#define DIRB    10   // Right Backward

int timer0_overflow; // Overflow for Timer 1


Pin A0;
Pin A1;
Pin A2;
Pin A3;
Pin A4;
Pin A5;
Pin A6;
Pin A7;

Pin B0;
Pin B1;
Pin B2;
Pin B3;
Pin B4;
Pin B5;
Pin B6;
Pin B7;

Pin C0;
Pin C1;
Pin C2;
Pin C3;
Pin C4;
Pin C5;
Pin C6;
Pin C7;

Pin D0;
Pin D1;
Pin D2;
Pin D3;
Pin D4;
Pin D5;
Pin D6;
Pin D7;

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

// ADC
void ADC_int(void);
int ADC_read(Pin pin);
int ADC_read_full(Pin pin);

// PWN
void PWM_init(void);
int PWM_write_reg(void *regi, int level);
int PWM_write(Pin pin, int level);

// Display
void LCD_Command(unsigned char cmnd);
void LCD_Char(unsigned char data);
void LCD_Init(void);
void LCD_String(char *str);
void LCD_String_xy (char row, char col, char *str);
void LCD_Clear();
void LCD_Int(int val);
 
#endif
