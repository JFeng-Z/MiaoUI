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
#include "wave.h"
#include "stdio.h"
#include "display/dispDriver.h"

#if ( UI_USE_FREERTOS == 1 )
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#endif

// 横坐标轴位置
#define AXIS_HOR_X0 UI_FONT_WIDTH*4
#define AXIS_HOR_Y0 (UI_VER_RES - 2*UI_FONT_HIGHT)
#define AXIS_HOR_X1 UI_HOR_RES
#define AXIS_HOR_Y1 AXIS_HOR_Y0
// 纵坐标轴位置
#define AXIS_VER_X0 UI_FONT_WIDTH*4
#define AXIS_VER_Y0 AXIS_HOR_Y0
#define AXIS_VER_X1 AXIS_VER_X0
#define AXIS_VER_Y1 0
// 波形显示区域
#define WAVE_X UI_FONT_WIDTH*4
#define WAVE_H AXIS_HOR_Y0

uint8_t buffer[UI_HOR_RES];

#if ( UI_USE_FREERTOS == 1 )
void Wave_Widget(ui_t *ui)
{
    uint8_t time;
    char str[30];
    float value = 0;
    int ri_queue = 0;
    float rf_queue = 0;
    float temp = 0;
    if(ui->nowItem->element->data->dataRootTask != NULL)
    {
        if(eTaskGetState(*ui->nowItem->element->data->dataRootTask) != eSuspended)
        {
            switch (ui->nowItem->element->data->dataType)
            {
            case UI_DATA_INT:
                if(ui->nowItem->element->data->dataRootQueue != NULL)xQueueReceive(*ui->nowItem->element->data->dataRootQueue, &ri_queue, portMAX_DELAY);
                value = (float)ri_queue;
                break;
            case UI_DATA_FLOAT:
                if(ui->nowItem->element->data->dataRootQueue != NULL)xQueueReceive(*ui->nowItem->element->data->dataRootQueue, &rf_queue, portMAX_DELAY);
                value = rf_queue;
                break;
            default:
                break;
            }
        }
    }
    for (time = UI_HOR_RES - 1; time > 0; time--)
    {
        buffer[time] = buffer[time - 1];
    }
    if(value != ui->nowItem->element->data->min)
    temp = ((float )(value - ui->nowItem->element->data->min) / (float)((ui->nowItem->element->data->max - ui->nowItem->element->data->min))) * WAVE_H;
    else temp = 0;
    buffer[0] = (uint8_t)temp;
    Disp_ClearBuffer();
    Disp_SetDrawColor(&ui->bgColor);
    Disp_DrawBox(0, 0, UI_HOR_RES, UI_VER_RES);
    uint8_t color = ui->bgColor^0x01;
    Disp_SetDrawColor(&color);

    Disp_DrawLine(AXIS_HOR_X0, AXIS_HOR_Y0, AXIS_HOR_X1, AXIS_HOR_Y1);
    Disp_DrawLine(AXIS_VER_X0, AXIS_VER_Y0, AXIS_VER_X1, AXIS_VER_Y1);

    for (time = 0; time < UI_HOR_RES - 1; time++)
    {
        Disp_DrawLine(time + WAVE_X, WAVE_H - buffer[time], time + WAVE_X + 1, WAVE_H - buffer[time + 1]);
    }
    switch (ui->nowItem->element->data->dataType)
    {
    case UI_DATA_INT:
        snprintf(str, sizeof(str), "value:%d ", ri_queue);
        break;
    case UI_DATA_FLOAT:
        snprintf(str, sizeof(str), "value:%.2f ", rf_queue);
        break;
    default:
        break;
    }
    Disp_DrawStr(2, UI_VER_RES, str);
    snprintf(str, sizeof(str), "%d", ui->nowItem->element->data->max);
    Disp_DrawStr(2, UI_FONT_HIGHT, str);
    snprintf(str, sizeof(str), "%d", ui->nowItem->element->data->min);
    Disp_DrawStr(2, UI_VER_RES - UI_FONT_HIGHT, str);
    Disp_DrawStr(UI_HOR_RES - UI_FONT_WIDTH*4, UI_VER_RES - UI_FONT_HIGHT, "time");
    Disp_SendBuffer();
}
#endif

#if ( UI_USE_FREERTOS == 0 )
void Wave_Widget(ui_t *ui)
{
    uint8_t time;
    char str[30];
    float value = 0;
    float temp = 0;
    switch (ui->nowItem->element->data->dataType)
    {
    case UI_DATA_INT:
        value = (float )*(int *)ui->nowItem->element->data->ptr;
        break;
    case UI_DATA_FLOAT:
        value = *(float *)ui->nowItem->element->data->ptr;
        break;
    default:
        break;
    }
    for (time = UI_HOR_RES - 1; time > 0; time--)
    {
        buffer[time] = buffer[time - 1];
    }
    if(value != ui->nowItem->element->data->min)
    temp = ((float )(value - ui->nowItem->element->data->min) / (float)((ui->nowItem->element->data->max - ui->nowItem->element->data->min))) * WAVE_H;
    else temp = 0;
    buffer[0] = (uint8_t)temp;
    Disp_ClearBuffer();
    Disp_SetDrawColor(&ui->bgColor);
    Disp_DrawBox(0, 0, UI_HOR_RES, UI_VER_RES);
    uint8_t color = ui->bgColor^0x01;
    Disp_SetDrawColor(&color);

    Disp_DrawLine(AXIS_HOR_X0, AXIS_HOR_Y0, AXIS_HOR_X1, AXIS_HOR_Y1);
    Disp_DrawLine(AXIS_VER_X0, AXIS_VER_Y0, AXIS_VER_X1, AXIS_VER_Y1);

    for (time = 0; time < UI_HOR_RES - 1; time++)
    {
        Disp_DrawLine(time + WAVE_X, WAVE_H - buffer[time], time + WAVE_X + 1, WAVE_H - buffer[time + 1]);
    }
    switch (ui->nowItem->element->data->dataType)
    {
    case UI_DATA_INT:
        snprintf(str, sizeof(str), "value:%d ", *(int *)ui->nowItem->element->data->ptr);
        break;
    case UI_DATA_FLOAT:
        snprintf(str, sizeof(str), "value:%.2f ", *(float *)ui->nowItem->element->data->ptr);
        break;
    default:
        break;
    }
    Disp_DrawStr(2, UI_VER_RES, str);
    snprintf(str, sizeof(str), "%d", ui->nowItem->element->data->max);
    Disp_DrawStr(2, UI_FONT_HIGHT, str);
    snprintf(str, sizeof(str), "%d", ui->nowItem->element->data->min);
    Disp_DrawStr(2, UI_VER_RES - UI_FONT_HIGHT, str);
    Disp_DrawStr(UI_HOR_RES - UI_FONT_WIDTH*4, UI_VER_RES - UI_FONT_HIGHT, "time");
    Disp_SendBuffer();
}
#endif
