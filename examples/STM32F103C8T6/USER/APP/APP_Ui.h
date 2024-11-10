#ifndef __APP_UI_H__
#define __APP_UI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "ui_conf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

extern TaskHandle_t UiTask_Handle;
extern ui_t ui;    

void APP_MiaoUi_Setup(void);
void UI_Loop(void);
void UI_Task(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif
