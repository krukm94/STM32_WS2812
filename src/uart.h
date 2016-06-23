/**
* \file uart.H
* \brief Plik H - Driver uartu
* \author Michal Kruk
* \date 13-06-2016
*/


#ifndef __uart_H__
#define __uart_H__

#include "init.h"
							
uint8_t usart1_init(uint32_t	BAUDRATE);								

void usart1_Write(char data);
void usart1_WriteS(char *s);


//void HAL_USART_TxCpltCallback(USART_HandleTypeDef *husart);

 #endif // __uart_H__
 
