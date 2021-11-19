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
uint8_t char_to_int(char val) {
	return (uint8_t)(val - '0'); // Convert char to int
}


/*
 * Select register from given registers according to given input.
 *
 * Parameter
 *	- Registers according to ports (A, B, C, D)
 * Return
 *	- Pointer of selected register.
 */
volatile uint8_t* select_register(char portChar, volatile uint8_t* A, volatile uint8_t* B, volatile uint8_t* C, volatile uint8_t* D) {
	switch(portChar) { // Select register
		case 'A':
			// PORT A
			return A;
			break;
		case 'B':
			// PORT B
			return B;
			break;
		case 'C':
			// PORT C
			return C;
			break;
		case 'D':
			// PORT D
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
 *	- mode (int) - 0 for output, 1 for input (INPUT, OUTPUT, INPUT_PULLUP)
 * Return
 *	- (int) - 0 if no errors.
 */
int pin_mode(char* pin, int mode) {
	volatile uint8_t *regi = select_register(pin[0], &DDRA, &DDRB, &DDRC, &DDRD); // Select DDR according to pin
	uint8_t pin_val = char_to_int(pin[1]); // Get pin number
	
	if (mode == 0) { // Check input or output
		*regi &= ~(1 << pin_val); // Set pin as Input pin
	} else if (mode == 1) {
		*regi |= 1 << pin_val; // Set pin as Output pin
	} else if (mode == 2){
		// Set pin as Input Pull up
	} else {
		return -1; // Return Error
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
int digital_write(char* pin, int level) {
	volatile uint8_t *regi = select_register(pin[0], &PORTA, &PORTB, &PORTC, &PORTD); // Select PORT register according to pin
	uint8_t pin_val = char_to_int(pin[1]); // Get pin number
	
	if (level == 1) { // Check weather high or low
		*regi |= 1 << pin_val; // Output high value
	} else {
		*regi &= ~(1 << pin_val); // Output low value
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
int digital_read(char* pin) {
	volatile uint8_t *regi = select_register(pin[0], &PINA, &PINB, &PINC, &PIND); // Select PIN register according to pin
	uint8_t pin_val = char_to_int(pin[1]); // Get pin number
	
	int val = *regi & (1 << pin_val); // Get value of the register
	if (val == 0) { // Check weather the value is high or low
		return 0; // Return low value
	} else {
		return 1; // Return high value
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
 * Analog input (0 - 255)
 *
 * Parameter
 *	- pin (string) - Input pin eg: A1, B4
 * Return
 *	- (int) - Value of the pin 0 or 1023.
 */
int ADC_read(char* pin) {
	// Change Configuration
	ADMUX = (1 << ADLAR); // ADC Left Adjust Result; Set to Left-Justified
	
	if (pin[0] != 'A') { // A port is the only port ADC accessible.
		return NULL;
	}
	
	uint8_t pin_val = char_to_int(pin[1]); // Get pin number
	
	ADMUX &= 0xE0; // Clean multiplexer bits
	ADMUX |= pin_val; // Set input channel
	
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
 *	- pin (string) - Input pin eg: A1, B4
 * Return
 *	- (int) - Value of the pin 0 or 1023.
 */
int ADC_read_full(char* pin) {
	if (pin[0] != 'A') { // A port is the only port ADC accessible.
		return NULL;
	}
	
	uint8_t pin_val = char_to_int(pin[1]); // Get pin number
	
	ADMUX &= 0xE0; // Clean multiplexer bits
	ADMUX |= pin_val; // Set input channel
	
	ADCSRA |= (1 << ADSC); // ADC Start Conversion
	
	uint8_t adif = (1 << ADIF); // Get value of ADC Interrupt Flag
	while((ADCSRA & adif) == 0); // Wait until ADC Interrupt Flag to be 1
	
	int val = 0;
	val |= ADCL; // Get the value of low register
	val |= (ADCH << 8); // Add high register values
	
	return val;
}


/*
 * Initialize PWN settings
 *
 * Parameter
 *	- None
 * Return
 *	- None
 */
void PWM_init(void) {
	TCCR0 = (1 << FOC0); // Force compare match
	TCCR0 |= (1 << WGM00) | (1 << WGM01); // Timer0 mode selection bit; Normal, CTC, PWM-Phase correct, [Fast PWM]
	TCCR0 |= (1 << COM01) | (0 << COM00); // Output Mode; Disconnected, Reserved, [Non-inverted], Inverted (This is only for Fast PWM)
	TCCR0 |= (0 << CS02) | (0 << CS01) | (1 << CS00); // Clock Source Select; no pre-scaling
}


/*
 * Analog output from pin
 *
 * Parameter
 *	- pin (string) - Input pin eg: B3, D4, D5, D7
 *	- level (int) - Value between 0 - 255
 * Return
 *	- (int) - 0 if no errors.
 */
int PWM_write(char* pin, int level) {
	volatile uint8_t *regi;
	if (pin[0] == 'B' && pin[1] == '3') {
		regi = &OCR0;
	} else if (pin[0] == 'D' && pin[1] == '4') {
		regi = &OCR1B;
	} else if (pin[0] == 'D' && pin[1] == '5') {
		regi = &OCR1A;
	} else if (pin[0] == 'D' && pin[1] == '7') {
		regi = &OCR2;
	} else {
		return -1;
	}
	
	*regi = level;
	return 0;
}


/*
 * Analog output from register
 *
 * Parameter
 *	- regi (string) - Register eg: OCR0, OCR1B, OCR1A, OCR2
 *	- level (int) - Value between 0 - 255
 * Return
 *	- (int) - 0 if no errors.
 */
int PWM_write_reg(volatile uint8_t *regi, int level) {
	*regi = level;
	return 0;
}
