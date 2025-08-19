#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

void secuencia1(void) {
	PORTB = 0x01; _delay_ms(200);
	PORTB = 0x02; _delay_ms(200);
	PORTB = 0x04; _delay_ms(200);
	PORTB = 0x08; _delay_ms(200);
	PORTB = 0x10; _delay_ms(200);
	PORTB = 0x20; _delay_ms(200);
	PORTB = 0x40; _delay_ms(200);
	PORTB = 0x80; _delay_ms(200);
}

void secuencia2(void) {
	PORTB = 0x81; _delay_ms(200);
	PORTB = 0x42; _delay_ms(200);
	PORTB = 0x24; _delay_ms(200);
	PORTB = 0x18; _delay_ms(200);
}

void secuencia3(void) {
	PORTB = 0xAA; _delay_ms(300); 
	PORTB = 0x55; _delay_ms(300);
}

void secuencia4(void) {
	for(int i = 0; i < 8; i++) {
		PORTB = (1 << i);
		_delay_ms(150);
	}
	for(int i = 6; i >= 0; i--) {
		PORTB = (1 << i);
		_delay_ms(150);
	}
}

int main(void) {
	DDRB = 0xFF;    
	DDRD &= 0xF0;  
	PORTB = 0x00;   

	while (1) {
		int valor = PIND & 0x0F; 
		if (valor == 0x01) {        
			secuencia1();
		}
		else if (valor == 0x02) {  
			secuencia2();
		}
		else if (valor == 0x04) { 
			secuencia3();
		}
		else if (valor == 0x08) {  
			secuencia4();
		}
		else {
			PORTB = 0x00; 
	}
}
