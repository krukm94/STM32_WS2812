/* second project 
	Michal K
*/


/*=============includes============== */
#include "init.h"


/*=============variables==============*/
extern UART_HandleTypeDef USART6_handle;
extern DMA_HandleTypeDef 	DMA_handle;
/*=============macros=================*/

/*=============functions==============*/

/*===============main=================*/

int main(void) {
	int i,k,z=0;
	uint8_t buf_tasma[240];
	uint8_t buf_short[8];
	
	//Initialization periphals
	init();
	
	//Wypelnianie tablicy
		for(i=0;i<30;i++){
			dioda(0,255,0,buf_short);
			for(k=0 ; k<8 ; k++){
				buf_tasma[z+k] = buf_short[k];
			}
			z+=8;
		}
	
		while( HAL_OK != HAL_UART_Transmit_DMA(&USART6_handle,(uint8_t*) buf_tasma, sizeof(buf_tasma)) ){
		usart1_WriteS(USART1, "\n\r DMA TRANSMIT \n\r");
		}
	while(1) {
		

		
	} //while(1)
		
} // int main(void)


