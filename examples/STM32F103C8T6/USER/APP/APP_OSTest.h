#ifndef __APP_OSTEST_H__
#define __APP_OSTEST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

extern int Wave_TestData;
extern TaskHandle_t WaveTestTask_Handle;
extern TaskHandle_t SystemStateUpdateTask_Handle;
extern QueueHandle_t WaveTest_Queue;

void WaveTest_Task(void *pvParameters);
void SystemStateUpdate_Task(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif
