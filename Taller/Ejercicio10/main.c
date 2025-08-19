#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

// Botón en PD0
#define BTN_MODE PD0

// Tabla de conversión para 7 segmentos (cátodo común)
uint8_t seg7_table[16] = {
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // b
	0b00111001, // C
	0b01011110, // d
	0b01111001, // E
	0b01110001  // F
};


int main(void) {
	// Entradas
	DDRC = 0x00;              // PORTC como entrada (dato)
	DDRD &= ~(1 << BTN_MODE); // PD0 como entrada
	PORTD |= (1 << BTN_MODE); // Pull-up en PD0

	// Salidas
	DDRA = 0xFF;  // Display izquierdo (decenas o nibble alto)
	DDRB = 0xFF;  // Display derecho (unidades o nibble bajo)

	uint8_t modo_hex = 1;
	uint8_t last_btn = 1;

	while (1) {
		// Leer botón (flanco descendente)
		uint8_t btn = (PIND & (1 << BTN_MODE)) ? 1 : 0;
		if (last_btn == 1 && btn == 0) {
			modo_hex = !modo_hex;
			_delay_ms(200); // antirrebote
		}
		last_btn = btn;

		// Leer dato
		uint8_t valor = PINC;

		uint8_t dig1, dig0;

		if (modo_hex) {
			// HEX: nibble alto y bajo
			dig1 = (valor >> 4) & 0x0F;
			dig0 = valor & 0x0F;
			} else {
			// DEC: saturar a 99
			if (valor > 99) valor = 99;
			dig1 = valor / 10;
			dig0 = valor % 10;
		}

		// Mostrar en displays
		PORTA = seg7_table[dig1]; // Decenas o nibble alto
		PORTB = seg7_table[dig0]; // Unidades o nibble bajo
	}
}
