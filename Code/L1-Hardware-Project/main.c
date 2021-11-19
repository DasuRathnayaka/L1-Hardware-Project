/*
 * L1-Hardware-Project.c
 *
 * Created: 10/19/2021 10:07:30 AM
 * Author : Hansa Jayathilaka
 */ 

// #ifdef F_CPU
// #define F_CPU 16000000L
// #endif

#include "src/defines.h"


int main(void) {
	
	sys_init();
	
	while(1) {
		
		sys_loop();
		
	}
	return 0;
}
