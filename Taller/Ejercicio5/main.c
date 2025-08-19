#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// Macros para leer botones (activos en bajo: 0 = presionado)
#define BTN_HORARIO()     (((PINC & (1<<PC0)) == 0))
#define BTN_ANTIHORARIO() (((PINC & (1<<PC1)) == 0))
#define BTN_FRENO()       (((PINC & (1<<PC2)) == 0))

// Máscara de los 4 pins de control (IN1..IN4 usamos 2 solo en ejemplo)
#define MOTOR_MASK 0x0F   // PB0..PB3

void motor_parar(void) {
	PORTB &= ~MOTOR_MASK; // todas salidas motor = 0
}

void motor_horario(void) {
	// Ejemplo: IN1=1, IN2=0 -> PB0=1, PB1=0
	PORTB = (PORTB & ~MOTOR_MASK) | (1<<PB0);
}

void motor_antihorario(void) {
	// Ejemplo: IN1=0, IN2=1 -> PB0=0, PB1=1
	PORTB = (PORTB & ~MOTOR_MASK) | (1<<PB1);
}

void motor_freno(void) {
	// Ambos en 1 (dependiendo del driver, esto suele ser brake)
	PORTB = (PORTB & ~MOTOR_MASK) | (1<<PB0) | (1<<PB1);
}

void fallo_on(void) {
	PORTB |= (1<<PB4);   // LED fallo
}

void fallo_off(void) {
	PORTB &= ~(1<<PB4);
}

int main(void) {
	// Configuración pines
	DDRB = 0xFF;    // PB0..PB3 salidas motor, PB4 LED fallo
	DDRC = 0x00;    // PC0..PC2 entradas botones
	PORTC = 0xFF;   // Pull-ups internos activados

	motor_parar();
	fallo_off();

	// Estado actual: 0 = parado, 1 = horario, 2 = antihorario
	int estado = 0;

	while (1) {
		// Leer botones (sin bloqueos)
		int h = BTN_HORARIO();
		int a = BTN_ANTIHORARIO();
		int f = BTN_FRENO();

		// Detectar combinaciones inválidas: por ejemplo H y A juntos -> fallo
		if ((h && a) || (h && a && f)) {
			// si presionan HORARIO y ANTI al mismo tiempo -> fallo
			motor_parar();
			fallo_on();
			estado = 0;
			_delay_ms(50); // antirrebote visual
			continue;
		}

		// Prioridad: FRENO
		if (f) {
			fallo_off();
			motor_freno();
			estado = 0;
			_delay_ms(50);
			continue;
		}

		// Si piden HORARIO
		if (h) {
			fallo_off();
			if (estado == 2) {
				// estaba en sentido contrario -> frenar antes
				motor_freno();
				_delay_ms(200);
			}
			motor_horario();
			estado = 1;
			_delay_ms(120); // antirrebote
			continue;
		}

		// Si piden ANTIHORARIO
		if (a) {
			fallo_off();
			if (estado == 1) {
				motor_freno();
				_delay_ms(200);
			}
			motor_antihorario();
			estado = 2;
			_delay_ms(120); // antirrebote
			continue;
		}

		// Si no hay botones -> parar (o mantener último estado, según diseño)
		// Aquí elegimos PARAR y apagar fallo
		motor_parar();
		fallo_off();
		estado = 0;
		_delay_ms(50);
	}
}

