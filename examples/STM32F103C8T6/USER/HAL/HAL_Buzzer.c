#include "HAL_Buzzer.h"

#define BUZZER_TIM TIM3
#define BUZZER_CLOCK RCC_APB2Periph_GPIOB
#define BUZZER_PORT GPIOB
#define BUZZER_PIN GPIO_Pin_0

void HAL_Buzzer_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
 
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;		;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);
 
    TIM_InternalClockConfig(BUZZER_TIM);
 
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(BUZZER_TIM, &TIM_TimeBaseInitStructure);
 
    TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  //取反PWM波形
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 999;		//CCR 默认占空比为50，音量50
	TIM_OC3Init(BUZZER_TIM, &TIM_OCInitStructure);
	
    TIM_Cmd(BUZZER_TIM, DISABLE);
 
}

/**
 * @brief 设置 PWM 的频率,需要完成传入 0 关闭 PWM
 *
 * @param frequency 频率值，单位为赫兹（Hz）
 */
void pwm_set_freq(uint32_t frequency)
{
    if (frequency == 0) {
        // 停止定时器
        TIM_Cmd(BUZZER_TIM, DISABLE);
    } else {
        // 计算预分频值和周期值
        uint32_t prescaler = SystemCoreClock / frequency - 1;
        // 停止定时器
        TIM_Cmd(BUZZER_TIM, DISABLE);;
        // 更新预分频值和周期值
        TIM_PrescalerConfig(BUZZER_TIM, prescaler, TIM_PSCReloadMode_Update);
        // 重新启动定时器
        TIM_Cmd(BUZZER_TIM, ENABLE);
    }
}
