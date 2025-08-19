#include "SEVENSEG_LIB.h"

char decoCC[10]={191, 134, 219, 207, 230, 237, 253, 135, 255, 231};
char decoAC[10]={64, 121, 36, 48, 25, 18, 2, 120, 0, 24};


void diplayInit(){
	DDR_DISPLAY = 0xFF;
}
void displayDecoCC( unsigned char digito ){
	if(digito>9) return;
	PORT_DISPLAY = decoCC[digito];
}
void displayDecoAC(unsigned char digito ){
	if(digito>9) return;
	PORT_DISPLAY = decoAC[digito];
}
