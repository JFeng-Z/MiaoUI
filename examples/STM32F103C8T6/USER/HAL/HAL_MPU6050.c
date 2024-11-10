#include "HAL_MPU6050.h"
#include "mpu6050.h"
#include "inv_mpu.h"


void HAL_MPU6050_Init(void)
{
    MPU_Init();
    mpu_dmp_init();
}