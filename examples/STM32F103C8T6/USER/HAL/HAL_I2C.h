#ifndef _HAL_I2C_H
#define _HAL_I2C_H

#include "stm32f10x.h"

#define I2C_PORT GPIOB
#define I2C_SCL GPIO_Pin_10
#define I2C_SDA GPIO_Pin_11
#define I2C_RCC RCC_APB2Periph_GPIOB

void HAL_I2C_Init(void);

#endif
