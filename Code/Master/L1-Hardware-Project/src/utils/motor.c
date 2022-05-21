/*
 * motor.c
 *
 * Created: 11/30/2021 4:54:44 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "../defines.h"

#define PWM0A   D4    // Left Forward
#define PWM0B   D5   // Right Forward
#define DIRA    D6    // Left Backward
#define DIRB    B2   // Right Backward

void motor_init() {
	pin_mode(PWM0A, OUTPUT);
	pin_mode(PWM0B, OUTPUT);
	pin_mode(DIRA, OUTPUT);
	pin_mode(DIRB, OUTPUT);
}

void setM2Speed(int speed) {
	unsigned char reverse = 0;

	if (speed < 0) {
		speed = -speed; // make speed a positive quantity
		reverse = 1;    // preserve the direction
	}

	if (speed > 0xFF)
	speed = 0xFF;

	if (reverse) {
		digital_write(DIRB, HIGH);
		PWM_write(PWM0B, 0xFF - speed);
	}
	else { // forward
		digital_write(DIRB, LOW);
		PWM_write(PWM0B, speed);
	}
}

void setM1Speed(int speed) {
	unsigned char reverse = 0;

	if (speed < 0) {
		speed = -speed; // make speed a positive quantity
		reverse = 1;    // preserve the direction
	}

	if (speed > 0xFF)
	speed = 0xFF;

	if (reverse) {
		digital_write(DIRA, HIGH);
		PWM_write(PWM0A, 0xFF - speed);
	}
	else { // forward
		digital_write(DIRA, LOW);
		PWM_write(PWM0A, speed);
	}
}

void drive(int m1Speed, int m2Speed) {
	setM1Speed(m1Speed);
	setM2Speed(m2Speed);
}
