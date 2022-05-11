/*
 * ADC.c
 *
 * Created: 11/1/2021 10:08:54 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "../defines.h"


/*
 * Initialize ADC registers
 *
 * Parameter
 *	- None
 * Return
 *	- None
 */
void ADC_int(void) {
	ADCSRA = (1 << ADEN); // Enable pin; Enable ADC conversion
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set prescaler select bit; Division Factor 64
	
	ADMUX = (0 << REFS1) | (1 << REFS0); // Reference voltage selection; Select AVCC pin
	ADMUX = (0 << ADLAR); // ADC Left Adjust Result; Set to Right-Justified
}


/*
 * Analog input (0 - 255)
 *
 * Parameter
 *	- pin (Pin) - Input pin eg: A1, B4
 * Return
 *	- (int) - Value of the pin 0 or 255.
 */
int ADC_read(Pin pin) {
	// Change Configuration
	ADMUX = (1 << ADLAR); // ADC Left Adjust Result; Set to Left-Justified
	
	if (pin.port != 'A') { // A port is the only port ADC accessible.
		return 0;
	}
	
	ADMUX &= 0xE0; // Clean multiplexer bits
	ADMUX |= pin.pin; // Set input channel
	
	ADCSRA |= (1 << ADSC); // ADC Start Conversion
	
	uint8_t adif = (1 << ADIF); // Get value of ADC Interrupt Flag
	while((ADCSRA & adif) == 0); // Wait until ADC Interrupt Flag to be 1
	
	int val = ADCH; // Read value
	
	// Change Configuration back to previous
	ADMUX = (0 << ADLAR); // ADC Left Adjust Result; Set to Right-Justified
	
	return val;
}


/*
 * Analog input full value (0 - 1023)
 *
 * Parameter
 *	- pin (Pin) - Input pin eg: A1, B4
 * Return
 *	- (int) - Value of the pin 0 or 1023.
 */
int ADC_read_full(Pin pin) {
	if (pin.port != 'A') { // A port is the only port ADC accessible.
		return 0;
	}
	
	ADMUX &= 0xE0; // Clean multiplexer bits
	ADMUX |= pin.pin; // Set input channel
	
	ADCSRA |= (1 << ADSC); // ADC Start Conversion
	
	uint8_t adif = (1 << ADIF); // Get value of ADC Interrupt Flag
	while((ADCSRA & adif) == 0); // Wait until ADC Interrupt Flag to be 1
	
	int val = 0;
	val |= ADCL; // Get the value of low register
	val |= (ADCH << 8); // Add high register values
	
	return val;
}
