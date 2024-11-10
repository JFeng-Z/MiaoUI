#include "APP_MPU6050.h"
#include "inv_mpu.h"

/* Task Handle */
TaskHandle_t MPU6050UpdateTask_Handle;

/* Queue Handle */
SemaphoreHandle_t MPU6050Update_Mutex;

/* Global Variable */
float Pitch, Roll, Yaw;

void MPU6050Update_Task(void *pvParameters)
{
    while (1)
    {
        xSemaphoreTake(MPU6050Update_Mutex, portMAX_DELAY);
        mpu_dmp_get_data(&Pitch, &Roll, &Yaw);
        xSemaphoreGive(MPU6050Update_Mutex);
    }
}
