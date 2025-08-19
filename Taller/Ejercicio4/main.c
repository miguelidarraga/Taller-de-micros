#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRA = 0xFF;
	DDRC = 0x00;
	PORTC = 0xFF;

	int patron = 0x00;
	int prevPC3 = 1;

	while (1) {
		int botones = PINC;

		if (!(botones & (1<<PC2))) {
			patron = 0x00;
		}
		else {
			if (!(botones & (1<<PC0))) {
				patron = 0b10101010;
			}
			if (!(botones & (1<<PC1))) {
				patron = 0b01010101;
			}
		}

		int invertPC3 = (botones & (1<<PC3)) ? 1 : 0;
		if (prevPC3 == 1 && invertPC3 == 0) {
			patron = ~patron;
		}
		prevPC3 = invertPC3;

		PORTA = patron;

		_delay_ms(50);
	}
}

