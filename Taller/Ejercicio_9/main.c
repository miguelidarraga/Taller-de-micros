#define F_CPU 20000000UL
#include <avr/io.h>

#define PATRON 0b1010

int main(void) {
	
	DDRD &= ~(0x3F);
	PORTD |= 0x3F;

	DDRA |= 0x0F;
	DDRB |= (1<<PB0) | (1<<PB1);

	
	PORTA &= ~(0x0F);
	PORTB &= ~((1<<PB0) | (1<<PB1));

	
	int prevEnter = 1;

	while (1) {
		
		int nibble = PIND & 0x0F;
		PORTA = (PORTA & 0xF0) | nibble;
		
		if (!(PIND & (1<<PD5))) {
			PORTA &= ~(0x0F);
			PORTB &= ~((1<<PB0) | (1<<PB1));
		}

		
		int enter = (PIND & (1<<PD4)) ? 1 : 0;
		if (prevEnter == 1 && enter == 0) { 
			if (nibble == PATRON) {
				PORTB |=  (1<<PB0);  
				PORTB &= ~(1<<PB1);  
				} else {
				PORTB |=  (1<<PB1); 
				PORTB &= ~(1<<PB0);  
			}
		}
		prevEnter = enter;   
	}
}

