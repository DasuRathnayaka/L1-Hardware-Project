/*
 * pins.h
 *
 * Created: 10/19/2021 2:04:21 PM
 *  Author: Hansa Jayathilaka
 */ 


#define INPUT 0
#define OUTPUT 1

#define HIGH 1
#define LOW 0

char A0[] = "A0";
char A1[] = "A1";
char A2[] = "A2";
char A3[] = "A3";
char A4[] = "A4";
char A5[] = "A5";
char A6[] = "A6";
char A7[] = "A7";

char B0[] = "B0";
char B1[] = "B1";
char B2[] = "B2";
char B3[] = "B3";
char B4[] = "B4";
char B5[] = "B5";
char B6[] = "B6";
char B7[] = "B7";

char C0[] = "C0";
char C1[] = "C1";
char C2[] = "C2";
char C3[] = "C3";
char C4[] = "C4";
char C5[] = "C5";
char C6[] = "C6";
char C7[] = "C7";

char D0[] = "D0";
char D1[] = "D1";
char D2[] = "D2";
char D3[] = "D3";
char D4[] = "D4";
char D5[] = "D5";
char D6[] = "D6";
char D7[] = "D7";

int pinMode(char* pin, int mode);
int digitalWrite(char* pin, int level);
int digitalRead(char* pin);
void ADC_int(void);
int analogRead(char* pin);

void LCD_Command(unsigned char cmnd);
void LCD_Char(unsigned char data);
void LCD_Init(void);
void LCD_String(char *str);
void LCD_String_xy (char row, char col, char *str);
void LCD_Clear();
void LCD_Int(int val);
