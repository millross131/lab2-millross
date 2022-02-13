/*
 * Lab 2 draft 4
 *
 * Created: 2/11/2022 11:24:27 AM
 * Author : Ross Miller
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "uart.h"
#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)


int rising = 1;
volatile int flagged = 1;
volatile int start = 0;
volatile int ticSize = 0;
int letter = 0;
int size = 0;
volatile int last;
volatile int overflow = 0;
volatile int overflow2 = 0;
int newChar = 1;
char String[25];

void Initialize(){
	cli();
	DDRB &= ~(1<<DDB0);
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);
	DDRB |= (1<<DDB3);
	DDRB |= (1<<DDB4);
	
	TCCR1B |= (1<<CS10);
	TCCR1B &= ~(1<<CS11);
	TCCR1B &= ~(1<<CS12);
	
	TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	TIMSK1 |= (1<<ICIE1);
	TCCR1B &= ~(1<<ICES1);
	TIMSK1 |= (1<<TOIE1);
	sei();
}
int morseToLetter(int letter){
	switch(letter){
		case 12: 
			UART_putstring("A");
			break;
		case 2111:
			UART_putstring("B");
			break;
		case 2121:
			UART_putstring("C");
			break;
		case 211:
			UART_putstring("D");
			break;
		case 1:
			UART_putstring("E");
			break;
		case 1121:
			UART_putstring("F");
			break;
		case 221:
			UART_putstring("G");
			break;
		case 1111:
			UART_putstring("H");
			break;
		case 11:
			UART_putstring("I");
			break;
		case 1222:
			UART_putstring("J");
			break;
		case 212:
			UART_putstring("K");
			break;
		case 1211:
			UART_putstring("L");
			break;
		case 22:
			UART_putstring("M");
			break;
		case 21:
			UART_putstring("N");
			break;
		case 222:
			UART_putstring("O");
			break;
		case 1221:
			UART_putstring("P");
			break;
		case 2212:
			UART_putstring("Q");
			break;
		case 121:
			UART_putstring("R");
			break;
		case 111: 
			UART_putstring("S");
			break;
		case 2:
			UART_putstring("T");
			break;
		case 112:
			UART_putstring("U");
			break;
		case 1112:
			UART_putstring("V");
			break;
		case 122:
			UART_putstring("W");
			break;
		case 2112:
			UART_putstring("X");
			break;
		case 2122:
			UART_putstring("Y");
			break;
		case 2211:
			UART_putstring("Z");
			break;
		default : 
			UART_putstring("");
	}
	return 0;
}
ISR(TIMER1_CAPT_vect){
	//PORTB ^= (1<<PORTB1);
	TCCR1B ^= (1<<ICES1);
	if(flagged) {
		
		
		size = overflow;
		if(size > 7 && size <100){
			sprintf(String,"dot \n");
			UART_putstring(String);
			PORTB |= (1<<PORTB1);
			_delay_ms(50);
			PORTB &=  ~(1<<PORTB1);
			//letter = letter * 10 +1;
			if(newChar){
				letter = 1;
				newChar = 0;
			} else{
				letter = letter * 10 +1;
			}
		}
		else if(size > 100 && size < 300){
			sprintf(String,"dash \n");
			UART_putstring(String);
			PORTB |= (1<<PORTB2);
			_delay_ms(50);
			PORTB &=  ~(1<<PORTB2);
			if(newChar){
				letter = 2;
				newChar = 0;
			} else{
				letter = letter * 10 +2;
			}
		}
		overflow = 0;
		flagged = 0;
	} else {
		flagged = 1;
		sprintf(String, "size %u\n", overflow);
		UART_putstring(String);
		if(overflow >= 400){
			sprintf(String,"dash \n");
			UART_putstring(String);
			PORTB |= (1<<PORTB3);
			_delay_ms(50);
			PORTB &=  ~(1<<PORTB3);
			morseToLetter(letter);
			newChar = 1;
		}
	}
		}
	
ISR(TIMER1_OVF_vect){
	overflow++;
}

int main(void)
{
	Initialize();
	UART_init(BAUD_PRESCALER);
	while (1)
	{
	}
}
		
