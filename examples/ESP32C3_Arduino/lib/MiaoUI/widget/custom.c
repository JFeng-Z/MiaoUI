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
#include "custom.h"
#include "display/dispDriver.h"
#include "indev/indevDriver.h"
#include <stdio.h>
#include "images/image.h"
#include "version.h"

#if(UI_USE_FREERTOS == 1)
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#endif

const unsigned char UI_NAME_LOGO[] = {

    0x80, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x08, 0x01, 0xc0, 0xe3, 0x10, 0x00, 0x00, 0x08, 0x8c, 0x01, 0x60, 0xf3, 0x18, 0x00, 0x00, 0x0c, 0x8c, 0x01, 0x30, 0xdb, 0x00, 0x00, 0x00, 0x0c, 0x8c, 0x00, 0x30, 0xc9, 0x00, 0x00, 0x00, 0x0c,
    0x8c, 0x00, 0x18, 0x4d, 0x00, 0x1e, 0x1c, 0x04, 0xc4, 0x00, 0x88, 0x47, 0x0c, 0x1f, 0x3f, 0x04, 0xc6, 0x00, 0x8c, 0x43, 0x8c, 0x09, 0x33, 0x06, 0x46, 0x00, 0x8c, 0x63, 0xc4, 0x88, 0x31, 0x02, 0x63, 0x00, 0x86, 0x61, 0x44, 0xcc,
    0x30, 0x02, 0x63, 0x00, 0xc6, 0x61, 0x66, 0xce, 0x10, 0x82, 0x61, 0x00, 0xc2, 0x20, 0x66, 0xc7, 0x18, 0xc2, 0x20, 0x00, 0xc3, 0x20, 0xc6, 0xc5, 0x0f, 0x7e, 0x20, 0x00, 0x43, 0x00, 0xc2, 0x84, 0x07, 0x3c, 0x20, 0x00

};

const unsigned char UI_URL[] = {

    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xaf, 0xbf, 0xff, 0xfe, 0xdf, 0xff, 0xf7, 0xfb, 0xab, 0xfe, 0xf4, 0xd6, 0xff, 0x69, 0xff, 0xf9, 0xaf,
    0xfb, 0xbd, 0xfe, 0xef, 0xd9, 0xfd, 0xfb, 0xaf, 0xef, 0xaf, 0xfa, 0xef, 0xf0, 0xbe, 0xf7, 0xff, 0xef, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff

};

//首页
void Draw_Home(ui_t *ui)
{
    int16_t y     = 128;
    uint8_t state = 0;
    uint8_t color = 1;
    while(1)
    {
        if(indevScan( ) == UI_ACTION_ENTER)
            return;

        Disp_ClearBuffer( );
        Disp_SetDrawColor(&color);

        switch(state)
        {
        case 0:
            ui->dialog.nowWide = (uint16_t)easeInOutCirc(ui->dialog.times, 0, 30, 20);
            ui->dialog.times++;
            if(ui->dialog.times == 20)
            {
                state = 1;
            }
            break;
        case 1:
            ui->dialog.times = 0;
            y                = (int16_t)UI_Animation(26.0, (float)y, &ui->animation.textPage_ani);
            Disp_DrawXBMP(34, y, 57, 14, UI_NAME_LOGO);
            if(y == 26)
            {
                state = 2;
                y     = 0;
            }
            break;
        case 2:
            y = (int16_t)UI_Animation(14.0, (float)y, &ui->animation.textPage_ani);
            Disp_DrawXBMP(34, 26, 57, 14, UI_NAME_LOGO);
            Disp_SetFont(font_home_h6w4);
            Disp_DrawStr(y, 58, VERSION_PROJECT_LINK);
            if(y == 12)
            {
                state = 3;
                y     = 128;
            }
            break;
        case 3:
            y = (int16_t)UI_Animation(0.0, (float)y, &ui->animation.textPage_ani);
            Disp_DrawXBMP(34, 26, 57, 14, UI_NAME_LOGO);
            Disp_SetFont(font_home_h6w4);
            Disp_DrawStr(14, 58, VERSION_PROJECT_LINK);
            Disp_SetFont(UI_FONT);
            Disp_DrawStr(y, 16, "Version:");
            if(y == 0)
            {
                state = 4;
                y     = 128;
            }
            break;
        case 4:
            y = (int16_t)UI_Animation(54.0, (float)y, &ui->animation.textPage_ani);
            Disp_DrawXBMP(34, 26, 57, 14, UI_NAME_LOGO);
            Disp_SetFont(font_home_h6w4);
            Disp_DrawStr(14, 58, VERSION_PROJECT_LINK);
            Disp_SetFont(UI_FONT);
            Disp_DrawStr(0, 16, "Version:");
            Disp_DrawStr(y, 16, "1");
            if(y == 54)
            {
                state = 5;
                y     = 128;
            }
            break;
        case 5:
            y = (int16_t)UI_Animation(54.0, (float)y, &ui->animation.textPage_ani);
            Disp_DrawXBMP(34, 26, 57, 14, UI_NAME_LOGO);
            Disp_SetFont(font_home_h6w4);
            Disp_DrawStr(14, 58, VERSION_PROJECT_LINK);
            Disp_SetFont(UI_FONT);
            Disp_DrawStr(0, 16, "Version:");
            Disp_DrawStr(54, 16, "1");
            Disp_DrawStr(y + 6, 16, ".");
            if(y == 54)
            {
                state = 6;
                y     = 128;
            }
            break;
        case 6:
            y = (int16_t)UI_Animation(54.0, (float)y, &ui->animation.textPage_ani);
            Disp_DrawXBMP(34, 26, 57, 14, UI_NAME_LOGO);
            Disp_SetFont(font_home_h6w4);
            Disp_DrawStr(14, 58, VERSION_PROJECT_LINK);
            Disp_SetFont(UI_FONT);
            Disp_DrawStr(0, 16, "Version:");
            Disp_DrawStr(54, 16, "1");
            Disp_DrawStr(60, 16, ".");
            Disp_DrawStr(y + 12, 16, "2");
            if(y == 54)
            {
                state = 7;
            }
            break;
        case 7:
            return;
        default:
            break;
        }
        Disp_DrawLine(64, 45, 64 - ui->dialog.nowWide, 45);
        Disp_DrawLine(64, 45, 64 + ui->dialog.nowWide, 45);

        Disp_SendBuffer( );
    }
}

const unsigned char AUTHOR[] = {

    0x00, 0x00, 0x40, 0x10, 0x00, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x90, 0x00, 0x00, 0x04, 0x88, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0x00, 0x00, 0x08, 0x20, 0x80, 0x28, 0x80, 0x20, 0x00, 0x00, 0x44, 0x00, 0x20,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x02, 0x01, 0x20, 0x00, 0x08, 0x02, 0x00, 0x20, 0x00, 0x08, 0x02, 0x00, 0x08, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x08, 0x01, 0x00, 0x01, 0x10, 0x20, 0x00, 0x08, 0x40, 0x00, 0x00, 0x80, 0x00, 0x00, 0x89, 0x04, 0x01, 0x00, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x10, 0x00, 0x10, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x00, 0x00, 0x81, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x04, 0x00, 0x00, 0x08, 0x02, 0x20, 0x20, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x08, 0x10, 0x02, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x80, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x04,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3d, 0x00, 0x00, 0x00, 0x81, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x7f, 0x40, 0x04, 0x22, 0x10, 0x00, 0x75, 0x10, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02,
    0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0x30, 0x00, 0x00, 0x40, 0x00, 0xe4, 0x71, 0x01, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x8b, 0x08, 0x04, 0x00, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x07, 0x00,
    0x00, 0x80, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x20, 0xff, 0xff, 0x07, 0x00, 0x00, 0x80, 0xff, 0xff, 0x0f, 0x10, 0x00, 0x08, 0xf9, 0xff, 0x1f, 0x00, 0x5a, 0x01, 0xf0, 0xff, 0x0f, 0x09, 0xff, 0x01, 0xf1, 0xff, 0x01, 0x00, 0xff, 0x32, 0xf8, 0xff, 0xa1, 0x1e, 0x80, 0x4f, 0xf8, 0xff,
    0x01, 0x00, 0x81, 0x37, 0xf0, 0xff, 0x01, 0x00, 0x01, 0x7e, 0xf8, 0xff, 0x08, 0x00, 0x29, 0x3c, 0xf3, 0xff, 0x02, 0x00, 0x85, 0x80, 0xff, 0xff, 0x06, 0x00, 0x00, 0x80, 0xfb, 0x7f, 0x0f, 0x00, 0x00, 0x80, 0xff, 0x7f, 0x47, 0x00

};

void Show_Version(ui_t *ui)
{
    int16_t value = -128;
    uint8_t state = 0;
    while(1)
    {
        if(indevScan( ) == UI_ACTION_ENTER)
            return;

        Disp_ClearBuffer( );

        switch(state)
        {
        case 0:
            value = (int16_t)UI_Animation(0.0, (float)value, &ui->animation.textPage_ani);
            Disp_DrawXBMP(value, 0, 45, 60, AUTHOR);
            if(value == 0)
            {
                state = 1;
                value = 128;
            }
            break;
        case 1:
            value = (int16_t)UI_Animation(50, (float)value, &ui->animation.textPage_ani);
            Disp_DrawXBMP(0, 0, 45, 60, AUTHOR);
            Disp_SetFont(font_home_h6w4);
            Disp_DrawStr(value, 6, "Author:JFeng-Z");
            Disp_DrawStr(value, 18, "UI:MiaoUI");
            Disp_DrawStr(value, 30, "Version:1.2");
            Disp_DrawStr(value, 42, "OS:FreeRTOS v10.3");
            Disp_DrawStr(value, 56, "Hardware:STM32F103");
            break;
        default:
            break;
        }
        Disp_SendBuffer( );
    }
}

void Show_Logo(ui_t *ui)
{
    Disp_ClearBuffer( );
    Disp_DrawXBMP(34, 26, 57, 14, UI_NAME_LOGO);
    Disp_SendBuffer( );
}

#if(UI_USE_FREERTOS == 1)
void TaskLvel_Setting(ui_t *ui)
{
    vTaskPrioritySet(*ui->nowItem->element->data->dataRootTask, *(UBaseType_t *)ui->nowItem->element->data->ptr);
}
#endif
