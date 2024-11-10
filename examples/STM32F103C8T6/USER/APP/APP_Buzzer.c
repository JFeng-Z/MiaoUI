#include "APP_Buzzer.h"
#include "HAL_Buzzer.h"
#include "buzzer.h"

buzzer_t Buzzer;

/**
 * @brief 初始化蜂鸣器
 */
void APP_Buzzer_Setup(void)
{
  // 配置蜂鸣器对象
  Buzzer.interruptMs = 10; // 每10毫秒触发一次中断，需要与定时器定时一样
  Buzzer.fnx.pwmOut = pwm_set_freq; // 设置频率的函数传递
  // 初始化蜂鸣器
  buzzer_init(&Buzzer);
}
