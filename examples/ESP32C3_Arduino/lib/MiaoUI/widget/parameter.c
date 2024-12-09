/**
<one line to give the program's name and a brief idea of what it does.>
Copyright (C) <2024>  <JianFeng>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "parameter.h"
#include "stdio.h"
#include "core/ui.h"
#include "display/dispDriver.h"

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
