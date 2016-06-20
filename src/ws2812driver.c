
/**
* \file ws2812driver.c
* \brief Plik c - Plik zawiera funkcje do sterowania diodami WS2812
* \author Michal Kruk
* \date 13-06-2016
*/
 
#include "ws2812driver.h"

volatile 	uint8_t buf_tasma[255][240];
volatile  uint8_t buf_short[8];
//======================================================================================
void dioda(uint8_t R, uint8_t G, uint8_t B, uint8_t buf[]){
	
	uint8_t z,y,i;
	uint32_t RGB;
	uint8_t b[3];
	i = 23;
	RGB = (G << 16 )|(R << 8) | B;
	
	for(z=0 ; z<8 ; z++){
		for(y=0 ; y < 3 ;y++){
			b[y] = 0;
			if(RGB & (1<<i)) b[y] = 1;
			
			i--;
		}
		buf[z] =	(b[0] << 6)|(0 << 5)|(1 << 4)|(b[1] << 3)|(0 << 2)|(1 << 1)| b[2];

	}
}

void tablica(void){

	uint8_t i,k,z,r1 = 0;
	
			for(r1 = 0 ; r1 < 255 ; r1++){

			for(i=0 ; i<30 ; i++){
			dioda(0,0,r1,(uint8_t*) buf_short);
				for(k=0 ; k<8 ; k++){
					buf_tasma[r1][z+k] = buf_short[k];
				}
			z+=8;
			}
		}	
}