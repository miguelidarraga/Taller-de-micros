
#ifndef SEVENSEG_LIB_H_
#define SEVENSEG_LIB_H_

#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

#define DDR_DISPLAY  DDRD
#define PORT_DISPLAY PORTD

void diplayInit();
void displayDecoCC( unsigned char digito );
void displayDecoAC(unsigned char digito );



#endif /* SEVENSEG_LIB_H_ */