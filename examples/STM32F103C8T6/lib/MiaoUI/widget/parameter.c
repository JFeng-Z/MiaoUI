#include "parameter.h"
#include "stdio.h"
#include "ui.h"
#include "dispDirver.h"

void ParameterSetting_Widget(ui_t *ui)
{
    char value[20] = {0};
    int x = 4, y = 12, w = UI_HOR_RES - 8, h = UI_VER_RES - 32;
    float Step = ui->nowItem->element->data->step;

    #if ( UI_USE_FREERTOS == 1 )
    if(ui->nowItem->element->data->functionType == UI_DATA_FUNCTION_EXIT_EXECUTE)
    {
        if(ui->nowItem->element->data->dataRootMutex != NULL)xSemaphoreTake(*ui->nowItem->element->data->dataRootMutex, portMAX_DELAY);
        if(ui->nowItem->element->data->dataRootTask != NULL)vTaskSuspend(*ui->nowItem->element->data->dataRootTask);
        if(ui->nowItem->element->data->dataRootMutex != NULL)xSemaphoreGive(*ui->nowItem->element->data->dataRootMutex);
    }
    #endif
    
    if (Dialog_Show(ui, x, y, w, h))
    {
        switch (ui->action)
        {
        case UI_ACTION_UP:
            Draw_Scrollbar(ui, x + 4, y + 18, w - 30, 6, 3, Step);
            if(ui->nowItem->element->data->function != NULL && ui->nowItem->element->data->functionType == UI_DATA_FUNCTION_STEP_EXECUTE)ui->nowItem->element->data->function(ui);
            break;
        case UI_ACTION_DOWN:
            Step = -Step;
            Draw_Scrollbar(ui, x + 4, y + 18, w - 30, 6, 3, Step);
            if(ui->nowItem->element->data->function != NULL && ui->nowItem->element->data->functionType == UI_DATA_FUNCTION_STEP_EXECUTE)ui->nowItem->element->data->function(ui);
            break;
        default:
            Draw_Scrollbar(ui, x + 4, y + 18, w - 30, 6, 3, 0);
            break;
        }
        if(ui->nowItem->element->data->name == NULL)ui->nowItem->element->data->name = "Null name";
        switch (ui->nowItem->element->data->dataType)
        {
        case UI_DATA_INT:
            snprintf(value, sizeof(value), "%s:%d ", ui->nowItem->element->data->name, *(int *)(ui->nowItem->element->data->ptr));
            break;
        case UI_DATA_FLOAT:
            snprintf(value, sizeof(value), "%s:%.2f ", ui->nowItem->element->data->name, *(float *)(ui->nowItem->element->data->ptr));
        default:
            break;
        }
        Disp_DrawStr(x + 4, y + 13, value);
        Disp_SendBuffer();
    }
}

void Switch_Widget(ui_t *ui)
{
    if(ui->nowItem->element->data->function != NULL)ui->nowItem->element->data->function(ui);
    #if ( UI_USE_FREERTOS == 1 )
    if(ui->nowItem->element->data->dataRootTask != NULL)
    {
        switch (*(uint8_t *)ui->nowItem->element->data->ptr)
        {
        case false:
            vTaskResume(*ui->nowItem->element->data->dataRootTask);
            break;
        case true:
            vTaskSuspend(*ui->nowItem->element->data->dataRootTask);
            break;
        default:
            break;
        }
    }
    #endif
    *(uint8_t *)ui->nowItem->element->data->ptr = ! *(uint8_t *)ui->nowItem->element->data->ptr; // 切换开关状态
}
