#include "HAL_Button.h"
#include "Arduino.h"

#define NEXT_PIN      18
#define PREV_PIN      3
#define SELECT_PIN    8
#define DEBOUNCE_TIME 50

BUTTON_EVENT button_event;

void         button_init(void)
{
    pinMode(NEXT_PIN, INPUT_PULLUP);
    pinMode(PREV_PIN, INPUT_PULLUP);
    pinMode(SELECT_PIN, INPUT_PULLUP);
}
uint8_t key_scan(void)
{
    static uint8_t       last_state    = NONE; // 上一次的按键状态
    static unsigned long last_time     = 0;    // 上一次状态变化的时间

    uint8_t              current_state = NONE;

    // 读取当前按键状态
    if(digitalRead(NEXT_PIN) == LOW)
    {
        current_state = NEXT;
    }
    else if(digitalRead(PREV_PIN) == LOW)
    {
        current_state = PREV;
    }
    else if(digitalRead(SELECT_PIN) == LOW)
    {
        current_state = SELECT;
    }

    // 如果状态发生变化，记录时间
    if(current_state != last_state)
    {
        last_time  = millis( );
        last_state = current_state;
    }

    // 如果状态稳定时间超过消抖时间，返回当前状态
    if(millis( ) - last_time > DEBOUNCE_TIME)
    {
        return current_state;
    }

    return NONE;
}