/*
 * PWM.c
 *
 * Created: 11/1/2021 10:09:46 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "../defines.h"


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
int PWM_write(Pin pin, int level) {
	volatile uint8_t *regi;
	if (pin.port == 'B' && pin.pin == '3') {
		regi = &OCR0;
	} else if (pin.port == 'D' && pin.pin == '4') {
		regi = &OCR1B;
	} else if (pin.port == 'D' && pin.pin == '5') {
		regi = &OCR1A;
	} else if (pin.port == 'D' && pin.pin == '7') {
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
