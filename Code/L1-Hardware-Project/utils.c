/*
 * utils.c
 *
 * Created: 10/19/2021 10:10:07 AM
 *  Author: Hansa Jayathilaka
 */ 

#include <avr/io.h>
#include <stdio.h>


/*
 * Use to convert pin number to integer value
 *
 * Parameter
 *	- val (char) - input character
 * Return
 *	- (uint8_t) - 8 bit integer value
 */
uint8_t charToInt(char val) {
	return (uint8_t)(val - '0');
}


/*
 * Select register from given registers according to given input.
 *
 * Parameter
 *	- Registers according to ports (A, B, C, D)
 * Return
 *	- Pointer of selected register.
 */
volatile uint8_t* selectRegister(char portChar, volatile uint8_t* A, volatile uint8_t* B, volatile uint8_t* C, volatile uint8_t* D) {
	switch(portChar) {
		case 'A':
			// PORT A
			return A;
			break;
		case 'B':
			// PORT B
			return B;
			break;
		case 'C':
			// PORT A
			return C;
			break;
		case 'D':
			// PORT A
			return D;
			break;
		default:
			// Error
			return NULL;
	}
}


/*
 * Define a pin weather INPUT or OUTPUT.
 *
 * Parameter
 *	- pin (string) - Input pin eg: A1, B4
 *	- mode (int) - 0 for output, 1 for input
 * Return
 *	- (int) - 0 if no errors.
 */
int pinMode(char* pin, int mode) {
	volatile uint8_t *regi = selectRegister(pin[0], &DDRA, &DDRB, &DDRC, &DDRD);
	uint8_t pinVal = charToInt(pin[1]);
	
	if (mode == 0) {
		*regi &= ~(1 << pinVal);
	} else {
		*regi |= 1 << pinVal;
	}
	return 0;
}


/*
 * Digital output
 *
 * Parameter
 *	- pin (string) - Input pin eg: A1, B4
 *	- level (int) - 1 for high value, 0 for low value
 * Return
 *	- (int) - 0 if no errors.
 */
int digitalWrite(char* pin, int level) {
	volatile uint8_t *regi = selectRegister(pin[0], &PORTA, &PORTB, &PORTC, &PORTD);
	uint8_t pinVal = charToInt(pin[1]);
	
	if (level == 1) {
		*regi |= 1 << pinVal;
	} else {
		*regi &= ~(1 << pinVal);
	}
	return 0;
}


/*
 * Digital input
 *
 * Parameter
 *	- pin (string) - Input pin eg: A1, B4
 * Return
 *	- (int) - Value of the pin 0 or 1.
 */
int digitalRead(char* pin) {
	volatile uint8_t *regi = selectRegister(pin[0], &PINA, &PINB, &PINC, &PIND);
	uint8_t pinVal = charToInt(pin[1]);
	
	int val = *regi & (1 << pinVal);
	if (val == 0) {
		return 0;
	} else {
		return 1;
	}
}


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
 * Analog input
 *
 * Parameter
 *	- pin (string) - Input pin eg: A1, B4
 * Return
 *	- (int) - Value of the pin 0 or 1023.
 */
int analogRead(char* pin) {
	if (pin[0] != 'A') { // A port is the only port ADC accessible.
		return NULL;
	}
	
	uint8_t pinVal = charToInt(pin[1]); // Get pin number
	
	//ADMUX &= 0xE0; // Clean multiplexer bits
	ADMUX |= pinVal; // Set input channel
	
	ADCSRA |= (1 << ADSC); // ADC Start Conversion
	
	uint8_t adif = (1 << ADIF); // Get value of ADC Interrupt Flag
	while((ADCSRA & adif) == 0); // Wait until ADC Interrupt Flag to be 1
	
	int val = 0;
	val |= ADCL; // Get the 
	val |= (ADCH << 8);
	
	return val;
}
