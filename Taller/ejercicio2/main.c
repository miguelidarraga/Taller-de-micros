#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "SEVENSEG/SEVENSEG_LIB.h"

#define DP_DECENAS  (1<<PINB1)
#define DP_UNIDADES (1<<PINB0)


int numa, numb, result=0;

int main(void)
{
	diplayInit();
	
	DDRC = 0x00;
	DDRA &= ~( (1<<PINA0)|(1<<PINA1) );
	DDRB |=  ( (1<<PINB0)|(1<<PINB1) );
	
	while (1)
	{
		numa = (PINC & 0x0F)>>0;
		numb = (PINC & 0xF0)>>4;
		
		if( (PINA&(1<<PINA0)) !=0  && (PINA&(1<<PINA1)) == 0 ){
			result = numa + numb;
		}
		if( (PINA&(1<<PINA1)) !=0  && (PINA&(1<<PINA0)) == 0 ){
			result = abs(numa - numb);
		}
		
		PORTB = DP_DECENAS;
		displayDecoCC( result/10 );
		_delay_ms(10);
		
		PORTB = DP_UNIDADES;
		displayDecoCC( result%10 );
		_delay_ms(10);
	}
}


