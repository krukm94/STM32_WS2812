/* second project 
	Michal K
*/


/*=============includes============== */
#include "init.h"


/*=============variables==============*/
extern UART_HandleTypeDef USART6_handle;
extern DMA_HandleTypeDef 	DMA_handle;
extern TIM_HandleTypeDef			TIM2_HandleStruct;

volatile 	uint8_t buf_tasma[255][240];
volatile  uint8_t buf_tasma2[240];
volatile  uint8_t buf_short[8];

volatile uint8_t flag_usart_tc;
/*=============macros=================*/
#define ILOSC_DIOD				30
/*=============functions==============*/

/*===============main=================*/

int main(void) {
	//static variables
	int i,k,z = 0,x,r1 =0;
	
	//Initialization periphals
	init();
	
	//Wypelnianie tablicy
	for(r1 = 0 ; r1 < 255 ; r1++){
		
		for(i=0 ; i<ILOSC_DIOD ; i++){
			dioda(r1,0,10,(uint8_t*) buf_short);
			for(k=0 ; k<8 ; k++){
				buf_tasma[r1][z+k] = buf_short[k];
			}
			z+=8;
		}
}
	
	//TIMER INIT
	tim2_init();
	
	while(1) {
		

	} //while(1)
		
} // int main(void)


