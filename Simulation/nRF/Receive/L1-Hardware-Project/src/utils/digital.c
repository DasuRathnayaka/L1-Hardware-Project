/*
 * digital.c
 *
 * Created: 11/1/2021 10:10:53 PM
 *  
 */ 

#include "../defines.h"


/*
 * Digital output
 *
 * Parameter
 *	- pin (string) - Input pin eg: A1, B4
 *	- level (int) - 1 for high value, 0 for low value
 * Return
 *	- (int) - 0 if no errors.
 */
int digital_write(Pin pin, int level) {
	volatile uint8_t *regi = select_register(pin.port, &PORTA, &PORTB, &PORTC, &PORTD); // Select PORT register according to pin
	
	if (level == 1) { // Check weather high or low
		*regi |= 1 << pin.pin; // Output high value
	} else {
		*regi &= ~(1 << pin.pin); // Output low value
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
int digital_read(Pin pin) {
	volatile uint8_t *regi = select_register(pin.port, &PINA, &PINB, &PINC, &PIND); // Select PIN register according to pin
	
	int val = *regi & (1 << pin.pin); // Get value of the register
	if (val == 0) { // Check weather the value is high or low
		return 0; // Return low value
	} else {
		return 1; // Return high value
	}
}
