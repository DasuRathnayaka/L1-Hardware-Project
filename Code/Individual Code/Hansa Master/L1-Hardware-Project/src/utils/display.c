/*
 * display.c
 *
 * Created: 10/27/2021 4:00:14 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "../defines.h"

#define LCD_ADDRESS 0x70


void toggle() {
	I2C_write(TWDR | 0x02);			// Set enable pin 1;  Latching data in to LCD data register using High to Low signal
	I2C_write(TWDR & ~0x02);		// Set enable pin 0;
}

void LCD_cmd_hf(char val) {
	I2C_write(TWDR & ~0x01);		// Set RS pin to 0; Selecting register as Command register
	I2C_write(TWDR & 0x0F);			// Clearing the Higher 4 bits
	I2C_write(TWDR | (val & 0xF0));	//----Masking higher 4 bits and sending to LCD
	toggle();
}

void LCD_cmd(char val) {
	I2C_write(TWDR & ~0x01);		//rs = 0; ----Selecting register as command register
	I2C_write(TWDR & 0x0F);			//----clearing the Higher 4 bits
	I2C_write(TWDR | (val & 0xF0));	//----Masking higher 4 bits and sending to LCD
	toggle();
	
	I2C_write(TWDR & 0x0F);					//----clearing the Higher 4 bits
	I2C_write(TWDR | ((val & 0x0F) << 4));	//----Masking lower 4 bits and sending to LCD
	toggle();
}

void LCD_dwr(char val) {
	I2C_write(TWDR | 0x01);					//rs = 1; ----Selecting register as command register
	I2C_write(TWDR & 0x0F);				    //----clearing the Higher 4 bits
	I2C_write(TWDR | (val & 0xF0));			//----Masking higher 4 bits and sending to LCD
	toggle();
	
	I2C_write(TWDR & 0x0F);					//----clearing the Higher 4 bits
	I2C_write(TWDR | ((val & 0x0F) << 4));	//----Masking lower 4 bits and sending to LCD
	toggle();
}

void LCD_init() {
	I2C_start();
	I2C_select_slave(LCD_ADDRESS, WRITE);
	
	LCD_cmd_hf(0x30);       //-----Sequence for initializing LCD
	LCD_cmd_hf(0x30);       //-----     "            "              "               "
	LCD_cmd_hf(0x20);       //-----     "            "              "               "
	LCD_cmd(0x28);          //-----Selecting 16 x 2 LCD in 4Bit mode
	LCD_cmd(0x0C);          //-----Display ON Cursor OFF
	LCD_cmd(0x01);          //-----Clear display
	LCD_cmd(0x06);          //-----Cursor Auto Increment
	LCD_cmd(0x80);          //-----1st line 1st location of LCD
	
	I2C_stop();
}

void delay(int ms) {
	int i,j;
	for(i=0;i<=ms;i++)
	for(j=0;j<=120;j++);
}

void LCD_msg(char *c) {
	I2C_start();
	I2C_select_slave(LCD_ADDRESS, WRITE);
	
	while(*c != 0)      //----Wait till all String are passed to LCD
	LCD_dwr(*c++);		//----Send the String to LCD
	
	I2C_stop();
}

void LCD_rig_sh() {
	LCD_cmd(0x1C);      //----Command for right Shift
	delay(400);
}

void LCD_lef_sh() {
	LCD_cmd(0x18);      //----Command for Left Shift
	delay(200);
}

void LCD_clear_msg(char* c) {
	I2C_start();
	I2C_select_slave(LCD_ADDRESS, WRITE);
	
	LCD_cmd(0x01);
	LCD_cmd(0x80);
	
	while(*c != 0)      //----Wait till all String are passed to LCD
		LCD_dwr(*c++);	//----Send the String to LCD
	
	I2C_stop();
}

void LCD_clear() {
	I2C_start();
	I2C_select_slave(LCD_ADDRESS, WRITE);
	
	LCD_cmd(0x01);
	LCD_cmd(0x80);
	
	I2C_stop();
}

void LCD_line_1() {
	I2C_start();
	I2C_select_slave(LCD_ADDRESS, WRITE);
	
	LCD_cmd(0x80);
	
	I2C_stop();
}

void LCD_line_2() {
	I2C_start();
	I2C_select_slave(LCD_ADDRESS, WRITE);
	
	LCD_cmd(0xC0);
	
	I2C_stop();
}