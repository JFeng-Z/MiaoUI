#include "HAL_Tick.h"
#include "multi_button.h"
#include "indevDirver.h"
#include "ui.h"
#include "buzzer.h"

// 初始化定时器，设置1ms周期的中断
void HAL_Tick_Init(void)
{
    // 使能定时器2外设时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 配置定时器2
    TIM_TimeBaseInitTypeDef TIM_InitStruct;
    TIM_InitStruct.TIM_Prescaler = 72 - 1;   // 设置预分频值，将时钟频率降低为1KHz
    TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;         // 向上计数模式
    TIM_InitStruct.TIM_Period = 1000 - 1;                               // 自动重装载寄存器的值，设置为1以产生1ms的中断
    TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;             // 时钟分割: 不分割
    TIM_InitStruct.TIM_RepetitionCounter = 0;                    // 重复计数器的值，设置为0
    TIM_TimeBaseInit(TIM2, &TIM_InitStruct);

    // 使能定时器2更新中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // 配置中断优先级
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    // 启动定时器2
    TIM_Cmd(TIM2, ENABLE);
}

// volatile unsigned long g_SystemTicks;
volatile uint8_t tims1;
volatile uint8_t tims2;
extern buzzer_t Buzzer;
// 定时器2中断服务函数
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        // 清除中断标志位
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        tims1 ++;
        if(tims1 > 5)
        {
            tims1 = 0;
            button_ticks();
        }
        tims2 ++;
        if(tims2 > 10)
        {
            tims2 = 0;
            buzzer_proc(&Buzzer);
        }
        // g_SystemTicks ++;
    }
}

void HAL_Delay_Us(uint16_t nus)
{
    uint32_t count = nus * (SystemCoreClock / 1000000);
    while (count--);
}

void HAL_Delay_Ms(uint32_t xms)
{
	while(xms--)
	{
		HAL_Delay_Us(1000);
	}
}
