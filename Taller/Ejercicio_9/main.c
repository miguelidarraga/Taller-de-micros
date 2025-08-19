#define F_CPU 20000000UL
#include <avr/io.h>

#define PATRON 0b1010   // Patrón fijo de validación

int main(void) {
	// -------------------------------
	// CONFIGURACIÓN DE PUERTOS
	// -------------------------------
	DDRD &= ~(0x3F);    // PD0..PD5 como entradas
	PORTD |= 0x3F;      // Pull-ups internos (botones activos en bajo)

	DDRA |= 0x0F;       // PA0..PA3 como salidas (eco)
	DDRB |= (1<<PB0) | (1<<PB1);   // PB0=OK (verde), PB1=FAIL (rojo)

	// Inicializar salidas
	PORTA &= ~(0x0F);
	PORTB &= ~((1<<PB0) | (1<<PB1));

	// Variables para detectar flanco
	int prevEnter = 1;   // estado previo de ENTER (reposo=1 por pull-up)

	while (1) {
		// -------------------------------
		// ECO en PA0..PA3
		// -------------------------------
		int nibble = PIND & 0x0F;
		PORTA = (PORTA & 0xF0) | nibble;

		// -------------------------------
		// CLR (PD5 activo en bajo)
		// -------------------------------
		if (!(PIND & (1<<PD5))) {
			PORTA &= ~(0x0F);
			PORTB &= ~((1<<PB0) | (1<<PB1));
		}

		// -------------------------------
		// ENTER (PD4 activo en bajo, flanco de bajada)
		// -------------------------------
		int enter = (PIND & (1<<PD4)) ? 1 : 0;  // leer PD4
		if (prevEnter == 1 && enter == 0) {         // flanco 1→0
			if (nibble == PATRON) {
				PORTB |=  (1<<PB0);  // encender OK (verde)
				PORTB &= ~(1<<PB1);  // apagar FAIL
				} else {
				PORTB |=  (1<<PB1);  // encender FAIL (rojo)
				PORTB &= ~(1<<PB0);  // apagar OK
			}
		}
		prevEnter = enter;   // actualizar estado previo
	}
}

