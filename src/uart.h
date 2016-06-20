/**
* \file uart.H
* \brief Plik H - Driver uartu
* \author Michal Kruk
* \date 13-06-2016
*/


#ifndef __uart_H__
#define __uart_H__

#include "init.h"
#include "discovery_boards.h"

uint8_t usart6_init(USART_TypeDef 	*USARTx,
										uint32_t			BAUDRATE,
										GPIO_TypeDef 	*GPIOx,					//PORT TX i RX pin's np. GPIOA
										uint16_t 			USART_PIN_TX, 
										uint16_t 			USART_PIN_RX,
										uint32_t			USART_MODE);
										
uint8_t usart1_init(USART_TypeDef 	*USARTx,
										uint32_t			BAUDRATE,
										GPIO_TypeDef 	*GPIOx,					//PORT TX i RX pin's np. GPIOA
										uint16_t 			USART_PIN_TX, 
										uint16_t 			USART_PIN_RX,
										uint32_t			USART_MODE);				
										
void usart6_Write(USART_TypeDef *USARTx,char data);
void usart6_WriteS(USART_TypeDef *USARTx,char *s);

void usart1_Write(USART_TypeDef *USARTx,char data);
void usart1_WriteS(USART_TypeDef *USARTx,char *s);

void dma_conf(void);
void start_dma(uint8_t *SrcAddress, uint16_t DataLength);

//void HAL_USART_TxCpltCallback(USART_HandleTypeDef *husart);

 #endif // __uart_H__
 
