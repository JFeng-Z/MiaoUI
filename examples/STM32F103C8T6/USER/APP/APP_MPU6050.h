#ifndef __APP_MPU6050_H__
#define __APP_MPU6050_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

extern TaskHandle_t MPU6050UpdateTask_Handle;
extern SemaphoreHandle_t MPU6050Update_Mutex;
extern float Pitch, Roll, Yaw;

void MPU6050Update_Task(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif
