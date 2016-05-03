/* ==================================================================================================================================

																												USART HEADER FILE
																												Author: MK
																												Data: 22.03.2016
									
 ====================================================================================================================================
 */

#ifndef __uart_H__
#define __uart_H__

// --------------------------> Includes
#include "init.h"
#include "discovery_boards.h"

// --------------------------> Functions
uint8_t usart_init(USART_TypeDef 	*USARTx,
										uint32_t			BAUDRATE,
										GPIO_TypeDef 	*GPIOx,					//PORT TX i RX pin's np. GPIOA
										uint16_t 			USART_PIN_TX, 
										uint16_t 			USART_PIN_RX,
										uint32_t			USART_MODE);
void usart_Write(USART_TypeDef *USARTx,char data);
void usart_WriteS(USART_TypeDef *USARTx,char *s);

void dma_conf();
void start_dma(uint8_t *SrcAddress, uint16_t DataLength);
 #endif // __uart_H__
 

/* ==================================================================================================================================

																												END OF FILE
									
 ====================================================================================================================================
 */
