/**
* \file timer.c
* \brief Plik c - Driver do akcelerometru LIS3DSH
* \author Michal Kruk
* \date 13-06-2016
*/


#include "timer.h"

#define TIM_INIT_ERROR 2;

uint8_t buf_cnt;

volatile uint8_t flag_usart_tc; 
volatile 	uint8_t buf_tasma[255][240];

extern UART_HandleTypeDef USART6_handle;
TIM_HandleTypeDef		TIM3_HandleStruct;
//======================================================================================
uint8_t tim3_init(void){

		uint8_t tim3_return;
		char tim3_return_buf[20];
	
		tim3_return = TIM_INIT_ERROR;
		
		__HAL_RCC_TIM3_CLK_ENABLE();
	
				TIM3_HandleStruct.Instance = TIM3;
				TIM3_HandleStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
				TIM3_HandleStruct.Init.Prescaler = 10800 - 1;
				TIM3_HandleStruct.Init.Period = 100  - 1; //Przerwanie co 10 ms
		
				HAL_NVIC_SetPriority(TIM3_IRQn, 0, 4);
				HAL_NVIC_EnableIRQ(TIM3_IRQn);
	
				tim3_return =	HAL_TIM_Base_Init(&TIM3_HandleStruct);
					if(tim3_return != 0){
						sprintf(tim3_return_buf , "\r\n### ERROR IN TIM3 INIT! HAL STATUS: %d" , tim3_return);
						usart1_WriteS(tim3_return_buf);
					}
	
				HAL_TIM_Base_Start_IT(&TIM3_HandleStruct);

		return tim3_return;
}

//======================================================================================
void TIM3_IRQHandler(void)
{		
		if(__HAL_TIM_GET_FLAG(&TIM3_HandleStruct, TIM_SR_UIF)){
				__HAL_TIM_CLEAR_FLAG(&TIM3_HandleStruct, TIM_SR_UIF);
		
					gpio_tim_mes_set();
				HAL_UART_Transmit_DMA(&USART6_handle, (uint8_t*)buf_tasma[buf_cnt], 240);
			//		usart6_WriteS(buf_tasma[buf_cnt]);
			
				while(flag_usart_tc == 0);
						buf_cnt++;
						if(buf_cnt == 255) buf_cnt = 0;
		}
					gpio_tim_mes_reset();
}

