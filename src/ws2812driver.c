
/**
* \file ws2812driver.c
* \brief Plik c - Plik zawiera funkcje do sterowania diodami WS2812
* \author Michal Kruk
* \date 13-06-2016
*/
 
#include "ws2812driver.h"

extern volatile 	uint8_t buf_tasma[255][240];
volatile  uint8_t buf_short[8];

extern volatile uint8_t flag_usart_tc; 

UART_HandleTypeDef USART6_handle;
DMA_HandleTypeDef	 DMA_handle;

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

//======================================================================================
void tablica(void){

	uint8_t i,k,z,r1 = 0;
	
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

//======================================================================================
uint8_t usart6_init(uint32_t	BAUDRATE){

	uint8_t usart_status;
											
	GPIO_InitTypeDef     GPIO_InitStruct;
	
	usart_status = 0x01;
 
	USART6_GPIO_CLK_ENABLE();

	USART6_CLK_ENABLE();
	
	GPIO_InitStruct.Pin				= GPIO_PIN_6;
	GPIO_InitStruct.Mode	  	= GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull 			= GPIO_NOPULL;
	GPIO_InitStruct.Speed 		= GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
	
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	USART6_handle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_TXINVERT_INIT | UART_ADVFEATURE_DATAINVERT_INIT
																					  | UART_ADVFEATURE_MSBFIRST_INIT;
	USART6_handle.AdvancedInit.TxPinLevelInvert = UART_ADVFEATURE_TXINV_ENABLE;
	USART6_handle.AdvancedInit.DataInvert = UART_ADVFEATURE_DATAINV_ENABLE;
	USART6_handle.AdvancedInit.MSBFirst = UART_ADVFEATURE_MSBFIRST_ENABLE;

	USART6_handle.Instance = USART6;
	USART6_handle.Init.BaudRate = BAUDRATE;
	USART6_handle.Init.WordLength = USART_WORDLENGTH_7B;
	USART6_handle.Init.StopBits = USART_STOPBITS_1;
	USART6_handle.Init.Parity = USART_PARITY_NONE;
	USART6_handle.Init.Mode = USART_MODE_TX;
	USART6_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	
	//Configuration DMA 
	dma_conf();	
	
	__HAL_USART_ENABLE_IT(&USART6_handle , USART_IT_TC);
	
	usart_status = HAL_UART_Init(&USART6_handle);
	
	#ifdef USART_IT_RX_ON
			USART6 -> CR1 |= USART_CR1_RXNEIE;
	#endif
		
	HAL_NVIC_SetPriority(USART6_IRQn , 0 , 1 );
	HAL_NVIC_EnableIRQ(USART6_IRQn);
	
	HAL_NVIC_SetPriority(DMA2_Stream6_IRQn , 0 , 1 );
	HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);
	
	return usart_status;

}

//======================================================================================
void dma_conf(void){
	
	DMA2_CLK_ENABLE();
	 
	//FILL OF STRUCTURE TO INIT DMA
	DMA_handle.Instance 								= DMA2_Stream6;
	DMA_handle.Init.Channel 						= DMA_CHANNEL_5;					
	DMA_handle.Init.Direction 					= DMA_MEMORY_TO_PERIPH;   
	DMA_handle.Init.MemInc 							= DMA_MINC_ENABLE;				
	DMA_handle.Init.PeriphInc 					= DMA_PINC_DISABLE;				
	DMA_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;		
	DMA_handle.Init.MemDataAlignment		= DMA_MDATAALIGN_BYTE;		
	DMA_handle.Init.Mode 								= DMA_NORMAL;							
	DMA_handle.Init.Priority 						= DMA_PRIORITY_LOW;		
	DMA_handle.Init.FIFOMode 						= DMA_FIFOMODE_ENABLE;		
	DMA_handle.Init.FIFOThreshold				= DMA_FIFO_THRESHOLD_FULL;
	DMA_handle.Init.MemBurst						= DMA_MBURST_SINGLE;			
	DMA_handle.Init.PeriphBurst					= DMA_PBURST_SINGLE;			
	
	if(!(HAL_DMA_Init(&DMA_handle))== HAL_OK){
		//if error then
		usart1_WriteS("\n\r\n\r ERROR IN DMA INIT \n\r ");
		error();
	}
	__HAL_LINKDMA(&USART6_handle, hdmatx, DMA_handle);
}

//======================================================================================
void DMA2_Stream6_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&DMA_handle);
}

//======================================================================================
void USART6_IRQHandler(void){
	
	HAL_UART_IRQHandler(&USART6_handle);
}
 
//======================================================================================
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
		
	flag_usart_tc = 1;
}

//======================================================================================
void usart6_Write(char data){	
	while(!(__HAL_USART_GET_FLAG(&USART6_handle, USART_FLAG_TXE)));	
		
	USART6 -> TDR = data;
} 

//======================================================================================
void usart6_WriteS(char *s){
	while(*s)
	{
		while(!(__HAL_USART_GET_FLAG(&USART6_handle, USART_FLAG_TC)));
		usart6_Write( *s++);
		
	}
}





