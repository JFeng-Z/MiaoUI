#include "APP_Ui.h"
#include "ui.h"

/* Task Handle */
TaskHandle_t UiTask_Handle;

/* Global Variable */
ui_t ui;    

void APP_MiaoUi_Setup(void)
{
    MiaoUi_Setup(&ui);
}

void UI_Loop(void)
{
    ui_loop(&ui);
}

void UI_Task(void *pvParameters)
{
    while(1)
    {
        ui_loop(pvParameters);
        vTaskDelay(10);
    }
}
