#include "HAL_Button.h"

#define BUTTON_TOP_CLOCK RCC_APB2Periph_GPIOB
#define BUTTON_MID_CLOCK RCC_APB2Periph_GPIOB
#define BUTTON_DOWN_CLOCK RCC_APB2Periph_GPIOB

#define BUTTON_TOP_PORT GPIOB
#define BUTTON_MID_PORT GPIOB
#define BUTTON_DOWN_PORT GPIOB

#define BUTTON_TOP_PIN GPIO_Pin_12
#define BUTTON_MID_PIN GPIO_Pin_13
#define BUTTON_DOWN_PIN GPIO_Pin_14

void HAL_Button_Init(void)
{
    RCC_APB2PeriphClockCmd(BUTTON_TOP_CLOCK | BUTTON_MID_CLOCK | BUTTON_DOWN_CLOCK, ENABLE);
    GPIO_InitTypeDef gpio_init_struct;
    gpio_init_struct.GPIO_Pin = BUTTON_TOP_PIN | BUTTON_MID_PIN | BUTTON_DOWN_PIN;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(BUTTON_TOP_PORT, &gpio_init_struct);
}

uint8_t Read_Button(button_id id)
{

    switch (id)
    {
    case BUTTON_TOP_ID:
        return GPIO_ReadInputDataBit(BUTTON_TOP_PORT, BUTTON_TOP_PIN);
    case BUTTON_MID_ID:
        return GPIO_ReadInputDataBit(BUTTON_MID_PORT, BUTTON_MID_PIN);
    case BUTTON_DOWN_ID:
        return GPIO_ReadInputDataBit(BUTTON_DOWN_PORT, BUTTON_DOWN_PIN);
    default:
        break;
    }
    return 1;
}