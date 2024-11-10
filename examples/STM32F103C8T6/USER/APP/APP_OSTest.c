#include "APP_OSTest.h"
#include "APP_Ui.h"
#include "stdio.h"
#include "stdlib.h"

/* Task Handle */
TaskHandle_t WaveTestTask_Handle;
TaskHandle_t SystemStateUpdateTask_Handle;

/* Queue Handle */
QueueHandle_t WaveTest_Queue;

/* Global Variable */
int Wave_TestData;

void WaveTest_Task(void *pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 10;
    int Wave_Data = 0;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    while(1)
    {
        Wave_Data = rand()%600;
        xQueueSend(WaveTest_Queue, &Wave_Data, 0);
        xTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

char FreeHeap[20];
void SystemStateUpdate_Task(void *pvParameters)
{
    while(1)
    {
        snprintf(FreeHeap, sizeof(FreeHeap), "%d", (int)(uxTaskGetStackHighWaterMark(UiTask_Handle)));
        vTaskDelay(500);
    }
}
