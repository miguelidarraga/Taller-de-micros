#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	
	DDRD = 0x00; 
	DDRC &= ~(1<<PC0); 
	DDRA = 0xFF;  
	DDRB = 0xFF; 
	
	while(1) {
		int niveles = PIND & 0x0F;   
		int modo_manual = (PINC & (1<<PC0));
		
		
		PORTB = niveles;
		
		
		if(niveles == 0x00) {
			PORTA |= (1<<PA1); 
			} else {
			PORTA &= ~(1<<PA1);
		}
		
		if(niveles == 0x08) { 
			PORTA |= (1<<PA2); 
			} else {
			PORTA &= ~(1<<PA2);
		}
		
		
		if(modo_manual) {
			PORTA |= (1<<PA0); 
			} else {
			if(niveles < 0x02) {  
				PORTA |= (1<<PA0);
				} else {
				PORTA &= ~(1<<PA0);
			}
		}
	}
}

