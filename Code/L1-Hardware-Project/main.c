/*
 * L1-Hardware-Project.c
 *
 * Created: 10/19/2021 10:07:30 AM
 * Author : Hansa Jayathilaka
 */ 

// #ifdef F_CPU
#define F_CPU 16000000L
// #endif

#include <avr/io.h>
#include <util/delay.h>
#include "defines.h"

int main(void)
{
	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(C1, INPUT);
	
	digitalWrite(A2, HIGH);
	while(1) {
		if (digitalRead(C1) == 0) {
		//if ((PINC & (1 << 1)) == 0) {
			digitalWrite(A1, HIGH);
		} else {
			digitalWrite(A1, LOW);
		}
	}
	return 0;
}
