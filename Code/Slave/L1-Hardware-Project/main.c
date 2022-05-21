/*
 * L1-Hardware-Project.c
 *
 * Created: 10/19/2021 10:07:30 AM
 * Author : Hansa Jayathilaka
 */ 

#include "src/defines.h"

int main(void) {
	
	sys_init();
	
	while(1) {
		
		sys_loop();
		
	}
	
	return 0;
}


// /*
// 
// C Program for Distance Measurement using Ultrasonic Sensor and AVR Microocntroller
// 
//  */ 
// 
// 
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #define F_CPU 8000000
// #include <util/delay.h>
// #include <stdlib.h>
// 
// #define enable            5
// #define registerselection 6
// 
// static volatile int pulse = 0;
// static volatile int i = 0;
// 
// int main(void)
// {
//     DDRA = 0xFF;
//     DDRB = 0xFF;
//     DDRD = 0b11111011;
//     _delay_ms(50);
//     
// 
//     GICR|=(1<<INT0);
//     MCUCR|=(1<<ISC00);
//     
//     TCCR1A = 0;
//     
//     int16_t COUNTA = 0;
//     char SHOWA [16];
// 
//     sei();
// 
//     while(1)
//     {
//         PORTD|=(1<<PIND0);
//         _delay_us(15);
//         PORTD &=~(1<<PIND0);
// 
//         
//         COUNTA = pulse/58;
//         send_a_string ("CIRCUIT DIGEST");
//         send_a_string ("DISTANCE=");
//         itoa(COUNTA,SHOWA,10);
//         send_a_string(SHOWA);
//         send_a_string ("cm    ");
// 
//     }
// }
// 
// 
// ISR(INT0_vect)
// {
//     if (i==1)
//     {
//         TCCR1B=0;
//         pulse=TCNT1;
//         TCNT1=0;
//         i=0;
//     }
//     if (i==0)
//     {
//         TCCR1B|=(1<<CS10);
//         i=1;
//     }
// }
// 
// void send_a_string(char *string_of_characters)
// {
// 	
// }
