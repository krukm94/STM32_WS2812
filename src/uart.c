/**
* \file uart.c
* \brief Plik c - Driver uartu
* \author Michal Kruk
* \date 13-06-2016
*/

#include "uart.h"

UART_HandleTypeDef USART1_handle;


//======================================================================================
uint8_t usart1_init(uint32_t	BAUDRATE){


	uint8_t usart_status;
	
	GPIO_InitTypeDef     GPIO_InitStruct;
	
	usart_status = 0x01;
 
	USART1_GPIO_CLK_ENABLE();

	USART1_CLK_ENABLE();
	
	GPIO_InitStruct.Pin 			= GPIO_PIN_9;
	GPIO_InitStruct.Mode		  = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull 			= GPIO_PULLDOWN;
	GPIO_InitStruct.Speed			= GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = GPIO_AF_USART1;
	
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	USART1_handle.Instance				  = USART1;
	USART1_handle.Init.BaudRate 	  = BAUDRATE;
	USART1_handle.Init.WordLength 	= USART_WORDLENGTH_8B;
	USART1_handle.Init.StopBits 		= USART_STOPBITS_1;
	USART1_handle.Init.Parity 			= USART_PARITY_NONE;
	USART1_handle.Init.Mode 				= USART_MODE_TX;

	usart_status = HAL_UART_Init(&USART1_handle);
			
	return usart_status;

}
										

//======================================================================================
void usart1_Write(char data){	
	while(!(__HAL_USART_GET_FLAG(&USART1_handle, USART_FLAG_TXE)));	
		
	USART1 -> TDR = data;
} 

//======================================================================================
void usart1_WriteS(char *s){
	while(*s)
	{
		while(!(__HAL_USART_GET_FLAG(&USART1_handle, USART_FLAG_TC)));
		usart1_Write( *s++);
		
	}
}

