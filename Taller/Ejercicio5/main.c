#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


#define BTN_HORARIO()     (((PINC & (1<<PC0)) == 0))
#define BTN_ANTIHORARIO() (((PINC & (1<<PC1)) == 0))
#define BTN_FRENO()       (((PINC & (1<<PC2)) == 0))

#define MOTOR_MASK 0x0F   

void motor_parar(void) {
	PORTB &= ~MOTOR_MASK; 
}

void motor_horario(void) {
	
	PORTB = (PORTB & ~MOTOR_MASK) | (1<<PB0);
}

void motor_antihorario(void) {
	PORTB = (PORTB & ~MOTOR_MASK) | (1<<PB1);
}

void motor_freno(void) {
	PORTB = (PORTB & ~MOTOR_MASK) | (1<<PB0) | (1<<PB1);
}

void fallo_on(void) {
	PORTB |= (1<<PB4);   
}

void fallo_off(void) {
	PORTB &= ~(1<<PB4);
}

int main(void) {
	
	DDRB = 0xFF;    
	DDRC = 0x00;    
	PORTC = 0xFF;   
	
	motor_parar();
	fallo_off();

	int estado = 0;

	while (1) {
		int h = BTN_HORARIO();
		int a = BTN_ANTIHORARIO();
		int f = BTN_FRENO();

		if ((h && a) || (h && a && f)) {
			motor_parar();
			fallo_on();
			estado = 0;
			_delay_ms(50); 
			continue;
		}

		if (f) {
			fallo_off();
			motor_freno();
			estado = 0;
			_delay_ms(50);
			continue;
		}

		if (h) {
			fallo_off();
			if (estado == 2) {
				motor_freno();
				_delay_ms(200);
			}
			motor_horario();
			estado = 1;
			_delay_ms(120);
			continue;
		}

		if (a) {
			fallo_off();
			if (estado == 1) {
				motor_freno();
				_delay_ms(200);
			}
			motor_antihorario();
			estado = 2;
			_delay_ms(120); 
			continue;
		}

	
		motor_parar();
		fallo_off();
		estado = 0;
		_delay_ms(50);
	}
}

