/*
 * This file is part of the MiaoUI Library.
 *
 * Copyright (c) 2025, JFeng-Z, <2834294740@qq.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Created on: 2025-02-08
 */
#include "parameter.h"
#include "stdio.h"
#include "lib/MiaoUI/core/ui.h"
#include "lib/MiaoUI/display/dispDriver.h"

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
    *(uint8_t *)ui->nowItem->element->data->ptr = ! *(uint8_t *)ui->nowItem->element->data->ptr; // 切换开关状态
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
}
