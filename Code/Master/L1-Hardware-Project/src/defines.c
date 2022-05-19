/*
 * defines.c
 *
 * Created: 11/1/2021 11:46:25 PM
 *  Author: Hansa Jayathilaka
 */ 

#include "defines.h"

int timer0_overflow = 0;

//GPS related


const Pin A0 = {.port = 'A', .pin = 0};
const Pin A1 = {.port = 'A', .pin = 1};
const Pin A2 = {.port = 'A', .pin = 2};
const Pin A3 = {.port = 'A', .pin = 3};
const Pin A4 = {.port = 'A', .pin = 4};
const Pin A5 = {.port = 'A', .pin = 5};
const Pin A6 = {.port = 'A', .pin = 6};
const Pin A7 = {.port = 'A', .pin = 7};

const Pin B0 = {.port = 'B', .pin = 0};
const Pin B1 = {.port = 'B', .pin = 1};
const Pin B2 = {.port = 'B', .pin = 2};
const Pin B3 = {.port = 'B', .pin = 3};
const Pin B4 = {.port = 'B', .pin = 4};
const Pin B5 = {.port = 'B', .pin = 5};
const Pin B6 = {.port = 'B', .pin = 6};
const Pin B7 = {.port = 'B', .pin = 7};

const Pin C0 = {.port = 'C', .pin = 0};
const Pin C1 = {.port = 'C', .pin = 1};
const Pin C2 = {.port = 'C', .pin = 2};
const Pin C3 = {.port = 'C', .pin = 3};
const Pin C4 = {.port = 'C', .pin = 4};
const Pin C5 = {.port = 'C', .pin = 5};
const Pin C6 = {.port = 'C', .pin = 6};
const Pin C7 = {.port = 'C', .pin = 7};

const Pin D0 = {.port = 'D', .pin = 0};
const Pin D1 = {.port = 'D', .pin = 1};
const Pin D2 = {.port = 'D', .pin = 2};
const Pin D3 = {.port = 'D', .pin = 3};
const Pin D4 = {.port = 'D', .pin = 4};
const Pin D5 = {.port = 'D', .pin = 5};
const Pin D6 = {.port = 'D', .pin = 6};
const Pin D7 = {.port = 'D', .pin = 7};


const Pin SLAVE_SS_0 = {.port = 'B', .pin = 4};
const Pin MOSI = {.port = 'B', .pin = 5};
const Pin MISO = {.port = 'B', .pin = 6};
const Pin SCK = {.port = 'B', .pin = 7};
