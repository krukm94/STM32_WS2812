/* ==================================================================================================================================

																						WS2812 DIODE DRIVER SOURCE FILE
																						Author: MK
																						Data: 22.03.2016
									
 ====================================================================================================================================
 */
 
#include "ws2812driver.h"

/* ---------------------> VARIABLES */

volatile 	uint8_t buf_tasma[255][240];
volatile  uint8_t buf_short[8];

/* ==================================================================================================================================

																						Funkcja zapalania jednej doidy
																						Jezeli sterujemy wiecej niz jedna to tyle ile diód
																						tyle razy wywolujemy ta funkcjie
																						AUTOR: MK
 ====================================================================================================================================
 */

uint8_t dioda(uint8_t R, uint8_t G, uint8_t B, uint8_t buf[]){
	
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
/* ==================================================================================================================================
																					
																						Wypelnianie tablicy
	
 ====================================================================================================================================
 */
	
void tablica(void){
		//static variables
		uint8_t r1,i,k,z = 0;
	
		for(r1 = 0 ; r1 < 255 ; r1++){

			for(i=0 ; i<30 ; i++){
			dioda(r1,0,0,(uint8_t*) buf_short);
				for(k=0 ; k<8 ; k++){
					buf_tasma[r1][z+k] = buf_short[k];
				}
			z+=8;
			}
		}	

}

/* ==================================================================================================================================
																						Funkcja zapalania jednej doidy
																						Jezeli sterujemy wiecej niz jedna to tyle ile diód
																						tyle razy wywolujemy ta funkcjie
																						AUTOR: AB
 ====================================================================================================================================
 */
void WS2812B_transcodeGRB(uint8_t green, uint8_t red, uint8_t blue)   //Przekonwertuj podany kolor w formacie RGB na ciag 8 bajtów dla USART  
{  
    uint8_t frame1 = 0x12;
    uint8_t frame2 = 0x12;
    uint8_t frame3 = 0x12;
    uint8_t frame4 = 0x12;
    uint8_t frame5 = 0x12;
    uint8_t frame6 = 0x12;
    uint8_t frame7 = 0x12;
    uint8_t frame8 = 0x12;


    if( green & ( 1 << 7 ) ) frame1 |= (1 << 6);
    if( green & ( 1 << 6 ) ) frame1 |= (1 << 3);
    if( green & ( 1 << 5 ) ) frame1 |= (1 << 0);
    if( green & ( 1 << 4 ) ) frame2 |= (1 << 6);
    if( green & ( 1 << 3 ) ) frame2 |= (1 << 3);
    if( green & ( 1 << 2 ) ) frame2 |= (1 << 0);
    if( green & ( 1 << 1 ) ) frame3 |= (1 << 6);
    if( green & ( 1 << 0 ) ) frame3 |= (1 << 3);

    if( red & ( 1 << 7 ) ) frame3 |= (1 << 0);
    if( red & ( 1 << 6 ) ) frame4 |= (1 << 6);
    if( red & ( 1 << 5 ) ) frame4 |= (1 << 3);
    if( red & ( 1 << 4 ) ) frame4 |= (1 << 0);
    if( red & ( 1 << 3 ) ) frame5 |= (1 << 6);
    if( red & ( 1 << 2 ) ) frame5 |= (1 << 3);
    if( red & ( 1 << 1 ) ) frame5 |= (1 << 0);
    if( red & ( 1 << 0 ) ) frame6 |= (1 << 6);

    if( blue & ( 1 << 7 ) ) frame6 |= (1 << 3);
    if( blue & ( 1 << 6 ) ) frame6 |= (1 << 0);
    if( blue & ( 1 << 5 ) ) frame7 |= (1 << 6);
    if( blue & ( 1 << 4 ) ) frame7 |= (1 << 3);
    if( blue & ( 1 << 3 ) ) frame7 |= (1 << 0);
    if( blue & ( 1 << 2 ) ) frame8 |= (1 << 6);
    if( blue & ( 1 << 1 ) ) frame8 |= (1 << 3);
    if( blue & ( 1 << 0 ) ) frame8 |= (1 << 0);

    USART6 ->TDR = frame1;
    while(!(USART6-> ISR & USART_ISR_TXE));
    USART6 ->TDR = frame2;
    while(!(USART6-> ISR & USART_ISR_TXE));
    USART6 ->TDR = frame3;
    while(!(USART6-> ISR & USART_ISR_TXE));
    USART6 ->TDR = frame4;
    while(!(USART6-> ISR & USART_ISR_TXE));
    USART6 ->TDR = frame5;
    while(!(USART6-> ISR & USART_ISR_TXE));
    USART6 ->TDR = frame6;
    while(!(USART6-> ISR & USART_ISR_TXE));
    USART6 ->TDR = frame7;
    while(!(USART6-> ISR & USART_ISR_TXE));
    USART6 ->TDR = frame8;
    while(!(USART6-> ISR & USART_ISR_TXE));

} 

/* ==================================================================================================================================
																						POLICE EFFECT
 ====================================================================================================================================
 */
void police_effect(void){
	
//				dioda(0,0,250);
//				dioda(0,0,0);
//				
//				HAL_Delay(50);
//				
//				dioda(0,0,0);
//				dioda(0,0,0);
//				
//				HAL_Delay(50);

//				dioda(0,0,250);
//				dioda(0,0,0);
//				
//				HAL_Delay(50);
//				
//				dioda(0,0,0);
//				dioda(0,0,0);
//				
//				HAL_Delay(50);				
//				
//				dioda(0,0,250);
//				dioda(0,0,0);
//				
//				HAL_Delay(50);
//				
//				dioda(0,0,0);
//				dioda(0,0,250);	
//				
//				HAL_Delay(150);
}
/* ==================================================================================================================================
																					END OF FILE
 ====================================================================================================================================
 */

