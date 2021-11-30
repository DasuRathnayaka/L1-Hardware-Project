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
	// TCCR0 |= (1 << WGM00) | (1 << WGM01); // Timer0 mode selection bit; Normal, CTC, PWM-Phase correct, [Fast PWM]
	TCCR0 |= (1 << WGM00) | (0 << WGM01); // Timer0 mode selection bit; Normal, CTC, [PWM-Phase correct], Fast PWM
	// TCCR0 |= (1 << COM01) | (0 << COM00); // Output Mode; Disconnected, Reserved, [Non-inverted], Inverted (This is only for Fast PWM)
	TCCR0 |= (1 << COM01) | (0 << COM00); // Output Mode; Disconnected, Reserved, [Non-inverted], Inverted (This is only for Fast PWM)
	TCCR0 |= (0 << CS02) | (1 << CS01) | (1 << CS00); // Clock Source Select; no pre-scaling
	TIMSK |= (1 << TOIE0); // Enable Overflow interrupt
	
	/*
	TCCR1A = (0 << FOC0); // Force compare match
	TCCR1A |= (1 << WGM00) | (1 << WGM01); // Timer0 mode selection bit; Normal, CTC, PWM-Phase correct, [Fast PWM]
	TCCR1A |= (1 << COM01) | (0 << COM00); // Output Mode; Disconnected, Reserved, [Non-inverted], Inverted (This is only for Fast PWM)
	TCCR1A |= (0 << CS02) | (0 << CS01) | (1 << CS00); // Clock Source Select; no pre-scaling
	
	TCCR1B = (0 << FOC0); // Force compare match
	TCCR1B |= (1 << WGM00) | (1 << WGM01); // Timer0 mode selection bit; Normal, CTC, PWM-Phase correct, [Fast PWM]
	TCCR1B |= (1 << COM01) | (0 << COM00); // Output Mode; Disconnected, Reserved, [Non-inverted], Inverted (This is only for Fast PWM)
	TCCR1B |= (0 << CS02) | (0 << CS01) | (1 << CS00); // Clock Source Select; no pre-scaling
	*/
	/*
	TCCR2 = (0 << FOC0); // Force compare match
	TCCR2 |= (1 << WGM00) | (1 << WGM01); // Timer0 mode selection bit; Normal, CTC, PWM-Phase correct, [Fast PWM]
	TCCR2 |= (1 << COM01) | (0 << COM00); // Output Mode; Disconnected, Reserved, [Non-inverted], Inverted (This is only for Fast PWM)
	TCCR2 |= (0 << CS02) | (0 << CS01) | (1 << CS00); // Clock Source Select; no pre-scaling
	*/
	/*
	TCCR2 = (0 << FOC2); // Force compare match
	TCCR2 |= (1 << WGM20) | (1 << WGM21); // Timer0 mode selection bit; Normal, CTC, PWM-Phase correct, [Fast PWM]
	TCCR2 |= (1 << COM21) | (0 << COM20); // Output Mode; Disconnected, Reserved, [Non-inverted], Inverted (This is only for Fast PWM)
	TCCR2 |= (0 << CS22) | (0 << CS21) | (1 << CS20); // Clock Source Select; no pre-scaling
	*/
	/*
	TCCR2 |= (1<<WGM20)|(1<<WGM21);                   //select Fast PWM mode
	TCCR2 |=(1<<COM21)|(1<<CS20)|(0<<CS21)|(0<<CS22); //clear OC2 on compare match
	*/
	/*
	//Configure TIMER1
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

	ICR1=4999;  //fPWM=50Hz (Period = 20ms Standard).
	*/
	
	TCCR1A |= (1 << COM1A1);
	TCCR1A |= (1 << COM1B1);
	// set non-inverting mode
	TCCR1A |= (1 << WGM11) | (0 << WGM10);
	// set 10bit phase corrected PWM Mode
	TCCR1B |= (1 << CS11);
	// set prescaler to 8 and starts PWM
	
	TCCR2 |= (1 << COM21);
	// set non-inverting mode
	TCCR2 |= (1 << WGM21) | (0 << WGM20);
	// set fast PWM Mode
	TCCR2 |= (1 << CS21) | (1 << CS20);
	// set prescaler to 8 and starts PWM
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
int PWM_write_reg(void *regi, int level) {
	volatile uint8_t *_regi = regi;
	*_regi = level;
	return 0;
}
