/*
 * sys_loop.c
 *
 * Created: 11/1/2021 10:35:03 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"

int i = 0;
void sys_loop(void) {
	//LCD_String("Group - 47");
	//_delay_ms(500000);
	/*int val = ADC_read(A0);
	LCD_Int(time_us());*/

	// int val = ADC_read(A0);
	// LCD_Int(val);
	/*PWM_write(B3, val);
	PWM_write(D4, val);
	PWM_write(D5, val);
	PWM_write(D7, val);*/
	/*OCR0 = val;
	OCR1AH = (val * 4) >> 8;
	OCR1AL = val;
	OCR1BH = (val * 4) >> 8;
	OCR1BL = val;
	OCR2 = val;
	_delay_ms(100);*/
	/*LCD_Clear();
	LCD_String("0");
	OCR0 = 0;
	OCR1AH = 0;
	OCR1AL = 0;
	OCR1BH = 0;
	OCR1BL = 0;
	OCR2 = 0;
	_delay_ms(1000);

	LCD_Clear();
	LCD_String("255");
	OCR0 = 255;
	OCR1AH = 255;
	OCR1AL = 255;
	OCR1BH = 255;
	OCR1BL = 255;
	OCR2 = 255;
	_delay_ms(1000);*/
	/*if (i == 0) {
		OCR0++;
		if (OCR0 == 254) {
			i = 1;
		}
	} else {
		OCR0--;
		if (OCR0 == 0) {
			i = 0;
		}
	}*/
	/*
	if (i == 0) {
		OCR1B++;
		if (OCR1B == 254) {
			i = 1;
		}
		} else {
		OCR1B--;
		if (OCR1B == 0) {
			i = 0;
		}
	}*/
	/*
	if (i == 0) {
		OCR1A++;
		if (OCR1A == 254) {
			i = 1;
		}
		} else {
		OCR1A--;
		if (OCR1A == 0) {
			i = 0;
		}
	}
	*/
	/*
	if (i == 0) {
		OCR2++;
		if (OCR2 == 254) {
			i = 1;
		}
		} else {
		OCR2--;
		if (OCR2 == 0) {
			i = 0;
		}
	}
	_delay_ms(10);*/

	// PWM_write_reg(&OCR1A, val);


	/*digital_write(C3, HIGH);
	_delay_ms(500);
	digital_write(C3, LOW);
	_delay_ms(500);*/
	#define Buffer_Size 150
	#define degrees_buffer_size 20
	
	GGA_Index=0;
	memset(GGA_Buffer, 0, Buffer_Size);
	memset(degrees_buffer,0,degrees_buffer_size);
	
	LCD_Init();              /* initialize LCD16x2 */
	_delay_ms(3000);         /* wait for GPS receiver to initialize */
	UART_init(9600);        /* initialize USART with 9600 baud rate */
	sei();
	LCD_Clear();
	
	while (1)
	{
		_delay_ms(1000);
		
		LCD_String_xy(1,0,"Lat: ");
		get_latitude(GGA_Pointers[0]);   /* Extract Latitude */
		LCD_String(degrees_buffer);      /* display latitude in degree */
		memset(degrees_buffer,0,degrees_buffer_size);
		
		LCD_String_xy(2,0,"Long: ");
		get_longitude(GGA_Pointers[2]);  /* Extract Longitude */
		LCD_String(degrees_buffer);      /* display longitude in degree */
		memset(degrees_buffer,0,degrees_buffer_size);
		
		
	}
}
