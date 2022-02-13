/*
 * Lab 2 draft 4
 *
 * Created: 1/29/2022 11:07:43 AM
 * Author : Ross Miller
 */ 
#include <util/delay.h>
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>


int i = 0;

void Initialize(){
	cli();
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);
	DDRB |= (1<<DDB3);
	DDRB |= (1<<DDB4);
	DDRD &= ~(1<<DDD7);

	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	TCCR1B |= (1<<ICES1);
	
	TIFR1 |= (1<<ICF1);
	
	TIMSK1 |= (1<<ICIE1);
	sei();
}

ISR(TIMER1_CAPT_vect){
	
	TCCR1B ^= (1<<ICES1);
	PORTB ^= (1<<PORTB1);

}

int main(void)
{
	Initialize();
	while (1)
	{
	}
}

