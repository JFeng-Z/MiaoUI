#ifndef _HAL_BUTTON_H
#define _HAL_BUTTON_H

#include "stm32f10x.h"

typedef enum
{
    BUTTON_TOP_ID,
    BUTTON_MID_ID,
    BUTTON_DOWN_ID
}button_id;

void HAL_Button_Init(void);
uint8_t Read_Button(button_id id);

#endif
