#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	// Configuración de puertos
	DDRD = 0x00;    // PD0..PD3 como entradas (niveles)
	DDRC &= ~(1<<PC0); // PC0 como entrada (manual)
	DDRA = 0xFF;    // PA0..PA2 salidas (bomba y alarmas)
	DDRB = 0xFF;    // Barra de LEDs como salida
	
	while(1) {
		int niveles = PIND & 0x0F;   // Leer PD0..PD3
		int modo_manual = (PINC & (1<<PC0));
		
		// Mostrar niveles en LEDs
		PORTB = niveles;
		
		// Alarmas
		if(niveles == 0x00) {
			PORTA |= (1<<PA1); // Alarma bajo
			} else {
			PORTA &= ~(1<<PA1);
		}
		
		if(niveles == 0x08) { // PD3=1 ? 100%
			PORTA |= (1<<PA2); // Alarma alto
			} else {
			PORTA &= ~(1<<PA2);
		}
		
		// Control de bomba
		if(modo_manual) {
			PORTA |= (1<<PA0); // Bomba encendida manual
			} else {
			if(niveles < 0x02) {   // Nivel < 2 (0000 o 0001)
				PORTA |= (1<<PA0);
				} else {
				PORTA &= ~(1<<PA0);
			}
		}
	}
}

