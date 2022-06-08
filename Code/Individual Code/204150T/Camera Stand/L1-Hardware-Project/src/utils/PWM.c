/*
 * PWM.c
 *
 * Created: 11/1/2021 10:09:46 PM
 *  Author: Sadini Pathirana
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
	// Force compare match
	TCCR0 = (1 << FOC0);
	// Timer0 mode selection bit; Normal, CTC, PWM-Phase correct, [Fast PWM]
	TCCR0 |= (1 << WGM00) | (1 << WGM01);
	// Output Mode; Disconnected, Reserved, [Non-inverted], Inverted (This is only for Fast PWM)
	TCCR0 |= (1 << COM01) | (0 << COM00);
	// Clock Source Select; no pre-scaling
	TCCR0 |= (0 << CS02) | (1 << CS01) | (1 << CS00);
	// Enable Overflow interrupt
	TIMSK |= (1 << TOIE0);
	
	TCCR1A = (1 << COM1A1) | (0 << COM1A0); // A - Compare match mode, Non-Inverted Mode.
	TCCR1A |= (1 << COM1B1) | (0 << COM1B0); // B - Compare match mode, Non-Inverted Mode.
	TCCR1A |= (1 << WGM11) | (0 << WGM10); // Fast PWM mode
	TCCR1B = (1 << WGM13);
	TCCR1B |= (1 << WGM12); // Compare mode
	TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10); // No pre-scaler
	ICR1 = 255;
	
	// Force compare match
	TCCR2 = (1 << FOC2);
	// Timer0 mode selection bit; Normal, CTC, PWM-Phase correct, [Fast PWM]
	TCCR2 |= (1 << WGM20) | (1 << WGM21);
	// Output Mode; Disconnected, Reserved, [Non-inverted], Inverted (This is only for Fast PWM)
	TCCR2 |= (1 << COM21) | (0 << COM20);
	// Clock Source Select; no pre-scaling
	TCCR2 |= (0 << CS22) | (1 << CS21) | (1 << CS20);
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
int PWM_write(Pin pin, int dutyCyle) {
	if (pin.port == 'B' && pin.pin == 3) {
		OCR0 = dutyCyle;
		} else if (pin.port == 'D' && pin.pin == 4) {
		OCR1B = dutyCyle;
		} else if (pin.port == 'D' && pin.pin == 5) {
		OCR1A = dutyCyle;
		} else if (pin.port == 'D' && pin.pin == 7) {
		OCR2 = dutyCyle;
		} else {
		return -1;
	}
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
int PWM_write_reg(void *regi, int dutyCyle) {
	volatile uint8_t *_regi = regi;
	*_regi = dutyCyle;
	return 0;
}
