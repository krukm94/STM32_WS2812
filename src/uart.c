/* ==================================================================================================================================

																												USART SOURCE FILE
																												Author: MK
																												Data: 22.03.2016
									
 ====================================================================================================================================
 */


#include "uart.h"

// TYPEdef's and Handles
UART_HandleTypeDef UART_handle;
DMA_HandleTypeDef	 DMA_handle;

// ----------------------------> VARIABLES

//=============================================================================================
uint8_t usart_init(USART_TypeDef 	*USARTx,
										uint32_t			BAUDRATE,
										GPIO_TypeDef 	*GPIOx,					//PORT TX i RX pin's np. GPIOA
										uint16_t 			USART_PIN_TX, 
										uint16_t 			USART_PIN_RX,
										uint32_t			USART_MODE) {

	
	//zmienna do zwracania statusu funkcji
	uint8_t usart_status;
	
	//inicjalizacja struktur od GPIO
	GPIO_InitTypeDef     GPIO_InitStruct;
	
	usart_status = 0x01;
 
	/* Enable GPIO clock */
	USARTx_GPIO_CLK_ENABLE();

	// Enable clock for USART1 peripheral
	USARTx_CLK_ENABLE();
	
	// Inwersja Start i Stop Bitu
	UART_handle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_TXINVERT_INIT | UART_ADVFEATURE_DATAINVERT_INIT
																					 | UART_ADVFEATURE_MSBFIRST_INIT;
	UART_handle.AdvancedInit.TxPinLevelInvert = UART_ADVFEATURE_TXINV_ENABLE;
	UART_handle.AdvancedInit.DataInvert = UART_ADVFEATURE_DATAINV_ENABLE;
	UART_handle.AdvancedInit.MSBFirst = UART_ADVFEATURE_MSBFIRST_ENABLE;

	/* Configure USART Tx as alternate function */
	GPIO_InitStruct.Pin = USART_PIN_TX;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = GPIO_AF_USART6;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
	

	//UART handle
	UART_handle.Instance = USARTx;
	UART_handle.Init.BaudRate = BAUDRATE;
	UART_handle.Init.WordLength = USART_WORDLENGTH_7B;
	UART_handle.Init.StopBits = USART_STOPBITS_1;
	UART_handle.Init.Parity = USART_PARITY_NONE;
	UART_handle.Init.Mode = USART_MODE;
	UART_handle.hdmatx = &DMA_handle;
	
	
	
	//Init
	usart_status = HAL_UART_Init(&UART_handle);
	

	//USART enable	
	__HAL_UART_ENABLE(&UART_handle);

	#ifdef USART_IT_RX_ON
			USART6 -> CR1 |= USART_CR1_RXNEIE;
	#endif
		
	return usart_status;
}
/* ==================================================================================================================================

																												Configuration DMA 
									
 ====================================================================================================================================
 */								
void dma_conf(){
	
	//SET RCC ON FOR DMA
	DMA2_CLK_ENABLE();
	 
	//FILL OF STRUCTURE TO INIT DMA
	DMA_handle.Instance = DMA2_Stream6;
	DMA_handle.Init.Channel = DMA_CHANNEL_5;							//SELECT CHANNEL
	DMA_handle.Init.Direction = DMA_MEMORY_TO_PERIPH;    //CONFIGURE THE TRANSFER DIRECTION
	DMA_handle.Init.MemInc = DMA_MINC_ENABLE;						//SET INCREMENTATION ON FOR DMA
	DMA_handle.Init.PeriphInc = DMA_PINC_DISABLE;								//DISABLE PERIPHAL INCREMENTATION
	DMA_handle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;	//Specifies the Peripheral data width
	DMA_handle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;			//Specifies the Memory data width.
	DMA_handle.Init.Mode = DMA_NORMAL;									//SER NORMAL MODE FOR DMA
	DMA_handle.Init.Priority = DMA_PRIORITY_VERY_HIGH;	//
	DMA_handle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;		//
	//INIT DMA
	HAL_DMA_Init(&DMA_handle);
	
	//
	//__HAL_LINKDMA(&UART_handle, hdmatx, DMA_handle);	
	__HAL_DMA_ENABLE(&DMA_handle);
	


}//void dma_conf(DMA_TypeDef *DMAx)


/* ==================================================================================================================================

																												START DMA
									
 ====================================================================================================================================
 */	
void start_dma(uint8_t *SrcAddress, uint16_t DataLength){
	HAL_UART_Transmit_DMA(&UART_handle, SrcAddress , DataLength);
}// void start_dma
/* ==================================================================================================================================

																												usart_Write
									
 ====================================================================================================================================
 */
void usart_Write(USART_TypeDef *USARTx,char data){	
	while(!(__HAL_USART_GET_FLAG(&UART_handle, USART_FLAG_TXE)));	
		
	USARTx -> TDR = data;
} //void usart_Write(char data)
/* ==================================================================================================================================

																												usart_WriteS
									
 ====================================================================================================================================
 */
void usart_WriteS(USART_TypeDef *USARTx,char *s){
	while(*s)
	{
		while(!(__HAL_USART_GET_FLAG(&UART_handle, USART_FLAG_TC)));
		usart_Write(USARTx, *s++);
		
	}
}//void usart_WriteS(char *s)
 
/* ==================================================================================================================================

																												END OF FILE
									
 ====================================================================================================================================
 */

