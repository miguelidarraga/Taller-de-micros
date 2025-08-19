#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

// Secuencia 1 - Barrido simple
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

// Secuencia 2 - Extremos al centro
void secuencia2(void) {
	PORTB = 0x81; _delay_ms(200);
	PORTB = 0x42; _delay_ms(200);
	PORTB = 0x24; _delay_ms(200);
	PORTB = 0x18; _delay_ms(200);
}

// Secuencia 3 - Alterno pares/impares
void secuencia3(void) {
	PORTB = 0xAA; _delay_ms(300); // 10101010
	PORTB = 0x55; _delay_ms(300); // 01010101
}

// Secuencia 4 - Barrido ida y vuelta
void secuencia4(void) {
	for(uint8_t i = 0; i < 8; i++) {
		PORTB = (1 << i);
		_delay_ms(150);
	}
	for(int8_t i = 6; i >= 0; i--) {
		PORTB = (1 << i);
		_delay_ms(150);
	}
}

int main(void) {
	DDRB = 0xFF;    // Puerto B como salida (LEDs)
	DDRD &= 0xF0;   // PD0–PD3 como entrada
	PORTB = 0x00;   // LEDs apagados

	while (1) {
		uint8_t valor = PIND & 0x0F; // Lee nibble bajo (PD0–PD3)

		if (valor == 0x01) {        // PD0 activo
			secuencia1();
		}
		else if (valor == 0x02) {   // PD1 activo
			secuencia2();
		}
		else if (valor == 0x04) {   // PD2 activo
			secuencia3();
		}
		else if (valor == 0x08) {   // PD3 activo
			secuencia4();
		}
		else {
			PORTB = 0x00; // Ninguna entrada ? LEDs apagados
		}
	}
}
