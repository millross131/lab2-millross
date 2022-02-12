/*
 * 
 *
 * Created: 1/29/2022 11:07:43 AM
 * Author : Ross Miller
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int i = 0;
void Initialize(){
	cli();
	DDRB &= ~(1<<DDB0);
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);
	DDRB |= (1<<DDB3);
	DDRB |= (1<<DDB4);
	

	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	TCCR1B |= (1<<ICES1);
	
	TIFR1 |= (1<<ICF1);
	
	TIMSK1 |= (1<<ICIE1);
	sei();
}

ISR(TIMER1_CAPT_vect){
	PORTB ^= (1<<PORTB1);
	TCCR1B ^= (1<<ICES1);
}

int main(void)
{
	Initialize();
	/* Replace with your application code */
	while (1)
	{
	}
}

