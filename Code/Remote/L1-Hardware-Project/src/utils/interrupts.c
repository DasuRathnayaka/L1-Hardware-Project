/*
 * interrupts.c
 *
 * Created: 11/28/2021 6:10:38 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "../defines.h"


ISR(TIMER0_OVF_vect)
{
	timer0_overflow++;  // Get overflowing value.
}

