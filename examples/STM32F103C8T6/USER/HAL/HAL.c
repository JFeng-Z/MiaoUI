#include "HAL.h"
#include "HAL_Usart.h"
#include "HAL_Tick.h"
#include "HAL_Buzzer.h"
#include "HAL_Button.h"
#include "HAL_Display.h"
#include "HAL_MPU6050.h"

void HAL_Init(void)
{
	HAL_Usart_Init();
	HAL_Tick_Init();
	HAL_Buzzer_Init();
	HAL_Button_Init();
	HAL_MPU6050_Init();
	HAL_Display_Init();
}
