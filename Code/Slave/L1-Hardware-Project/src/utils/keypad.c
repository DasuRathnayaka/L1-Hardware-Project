/*
 * keypad.c
 *
 * Created: 12/4/2021 3:50:40 PM
 *  Author: Dasuni Rathnayaka
 */

#include "../defines.h"

#define KEY_PRT 	PORTA
#define KEY_DDR		DDRA
#define KEY_PIN		PINA

unsigned char keypad[4][4] = {
	{'7','4','1',' '},
	{'8','5','2','0'},
	{'9','6','3','='},
	{'/','*','-','+'},
};

unsigned char colloc, rowloc;


char key_char() {
	while(1) {
		KEY_DDR = 0xF0;           /* set port direction as input-output */
		KEY_PRT = 0xFF;

		do
		{
			KEY_PRT &= 0x0F;      /* mask PORT for column read only */
			asm("NOP");
			colloc = (KEY_PIN & 0x0F); /* read status of column */
		} while(colloc != 0x0F);
		
		do
		{
			do
			{
				_delay_ms(20);             /* 20ms key debounce time */
				colloc = (KEY_PIN & 0x0F); /* read status of column */
			} while(colloc == 0x0F);        /* check for any key press */
			
			_delay_ms (40);	            /* 20 ms key debounce time */
			colloc = (KEY_PIN & 0x0F);
		} while(colloc == 0x0F);

		/* now check for rows */
		KEY_PRT = 0xEF;            /* check for pressed key in 1st row */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F);
		if(colloc != 0x0F)
		{
			rowloc = 0;
			break;
		}

		KEY_PRT = 0xDF;		/* check for pressed key in 2nd row */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F);
		if(colloc != 0x0F)
		{
			rowloc = 1;
			break;
		}
		
		KEY_PRT = 0xBF;		/* check for pressed key in 3rd row */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F);
		if(colloc != 0x0F)
		{
			rowloc = 2;
			break;
		}

		KEY_PRT = 0x7F;		/* check for pressed key in 4th row */
		asm("NOP");
		colloc = (KEY_PIN & 0x0F);
		if(colloc != 0x0F)
		{
			rowloc = 3;
			break;
		}
	}

	if(colloc == 0x0E)
		return(keypad[rowloc][0]);
	else if(colloc == 0x0D)
		return(keypad[rowloc][1]);
	else if(colloc == 0x0B)
		return(keypad[rowloc][2]);
	else
		return(keypad[rowloc][3]);
}


void key_string(char buffer[], int buff) {
	UART_TxChar('\n');
	for(int i = 0; i < buff; i++) {
		char temp = key_char();
		LCD_char(temp);
		UART_TxChar(temp);
		if (temp == '=') {
			buffer[i] = '\0';
			break;
		}
		buffer[i] = temp;
	}
}
