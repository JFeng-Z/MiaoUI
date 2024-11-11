## 简介

此库提供基于PWM的有源 / 无源蜂鸣器驱动，有源 / 无源蜂鸣器可调节播放时长、间隔、循环、无源蜂鸣器可以通过控制PWM频率播放不同的音调。

## 准备

在使用此库之前需要先实现以下几个内容：

1. 确定设备有无源（PWM外设）有源（GPIO外设）；
2. 无源蜂鸣器需要确定单路 PWM 频率单独可调；
3. 有源蜂鸣器需要根据电路设置开启和关闭的电平；
```  
    #define _HIGH	1
    #define _LOW	0
```

## 注意事项

* 该库自动识别蜂鸣器类型，单个蜂鸣器对象只能配置一个输出 API；
```
    	gpioOutFx gpioOut;
        pwmOutFx pwmOut;
```
* 该库需要一个在定时器内回调处理函数，定时器时长应和初始化 buzzer 时的参数一致；
* 无源蜂鸣器的修改频率接口，输入 0 频率需要关闭 PWM 输出；

## 函数说明

| 函数              |           说明            | 返回 |
|  :----  | :----  | :----  |
|buzzer_err_e buzzer_init(buzzer_t *buzzer)| 初始化一个Buzzer |void|
|void buzzer_stop(buzzer_t *buzzer)|停止一个 Buzzer|void|
|void buzzer_turn_on(buzzer_t *buzzer, uint16_t freq)|开启一个 Buzzer|void|
|void buzzer_play_loop(buzzer_t *buzzer, uint16_t freq, uint16_t period, buzzer_loop_e loop)|开启一个 Buzzer 循环播放单个音符，仅无源|void|
|void buzzer_play_times(buzzer_t *buzzer, uint16_t freq, uint16_t period, uint8_t count)|开启一个 Buzzer 多次播放单个音符，仅无源|void|
|void buzzer_play_loop_array(buzzer_t *buzzer, uint16_t *pPeriod, uint16_t *pFreq, uint16_t len)|启动一个 Buzzer 以播放音符数组|void|
|buzzer_active_e buzzer_is_active(buzzer_t *buzzer)|检查 Buzzer 是否处于活动状态|buzzer_active_e|
|void __attribute__((weak)) buzzer_end_callback(buzzer_t *buzzer) |Buzzer 播放结束回调函数，该函数是一个弱符号函数，在应用程序中重新定义实现|void|
|void buzzer_proc(buzzer_t *buzzer)|Buzzer 任务处理函数，需要定时调用|void|

## 使用方法
1. 调用 buzzer_init(Buzzer) 初始化一个 Buzzer；
2. 调用 buzzer_play_times(Buzzer,4000,1000,1) 播放；

## 示例

```c
/**
 * @brief 声明一个名为 MyBuzzer1 的蜂鸣器对象
 */
buzzer_t MyBuzzer1;

/**
 * @brief 任意定时器中断处理函数
 */
void timer_callback_10ms()
{
    //Buzzer 任务处理函数
    buzzer_proc(MyBuzzer1);
}
/**
 * @brief 设置 PWM 的频率,需要完成传入 0 关闭 PWM
 *
 * @param frequency 频率值，单位为赫兹（Hz）
 */
void pwm_set_freq(uint32_t frequency) {
    if (frequency == 0) {
        // 停止定时器
        timer_disable(TIMER);
    } else {
        // 计算预分频值和周期值
        uint32_t prescaler = SystemCoreClock / frequency - 1;
        // 停止定时器
        timer_disable(TIMER);
        // 更新预分频值和周期值
        timer_prescaler_config(TIMER, prescaler, TIMER_PSC_RELOAD_NOW);
        // 重新启动定时器
        timer_enable(TIMER);
    }
}
/**
 * @brief 蜂鸣器结束回调函数
 *
 * @param buzzer 蜂鸣器对象指针
 */
buzzer_end_callback(buzzer_t *buzzer) 
{
    buzzer_play_loop_array(&mBuzzer,mario_theme_time,mario_theme_melody,mario_theme_len);
}
    
/**
 * @brief 初始化蜂鸣器
 */
void init_buzzer()
{
  buzzer_t *Buzzer;
  Buzzer = &MyBuzzer1;
  // 配置蜂鸣器对象
  Buzzer->interruptMs = 10; // 每10毫秒触发一次中断，需要与定时器定时一样
  Buzzer->fnx.pwmOut = pwm_set_freq; // 设置频率的函数传递
  // 初始化蜂鸣器
  buzzer_init(Buzzer);
}
/**
 * @brief 主函数
 */
void main()
{
    init_pwm();
    init_timer();
    init_buzzer();
    buzzer_play_times(&mBuzzer,4000,1000,4);
    while(1)
    {
        delay(100);
    }
}
```
