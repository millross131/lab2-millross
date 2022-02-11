/*
 * Lab 2 draft 4.c
 *
 * Created: 1/28/2022 1:02:01 PM
 * Author : millross
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>


void Initialize()
{
    /* Replace with your application code */
      DDRB |= (1<<DDB1);
      DDRB |= (1<<DDB2);
      DDRB |= (1<<DDB3);
      DDRB |= (1<<DDB4);
	  DDRB &= ~(1<<DDD7);
	  
}

int main(void)
{
	Initialize();
	int i = 0;
	while(1)
	{
		if(i==0 && (PIND & (1<<PIND7))){
			PORTB &= ~(1<<PORTB1);
			PORTB |= (1<<PORTB2);
			i++;
			_delay_ms(300);
		}
		else if(i==1 && (PIND & (1<<PIND7))){
			PORTB &= ~(1<<PORTB2);
			PORTB |= (1<<PORTB3);
			i++;
			_delay_ms(300);
		}
		else if(i==2 && (PIND & (1<<PIND7))){
			PORTB &= ~(1<<PORTB3);
			PORTB |= (1<<PORTB4);
			i++;
			_delay_ms(300);
		}
		else if(i==3 && (PIND & (1<<PIND7))){
			PORTB &= ~(1<<PORTB4);
			PORTB |= (1<<PORTB1);
			i=0;
			_delay_ms(300);
		}
		
	}
}

