#include "APP_Button.h"
#include "HAL_Button.h"
#include "multi_button.h"
#include "buzzer.h"

/* Global Variable */
Button button[3];
UI_ACTION Action;
extern buzzer_t Buzzer;

static void Callback_Button_Top_Handler(void* btn)
{
    Action = UI_ACTION_UP;
    buzzer_play_times(&Buzzer,10000,100,1);
}

static void Callback_Button_Mid_Handler(void* btn)
{
    Action = UI_ACTION_ENTER;
    buzzer_play_times(&Buzzer,10000,100,1);
}

static void Callback_Button_Down_Handler(void* btn)
{
    Action = UI_ACTION_DOWN;
    buzzer_play_times(&Buzzer,10000,100,1);
}

void APP_Button_Setup(void)
{
    button_init(&button[0], Read_Button, 0, BUTTON_TOP_ID);
    button_init(&button[1], Read_Button, 0, BUTTON_MID_ID);
    button_init(&button[2], Read_Button, 0, BUTTON_DOWN_ID);

    button_attach(&button[0], SINGLE_CLICK, Callback_Button_Top_Handler);
    button_attach(&button[0], LONG_PRESS_HOLD, Callback_Button_Top_Handler);
    button_attach(&button[1], SINGLE_CLICK, Callback_Button_Mid_Handler);
    button_attach(&button[1], LONG_PRESS_HOLD, Callback_Button_Mid_Handler);
    button_attach(&button[2], SINGLE_CLICK, Callback_Button_Down_Handler);
    button_attach(&button[2], LONG_PRESS_HOLD, Callback_Button_Down_Handler);

    button_start(&button[0]);
    button_start(&button[1]);
    button_start(&button[2]);
}

UI_ACTION ButtonScan(void)
{
    switch (Action)
    {
    case UI_ACTION_UP:
        Action = UI_ACTION_NONE;
        return UI_ACTION_UP;
    case UI_ACTION_DOWN:
        Action = UI_ACTION_NONE;
        return UI_ACTION_DOWN;
    case UI_ACTION_ENTER:
        Action = UI_ACTION_NONE;
        return UI_ACTION_ENTER;
    default:
        break;
    }
    return UI_ACTION_NONE;
}
