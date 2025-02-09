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
#include "text.h"
#include "ui.h"
#include "dispDriver.h"
#include "string.h"

void Text_Widget(ui_t *ui) 
{
    if (!ui || !ui->nowItem || !ui->nowItem->element || !ui->nowItem->element->text) {
        return;
    }

    const int fontWidth = ui->nowItem->element->text->fontWidth;
    const int fontHight = ui->nowItem->element->text->fontHight;
    const char* text_ptr = ui->nowItem->element->text->ptr;
    const uint8_t * font = ui->nowItem->element->text->font;

    // 设置字体
    Disp_SetFont(font);

    // 计算字符总数
    int char_cnt = strlen(text_ptr);

    // 计算每行的最大字符数
    int lineMaxCnt = UI_HOR_RES / fontWidth - 1;

    // 初始化行号和X坐标
    int line = 0;
    int x = ui->nowItem->element->text->fontWidth - 2;

    // 检查对话框是否显示成功
    if (Dialog_Show(ui, 0, 0, UI_HOR_RES - 2, UI_VER_RES - 2)) {
        for (int i = 0; i < char_cnt; i++) {
            char c = text_ptr[i];
            Disp_DrawStr(x, fontHight + line * fontHight, &c);
            x += fontWidth;
            if ((i + 1) % lineMaxCnt == 0) {
                line++;
                x = ui->nowItem->element->text->fontWidth - 2;
            }
            // 检查是否超出屏幕高度
            if (line * fontHight >= UI_VER_RES - 2) {
                break;
            }
        }
        Disp_SendBuffer();
    }
}
