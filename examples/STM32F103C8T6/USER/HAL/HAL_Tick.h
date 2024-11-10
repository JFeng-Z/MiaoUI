#ifndef _HAL_TICK_H
#define _HAL_TICK_H

#include "stm32f10x.h"   

void HAL_Tick_Init(void);
void HAL_Delay_Us(uint16_t nus);
void HAL_Delay_Ms(uint32_t xms);

#endif
