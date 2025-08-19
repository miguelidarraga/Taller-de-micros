#define F_CPU 20000000
#include <avr/io.h>
#include <util/delay.h>

#define BTN_PEATONAL PD0

#define VERDE_VEHICULO (1 << PA0)
#define AMARILLO_VEHICULO (1 << PA1)
#define ROJO_VEHICULO (1 << PA2)
#define VERDE_PEATON (1 << PA3)

int main(void) {
	
	DDRD &= ~(1 << BTN_PEATONAL);
	PORTD |= (1 << BTN_PEATONAL);

	DDRA |= VERDE_VEHICULO | AMARILLO_VEHICULO | ROJO_VEHICULO | VERDE_PEATON;

	uint8_t peatones_piden_cruce = 0;

	while (1) {
		
		if (!(PIND & (1 << BTN_PEATONAL))) {
			peatones_piden_cruce = 1;
		}

		
		PORTA = VERDE_VEHICULO;
		PORTA &= ~VERDE_PEATON;
		_delay_ms(5000);

		
		PORTA = AMARILLO_VEHICULO;
		PORTA &= ~VERDE_PEATON;
		_delay_ms(2000);

		
		PORTA = ROJO_VEHICULO;

		if (peatones_piden_cruce) {
			
			PORTA |= VERDE_PEATON;

			_delay_ms(5000);

			
			PORTA &= ~VERDE_PEATON;

			peatones_piden_cruce = 0;
			} else {
			PORTA &= ~VERDE_PEATON;
			_delay_ms(5000);
		}
	}
}

