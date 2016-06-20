/**
* \file error.c
* \brief Plik definiujacy bledy
* \author Michal Kruk
* \date 12-06-2016
*/


#include "error.h"

											//MAX APPLICATION TIME 49 DAYS
extern volatile uint32_t application_time;  


//=============================================================================================

void error(void){

	char buf[30];
	
	sprintf(buf, "\r\n###APPLICATION_TIME: %d [ms]",application_time); 
	usart1_WriteS(USART1  ,buf);
	
	while(1){
			led_toggle(GPIO_PIN_1);
			HAL_Delay(100);
	}
}

