/* second project 
	Michal K
*/


/*=============includes============== */
#include "init.h"
#include "WS2812.h"

/*=============variables==============*/
extern UART_HandleTypeDef USART6_handle;
extern DMA_HandleTypeDef 	DMA_handle;
extern TIM_HandleTypeDef	TIM2_HandleStruct;


volatile uint8_t buf_tasma_test[240];
volatile  uint8_t buf_short1[8];

/*=============macros=================*/

/*=============functions==============*/

/*===============main=================*/

int main(void) {
	
	uint8_t i,k,z = 0;
	
	//Initialization periphals
	init();
	//wygenerowanie tablicy dla diod WS2812
	tablica();
	

			for(i=0 ; i<30 ; i++){
			dioda(0,0,5,(uint8_t*) buf_short1);
				for(k=0 ; k<8 ; k++){
					buf_tasma_test[z+k] = buf_short1[k];
				}
			z+=8;
			}
			
			//TIM 3 INIT
	tim3_init();
	
	while(1) {
		

	} //while(1)
		
} // int main(void)


