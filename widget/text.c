#include "text.h"
#include "ui.h"
#include "dispDirver.h"
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
