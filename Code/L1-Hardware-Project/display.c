/*
 * display.c
 *
 * Created: 10/27/2021 4:00:14 PM
 *  Author: Hansa Jayathilaka
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

/*

Pin Configuration.
+---------+-------------+
| Display |    Atmel    | 
|---------+-------------|
|VSS      | GND         |
|VCC      | 5v          |
|VEE      | 10K Preset  | 
|RS       | B0          |
|RW       | GND         |
|En       | B1          |
|D4       | D4          |
|D5       | D5          |
|D6       | D6          |
|D7       | D7          |
+---------+-------------+

*/

#define LCD_Dir  DDRB // Define LCD data port direction
#define LCD_Port PORTB // Define LCD data port
#define RS PB0 // Define Register Select pin
#define EN PB1 // Define Enable signal pin

void LCD_Command(unsigned char cmnd) {
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); // Sending upper nibble
	LCD_Port &= ~ (1 << RS); // RS=0, command reg.
	LCD_Port |= (1 << EN);  // Enable pulse
	_delay_us(1);
	LCD_Port &= ~ (1 << EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4); // Sending lower nibble
	LCD_Port |= (1 << EN);
	_delay_us(1);
	LCD_Port &= ~(1 << EN);
	_delay_ms(2);
}


void LCD_Char(unsigned char data) {
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); // sending upper nibble
	LCD_Port |= (1 << RS); // RS=1, data reg.
	LCD_Port |= (1 << EN);
	_delay_us(1);
	LCD_Port &= ~ (1 << EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4); // Sending lower nibble
	LCD_Port |= (1 << EN);
	_delay_us(1);
	LCD_Port &= ~ (1 << EN);
	_delay_ms(2);
}

void LCD_Init(void) { // LCD Initialize function
	LCD_Dir = 0xFF; // Make LCD port direction as o/p
	_delay_ms(20); // LCD Power ON delay always >15ms
	
	LCD_Command(0x02); // send for 4 bit initialization of LCD
	LCD_Command(0x28); // 2 line, 5*7 matrix in 4-bit mode
	LCD_Command(0x0c); // Display on cursor off
	LCD_Command(0x06); // Increment cursor (shift cursor to right)
	LCD_Command(0x01); // Clear display screen
	_delay_ms(2);
}


void LCD_String(char *str) { // Send string to LCD function
	int i;
	for(i=0;str[i]!=0;i++) // Send each char of string till the NULL
	{
		LCD_Char(str[i]);
	}
}

void LCD_String_xy (char row, char col, char *str) { // Send string to LCD with x, y position
	if (row == 0 && col<16)
		LCD_Command((col & 0x0F)|0x80); // Command of first row and required position < 16
	else if (row == 1 && col<16)
		LCD_Command((col & 0x0F) | 0xC0); // Command of first row and required position < 16
	LCD_String(str); // Call LCD string function
}

void LCD_Clear() {
	LCD_Command(0x01); // Clear display
	_delay_ms(2);
	LCD_Command(0x80); // Cursor at home position
}

void LCD_Int(int val) {
	char str[16];
	itoa(val, str, 16);
	LCD_Clear();
	LCD_String(str);
}
