#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

static inline void jtag_off(void){ MCUCR |= (1<<JTD); MCUCR |= (1<<JTD); }

// Tabla 7 segmentos común cátodo
char decoCC[10]={191, 134, 219, 207, 230, 237, 253, 135, 255, 231};

int main(void){
	jtag_off();

	DDRA = 0xFF;    // decenas
	DDRC = 0xFF;    // unidades
	DDRD = 0x00;    // botones
	PORTD = (1<<PD0)|(1<<PD1)|(1<<PD2); // pull-ups internos activados

	int count = 0;

	while(1){
		// Botones activos en bajo
		int up   = !(PIND & (1<<PD0));
		int down = !(PIND & (1<<PD1));
		int clr  = !(PIND & (1<<PD2));

		if (clr){ count = 0; _delay_ms(150); }
		else {
			if (up){ count++; if(count>99) count=0; _delay_ms(150); }
			if (down){ count--; if(count<0) count=99; _delay_ms(150); }
		}

		int dec = count / 10;
		int uni = count % 10;

		PORTA = decoCC[dec];
		PORTC = decoCC[uni];
	}
}
