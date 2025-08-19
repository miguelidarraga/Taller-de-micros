#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>


#define BTN_MODE PD0

uint8_t seg7_table[16] = {
	0b00111111, 
	0b00000110, 
	0b01011011, 
	0b01001111, 
	0b01100110, 
	0b01101101, 
	0b01111101, 
	0b00000111, 
	0b01111111, 
	0b01101111,
	0b01110111, 
	0b01111100, 
	0b00111001, 
	0b01011110, 
	0b01111001, 
	0b01110001  
};


int main(void) {

	DDRC = 0x00;    
	DDRD &= ~(1 << BTN_MODE); 
	PORTD |= (1 << BTN_MODE); 

	
	DDRA = 0xFF; 
	DDRB = 0xFF;  

	int modo_hex = 1;
	int last_btn = 1;

	while (1) {
		
		int btn = (PIND & (1 << BTN_MODE)) ? 1 : 0;
		if (last_btn == 1 && btn == 0) {
			modo_hex = !modo_hex;
			_delay_ms(200); 
		}
		last_btn = btn;

		
		int valor = PINC;
		int dig1, dig0;

		if (modo_hex) {
			dig1 = (valor >> 4) & 0x0F;
			dig0 = valor & 0x0F;
			} else {
			
			if (valor > 99) valor = 99;
			dig1 = valor / 10;
			dig0 = valor % 10;
		}

		
		PORTA = seg7_table[dig1]; 
		PORTB = seg7_table[dig0]; 
	}
}
