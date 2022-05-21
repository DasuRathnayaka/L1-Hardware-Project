/*
 * sys_init.c
 *
 * Created: 11/1/2021 10:33:36 PM
 * 
 */

#include "defines.h"


void sys_init(void) {
	I2C_master_init();
	LCD_init();
	
	LCD_clear_msg("Group 47 Slave");
	LCD_line_2();
	LCD_msg("Initializing....");
	_delay_ms(10);
	
	// Siren
	pin_mode(B0, OUTPUT);
	
	ADC_int();
	PWM_init();
	motor_init();
	servo_init();
	SPI_master_init();
	
	ultrazonic_init();
	
	Magneto_init();
	
	UART_init(9600);
	UART_SendString("Starting...");
	
	nrf_init(NRF_MODE_PRX, NRF_RX_PLOAD);
	
	LCD_line_2();
	LCD_msg("Init Completed.");
	_delay_ms(500);
	
	LCD_line_1();
	LCD_msg("Enter Location");
	_delay_ms(500);
	
	char *temp;
	
	LCD_line_1();
	LCD_msg("Longitude       ");
	LCD_line_2();
	char longitude[20];
	key_string(longitude, 20);
	destination.longitude = strtod(longitude, temp);
	
	LCD_line_1();
	LCD_msg("Latitude        ");
	LCD_line_2();
	char latitude[20];
	key_string(latitude, 20);
	destination.latitude = strtod(latitude, temp);
}
