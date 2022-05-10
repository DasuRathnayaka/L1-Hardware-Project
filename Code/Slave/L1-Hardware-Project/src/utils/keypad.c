/*
 * keypad.c
 *
 * Created: 12/4/2021 3:50:40 PM
 *  Author: Hansa Jayathilaka
 */

#include "../defines.h"

// Set PORT C for keypad.
#define KEY_PRT PORTC
#define KEY_DDR DDRC
#define KEY_PIN PINC

unsigned char keypad[4][4] = {
	{'7', '8', '9', '/'},
	{'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {' ', '0', '=', '+'},
};

unsigned char col, row;

char key_char() {
    while (1) {
        KEY_DDR = 0xF0; // Set Data Direction (Input / Output)
        KEY_PRT = 0xFF; // First 4 output hight. Second 4 input pull-up

        do {
            KEY_PRT &= 0x0F; // Mask PORT for column read only
            asm("NOP");
            col = (KEY_PIN & 0x0F); // Read status of column
        } while (col != 0x0F);

        do {
            do {
                _delay_ms(20); // 20ms key debounce time
                col = (KEY_PIN & 0x0F); // Read status of column
            } while (col == 0x0F); // Check for any key press

            _delay_ms(40); // 20 ms key debounce time
            col = (KEY_PIN & 0x0F);
        } while (col == 0x0F);

        // Now check for rows
        KEY_PRT = 0xEF; // Check for pressed key in 1st row
        asm("NOP");
        col = (KEY_PIN & 0x0F);
        if (col != 0x0F) {
            row = 0;
            break;
        }

        KEY_PRT = 0xDF; // Check for pressed key in 2nd row
        asm("NOP");
        col = (KEY_PIN & 0x0F);
        if (col != 0x0F) {
            row = 1;
            break;
        }

        KEY_PRT = 0xBF; // Check for pressed key in 3rd row
        asm("NOP");
        col = (KEY_PIN & 0x0F);
        if (col != 0x0F) {
            row = 2;
            break;
        }

        KEY_PRT = 0x7F; // Check for pressed key in 4th row
        asm("NOP");
        col = (KEY_PIN & 0x0F);
        if (col != 0x0F) {
            row = 3;
            break;
        }
    }

    if (col == 0x0E)
        return (keypad[row][0]);
    else if (col == 0x0D)
        return (keypad[row][1]);
    else if (col == 0x0B)
        return (keypad[row][2]);
    else
        return (keypad[row][3]);
}


void key_string(char buffer[], int buff) {
	for(int i = 0; i < buff; i++) {
		char temp = key_char();
		if (temp == '=') {
			buffer[i] == '\0';
			break;
		}
	}
}
