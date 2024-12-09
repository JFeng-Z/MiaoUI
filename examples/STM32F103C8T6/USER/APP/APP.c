#include "APP.h"
#include "APP_Buzzer.h"
#include "APP_Button.h"
#include "APP_MPU6050.h"
#include "APP_Ui.h"
#include "APP_OSTest.h"

#include "stdio.h"
#include "stdlib.h"

#if ( UI_USE_FREERTOS == 1 )

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

static void APP_TaskCreate(void)
{
    xTaskCreate((TaskFunction_t )UI_Task, "UI", 256, &ui, 5, &UiTask_Handle);
    xTaskCreate((TaskFunction_t )WaveTest_Task, "WaveTest", 128, NULL, 1, &WaveTestTask_Handle);
    xTaskCreate((TaskFunction_t )MPU6050Update_Task, "MPU6050Update", 128, NULL, 1, &MPU6050UpdateTask_Handle);
    xTaskCreate((TaskFunction_t )SystemStateUpdate_Task, "SystemStateUpdate", 128, NULL, 1, &SystemStateUpdateTask_Handle);
}

static void APP_QueueCreat(void)
{
    WaveTest_Queue = xQueueCreate(1, sizeof(int));
    MPU6050Update_Mutex = xSemaphoreCreateMutex();
}

#endif

void APP_Init(void)
{
    APP_Button_Setup();
    APP_MiaoUi_Setup();
    APP_Buzzer_Setup();
    #if ( UI_USE_FREERTOS == 1 )
    APP_QueueCreat();
    APP_TaskCreate();
    vTaskStartScheduler();
    #endif
    #if ( UI_USE_FREERTOS == 0 )
    while (1)
    {
        Wave_TestData = rand()%600;
        UI_Loop();
    }
    #endif
}
