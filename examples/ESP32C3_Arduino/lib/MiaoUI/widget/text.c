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
#include "text.h"
#include "core/ui.h"
#include "display/dispDriver.h"
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
