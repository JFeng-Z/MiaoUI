#ifndef _HAL_BUZZER_H
#define _HAL_BUZZER_H

#include "stm32f10x.h"
#include "buzzer.h"

void HAL_Buzzer_Init(void);
void pwm_set_freq(uint32_t frequency);

#endif
