/*
 * basic.c
 *
 * Created: 10/19/2021 10:10:07 AM
 *  Author: Hansa Jayathilaka
 */ 

#include "../defines.h"


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
int pin_mode(Pin pin, int mode) {
	volatile uint8_t *regi = select_register(pin.port, &DDRA, &DDRB, &DDRC, &DDRD); // Select DDR according to pin
	
	if (mode == 0) { // Check input or output
		*regi &= ~(1 << pin.pin); // Set pin as Input pin
	} else if (mode == 1) {
		*regi |= (1 << pin.pin); // Set pin as Output pin
	} else if (mode == 2){
		// Set pin as Input Pull up
	} else {
		return -1; // Return Error
	}
	return 0;
}
