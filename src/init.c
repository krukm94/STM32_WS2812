#include "init.h"


/* ==================================================================================================================================

																												init function
									
 ====================================================================================================================================
 */	
void init(void)
{
	SystemClock_Config();
	//HAL Init
	HAL_Init();
	//LED PORT INIT
	led_init();
	//USART1 INIT
	usart1_init(USART1, 115200 , GPIOA  , GPIO_PIN_9 , GPIO_PIN_3 , USART_MODE_TX);
	
	usart1_WriteS(USART1 , "\n\r\n\r ----> STM32F7 <---- \n\r\n\r");
	
	//USART6 INIt
	usart6_init(USART6 , 2500000 , GPIOC , GPIO_PIN_6 , GPIO_PIN_7 ,USART_MODE_TX);

}


/* ==================================================================================================================================

																												LEd initialization
									
 ====================================================================================================================================
 */	

static void led_init(void)
{
	GPIO_InitTypeDef gpio_struct;
	
	__HAL_RCC_GPIOI_CLK_ENABLE();
	
	gpio_struct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_struct.Pin = LED_ALL;
	gpio_struct.Pull = GPIO_PULLUP;
	
	HAL_GPIO_Init(LED_PORT, &gpio_struct);
}


/* ==================================================================================================================================

																												LED ON 
									
 ====================================================================================================================================
 */	

void led_on(uint16_t led)
{
	HAL_GPIO_WritePin(LED_PORT, led, GPIO_PIN_SET);
}
/* ==================================================================================================================================

																												LED OFF
									
 ====================================================================================================================================
 */	
void led_off(uint16_t led)
{
	HAL_GPIO_WritePin(LED_PORT, led, GPIO_PIN_RESET);
}
/* ==================================================================================================================================

																												LED TOGGLE
									
 ====================================================================================================================================
 */	
void led_toggle(uint16_t led)
{
	HAL_GPIO_TogglePin(LED_PORT, led);
}

/* ==================================================================================================================================

																												ERROR FUNCTION
									
 ====================================================================================================================================
 */	

void error(){

		while(1){
			led_toggle(GPIO_PIN_1);
			HAL_Delay(100);
		}
}

/* ==================================================================================================================================

																												CLOCK CONFIG
									
 ====================================================================================================================================
 */	
/**		System Clock Configuration

  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 432
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;  
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1);
  }
  
  /* Activate the OverDrive to reach the 216 MHz Frequency */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1);
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2; 
  
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
    while(1);
  }  
} // static void SystemClock_Config(void)

