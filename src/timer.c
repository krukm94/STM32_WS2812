/*
 ===========================================================================================================================================================================
																																			SOURCE FILE
																																			TIMER DRIVER
																																			NUCLEO L476RG
																																			MICHAL KRUK

  ===========================================================================================================================================================================
*/ 

/* ---------------------> INCLUDES */
#include "timer.h"
/* ---------------------> MACROS */
#define TIM_INIT_ERROR 2;
/* ---------------------> FUNCTIONS */

/* ---------------------> VARIABLES */
uint8_t r;

/* bufory zbierajace dane z GPS */
extern UART_HandleTypeDef USART6_handle;
extern DMA_HandleTypeDef 	DMA_handle;

extern volatile uint8_t flag_usart_tc;
extern volatile uint8_t buf_tasma[255][240];
extern volatile uint8_t buf_tasma_test[240];


/* ====================================*/
/* ---------------------> Deklaracja uchwytów */
	TIM_HandleTypeDef			TIM3_HandleStruct;




// ===========================================================================================================================================================================

//																						INICJALIZACJA TIM 3

//  ===========================================================================================================================================================================

uint8_t tim3_init(void){

		/* zmienna zwracana przez funkcje */
		uint8_t tim3_return;
		tim3_return = TIM_INIT_ERROR;
		
		/* ENABLE CLOCK FOR TIM1 */
		__HAL_RCC_TIM3_CLK_ENABLE();
	
				/* Ustawienie Nvic */
				HAL_NVIC_SetPriority(TIM3_IRQn, 0, 4);
				HAL_NVIC_EnableIRQ(TIM3_IRQn);
	
				/* wypelnianie struktury do inicjalizacji */
				TIM3_HandleStruct.Instance = TIM3;
				TIM3_HandleStruct.Init.CounterMode = TIM_COUNTERMODE_UP;
				TIM3_HandleStruct.Init.Prescaler = 10800 - 1;
				TIM3_HandleStruct.Init.Period = 100  - 1; //Przerwanie co 10 ms
	
				// INIT OF TIM2		
				tim3_return =	HAL_TIM_Base_Init(&TIM3_HandleStruct);
	
				// ENABLE TIM2
				//__HAL_TIM_ENABLE(&TIM2_HandleStruct);
				
				HAL_TIM_Base_Start_IT(&TIM3_HandleStruct);

				/*Wlaczenie przerwan od TIM2 */
				//__HAL_TIM_ENABLE_IT(&TIM2_HandleStruct, TIM_IT_UPDATE);
				
				HAL_TIM_Base_Init(&TIM3_HandleStruct);
						
		return tim3_return;
}
/*
// ===========================================================================================================================================================================

//																								PRZERWANIE OD TIM 3

//  ===========================================================================================================================================================================
*/
// Przerwania z timera 
void TIM3_IRQHandler(void)
{		
		if(__HAL_TIM_GET_FLAG(&TIM3_HandleStruct, TIM_SR_UIF)){
				__HAL_TIM_CLEAR_FLAG(&TIM3_HandleStruct, TIM_SR_UIF);
			
			gpio_tim_mes_toggle();

			HAL_UART_Transmit_DMA(&USART6_handle, (uint8_t*) buf_tasma_test, sizeof(buf_tasma_test));
		
			
			while(flag_usart_tc == 0);
					r++;
					flag_usart_tc = 0;
					if(r == 255) r = 0;
		}

}
/*
// ===========================================================================================================================================================================

//																																								KONIEC PLIKU

//  ===========================================================================================================================================================================
*/
