/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "ui.h"
#include "ui_conf.h"
#include "Button.h"
#include "Display.h"

ui_t ui;

/* Task Handle */
TaskHandle_t ui_task_handle;
TaskHandle_t WaveTestTask_Handle;
TaskHandle_t SystemStateUpdateTask_Handle;

/* Queue Handle */
QueueHandle_t WaveTest_Queue;

/* Global Variable */
int Wave_TestData;

void WaveTest_Task(void *pvParameters)
{
    int Wave_Data = 0;
    while(1)
    {
        Wave_Data = rand()%600;
        xQueueSend(WaveTest_Queue, &Wave_Data, 0);
        vTaskDelay(50);
    }
}

char FreeHeap[20];
void SystemStateUpdate_Task(void *pvParameters)
{
    while(1)
    {
        snprintf(FreeHeap, sizeof(FreeHeap), "%d", (int)(uxTaskGetStackHighWaterMark(ui_task_handle)));
        vTaskDelay(500);
    }
}

void ui_task(void *pvParameter)
{
    while (1) {
        ui_loop(&ui);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    Button_Init();
    Display_Init();
    MiaoUi_Setup(&ui);
    xTaskCreate(ui_task, "ui", 1*2048, NULL, 5, &ui_task_handle);
    WaveTest_Queue = xQueueCreate(1, sizeof(int));
    xTaskCreate(WaveTest_Task, "WaveTest", 1*2048, NULL, 4, &WaveTestTask_Handle);
    xTaskCreate(SystemStateUpdate_Task, "SystemStateUpdate", 1*2048, NULL, 1, &SystemStateUpdateTask_Handle);
}
