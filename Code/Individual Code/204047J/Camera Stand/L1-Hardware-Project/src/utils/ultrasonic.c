/*
 * ultrasonic.c
 *
 * Created: 11/1/2021 10:49:53 PM
 *  Author: Binari Dissanayake
 */ 

#include "../defines.h"

#define trigPin C6
#define echoPin D6

#define mux1 C4
#define mux2 C5

int TimerOverflow = 0;


void ultrazonic_init() {
	pin_mode(trigPin, OUTPUT);
	pin_mode(echoPin, INPUT_PULLUP);
	
	pin_mode(mux1, OUTPUT);
	pin_mode(mux2, OUTPUT);
}


double ultrazonic_distance(void) {
	char string[10];
	long count;
	double distance;
	
	uint8_t _TCCR1B = TCCR1B;
	uint8_t _TCCR1A = TCCR1A;
	uint8_t _TIMSK = TIMSK;
	
	sei();			/* Enable global interrupt */
	TIMSK = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
	TCCR1A = 0;		/* Set all bit to zero Normal operation */

	/* Give 10us trigger pulse on trig. pin to HC-SR04 */
	digital_write(C6, HIGH);
	_delay_us(10);
	digital_write(C6, LOW);
	
	TCNT1 = 0;	/* Clear Timer counter */
	TCCR1B = 0x41;	/* Capture on rising edge, No prescaler*/
	TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */

	/*Calculate width of Echo by Input Capture (ICP) */
		
	while ((TIFR & (1 << ICF1)) == 0);/* Wait for rising edge */
	TCNT1 = 0;	/* Clear Timer counter */
	TCCR1B = 0x01;	/* Capture on falling edge, No prescaler */
	TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
	TimerOverflow = 0;/* Clear Timer overflow count */

	while ((TIFR & (1 << ICF1)) == 0);/* Wait for falling edge */
	count = ICR1 + (65535 * TimerOverflow);	/* Take count */
	/* 8MHz Timer freq, sound speed =343 m/s */
	distance = (double)count / 466.47;

	TCCR1B = _TCCR1B;
	TCCR1A = _TCCR1A;
	TIMSK = _TIMSK;
	// PWM_init();
	return distance;
}


int ultrazonic_error() {
	digital_write(mux1, LOW);
	digital_write(mux2, LOW);
	double left = ultrazonic_distance();
	
	digital_write(mux1, HIGH);
	digital_write(mux2, HIGH);
	double right = ultrazonic_distance();
	// LCD_clear_msg("*");
	_delay_ms(100);
	
	digital_write(mux1, LOW);
	digital_write(mux2, HIGH);
	double front = ultrazonic_distance();
	
	digital_write(mux1, HIGH);
	digital_write(mux2, LOW);
	double back = ultrazonic_distance();
	
	char string[16];
	LCD_clear();
	LCD_line_1();
	
	dtostrf(left, 2, 2, string);/* distance to string */
	strcat(string, " cm   ");	/* Concat unit i.e.cm */
	LCD_msg("1. ");
	LCD_msg(string);
	
	dtostrf(right, 2, 2, string);/* distance to string */
	strcat(string, " cm");	/* Concat unit i.e.cm */
	LCD_line_2();
	LCD_msg("2. ");
	LCD_msg(string);
	_delay_ms(1000);
	
	LCD_clear();
	LCD_line_1();
	
	dtostrf(front, 2, 2, string);/* distance to string */
	strcat(string, " cm   ");	/* Concat unit i.e.cm */
	LCD_msg("3. ");
	LCD_msg(string);
	
	dtostrf(back, 2, 2, string);/* distance to string */
	strcat(string, " cm");	/* Concat unit i.e.cm */
	LCD_line_2();
	LCD_msg("4. ");
	LCD_msg(string);
	_delay_ms(200);
	_delay_ms(1000);
	
	digital_write(mux1, LOW);
	digital_write(mux2, LOW);
	
	int error = right - left;
	
	return error;
}


ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	/* Increment Timer Overflow count */
}
