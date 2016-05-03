#ifndef __INIT_H_
#define __INIT_H_

//=============================================================================================


#include "stm32f7xx_hal.h"
#include "discovery_boards.h"
#include "uart.h"
#include "itoa.h"
#include "ws2812driver.h"

//============================================= MY INCLUDES ===================================



//=============================================================================================
void init(void);
static void SystemClock_Config(void);
static void led_init(void);
void led_on(uint16_t led);
void led_off(uint16_t led);
void led_toggle(uint16_t led);

#endif //__INIT_H_
