
/**
* \file ws2812driver.h
* \brief Plik h - Sterownik diod WS2812
* \author Michal Kruk
* \date 13-06-2016
*/
#ifndef __WS2812_H_
#define __WS2812_H_

#include "init.h"

void dioda(uint8_t R, uint8_t G, uint8_t B, uint8_t buf[]);
void tablica(void);

uint8_t usart6_init(uint32_t	BAUDRATE);
void usart6_Write(char data);
void usart6_WriteS(char *s);
void dma_conf(void);


#endif //__WS2812_H_


