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
#include "core/ui.h"
#include "display/dispDriver.h"
#include "indev/indevDriver.h"
#include "widget/custom.h"
#include "images/image.h"
#include "widget/parameter.h"
#include "widget/text.h"
#include "widget/wave.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

const uint8_t presetsLogo [] = {
	0xff, 0xff, 0xff, 0x3f, 0xff, 0xc3, 0xff, 0x3f, 0xff, 0x00, 0xfc, 0x3f, 0x3f, 0x00, 0xf0, 0x3f, 
	0x1f, 0x00, 0xe0, 0x3f, 0x0f, 0x00, 0x80, 0x3f, 0x07, 0x00, 0x00, 0x3f, 0x03, 0x7e, 0x00, 0x3e, 
	0x01, 0x7e, 0x00, 0x3c, 0x01, 0x7f, 0x00, 0x38, 0x01, 0x0c, 0x00, 0x38, 0x01, 0xe3, 0x00, 0x30, 
	0x01, 0xc3, 0x00, 0x30, 0xa1, 0xc7, 0x01, 0x30, 0xe3, 0xf7, 0x03, 0x38, 0xcb, 0xf3, 0x03, 0x38, 
	0x03, 0xc0, 0x60, 0x3c, 0x43, 0x00, 0x41, 0x3e, 0x47, 0x80, 0x41, 0x3e, 0xc7, 0xc0, 0x01, 0x38, 
	0xe7, 0xe1, 0x23, 0x30, 0xef, 0xff, 0x1f, 0x20, 0x8f, 0xff, 0x0f, 0x20, 0x0f, 0x03, 0x00, 0x00, 
	0x1f, 0x00, 0x00, 0x20, 0x0f, 0x00, 0x00, 0x20, 0x0f, 0x00, 0x08, 0x20, 0x07, 0x00, 0x00, 0x30, 
	0x07, 0x00, 0x00, 0x38, 0xff, 0xff, 0xff, 0x3f
};

/**
 * 添加项目到页面
 * 
 * 该函数用于向指定的页面添加一个新的项目。项目包括名称、类型、元素、图像等信息，
 * 并且可以设置项目的功能回调。添加的项目将按照链表的形式管理，同时维护页面上项目的数量。
 *
 * @param name 项目名称，不可为NULL。
 * @param type 项目类型，如数据、开关、文本等。
 * @param Element 项目关联的元素，根据项目类型不同，包含不同的数据。
 * @param image 项目显示的图像，如果为NULL，则使用预设图像。
 * @param item 待添加的项目结构体。
 * @param localPage 项目所在的页面结构体。
 * @param nextPage 项目跳转的下一个页面结构体，如果无跳转，则为NULL。
 * @param function 项目对应的函数指针，用于处理项目特定的功能。
 */
void AddItem(const char *name, UI_ITEM_TYPE type, const uint8_t *image, ui_item_t *item, ui_page_t *localPage, ui_page_t *nextPage, ui_item_function function)
{
    // 检查输入参数的有效性
    // 参数检验
    if (!name || !item || !localPage) {
        UI_LOG("Invalid parameter(s)\n");
        return; // 早期返回以避免进一步错误
    }
    item->x = UI_PAGE_INIT_X;
    item->y = UI_PAGE_INIT_Y;
    // 初始化项目的基本信息
    item->itemName = name; // 设置项目名称
    item->itemType = type; // 设置项目类型

    // 如果页面类型为图像且没有指定图像，则使用预设图像
    if(localPage->type == UI_PAGE_ICON && image == NULL)
    {
        item->logo = presetsLogo;
        UI_LOG("%s : Image is null!\n", item->itemName);
    }
    else if(localPage->type == UI_PAGE_ICON && image != NULL) 
    item->logo = image;

    item->page.location = localPage; // 设置项目所在页面

    if(function != NULL)
    item->itemFunction = function; // 设置项目关联的函数

    // 初始化项目链接信息
    /* 初始化项目下一个项为NULL */
    item->nextItem = NULL;

    // 设置跳转页面的父项目为当前项目
    /* 设置跳转页面的父级项目 */
    if (nextPage != NULL)
        nextPage->item.parent = item;
    else // 如果没有下一个页面，则设置为当前页面
        nextPage = localPage;
    item->page.jumpPage = nextPage; // 设置项目跳转页面

    // 如果页面为空，则初始化项目链表
    /* 链式结构创建项目 */
    if (localPage->item.head == NULL) // 如果是首个项目
    {
        // 初始化项目链表头部和尾部
        item->lastItem = item;
        localPage->item.head = item;
        localPage->item.tail = item;
        localPage->length = 0; // 初始化项目计数
    }
    else // 如果不是首个项目
    {
        // 将新项目连接到链表尾部
        // 连接新项目到链表尾部
        item->lastItem = localPage->item.tail;                // 新项目上一个项指向当前尾项目
        localPage->item.tail->nextItem = item;                // 尾项目下一个项指向新项目
        localPage->item.tail = localPage->item.tail->nextItem; // 更新尾项目为新项目
        localPage->length++; // 项目计数加一
    }
    // 设置项目ID为当前页面项目数量
    item->id = localPage->length; // 设置项目ID为当前页面项目计数
    // 关联页面的头尾项目互相指向，用于快速遍历
    // 关联页面的头尾项目互相指向，用于快速遍历
    localPage->item.tail->nextItem = localPage->item.head;  
    localPage->item.head->lastItem = localPage->item.tail;
}

/**
 * @brief 向页面中添加一个新页面。
 * 
 * @param name 新页面的名称。
 * @param page 指向新页面结构体的指针。
 * @param type 新页面的类型。
 */
void AddPage(const char *name, ui_page_t *page, UI_PAGE_TYPE type)
{
    // 初始化新页面的基本信息
    page->pageName = name;
    page->item.head = NULL;
    page->item.tail = NULL;
    page->pageState = UI_PAGE_STATIC;
    page->type = type;
}

float UI_Animation(float targrt, float now, ui_animation_param_t *obj)
{
    float x = now;
    
    // 计算误差
    obj->error = targrt - x;
    // 积分环节，累加误差
    obj->sum_error += obj->error;
    // 微分环节，计算误差变化率
    float delta_error = obj->error - obj->last_error;

    // 计算控制量
    float velocity = obj->kp * obj->error + obj->ki * obj->sum_error + obj->kd * delta_error;
    
    // 更新状态
    x += velocity;
    obj->last_error = obj->error;

    return x;
}

/**
 * 使用圆形函数实现的缓动效果，既适用于渐入也适用于渐出。
 * 
 * @param t 当前时间，表示动画的进度。
 * @param b 初始值，动画开始前的位置。
 * @param c 变化量，动画结束时的总变化。
 * @param d 持续时间，动画的总时长。
 * @return 返回动画当前位置的浮点数。
 * 
 * 该函数的特点是动画的加速和减速都是按照圆形函数的变化规律进行的。
 * 当t小于总时长的一半时，动画以圆形函数的减速形式进行，反之则以加速形式进行。
 * 这种方式使得动画在开始和结束时都比较平滑，适用于需要平滑过渡的动画场景。
 */
float easeInOutCirc(float t, float b, float c, float d) 
{
    // 当前时间归一化至动画周期的一半，如果小于1，则处于动画的前半段
    if ((t /= d / 2) < 1) return -c / 2 * (sqrtf(1 - t * t) - 1) + b;
    // 如果大于等于1，则处于动画的后半段，计算方式有所不同
    return c / 2 * (sqrtf(1 - (t -= 2) * t) + 1) + b;
}

static void Change_UIState(ui_t *ui, UI_STATE state)
{
    ui->menuState = state;
}

static void Cursor_AnimationParam_Init(ui_t *ui, ui_item_t *next_item)
{
    ui->nowItem->page.location->cursorLastColumn = ui->cursor.targrtColumn;
    ui->nowItem->page.location->cursorLastRow = ui->cursor.targrtRow;
    ui->nowItem->page.location->cursorLastWide = ui->cursor.targrtWide;
    ui->cursor.targrtColumn = next_item->x;
    ui->cursor.targrtRow = next_item->y - UI_FONT_HIGHT;
}

static void Cursor_AnimationParam_Change(ui_t *ui)
{
    ui->cursor.targrtColumn = ui->nowItem->page.jumpPage->cursorLastColumn;
    ui->cursor.targrtRow = ui->nowItem->page.jumpPage->cursorLastRow;
    ui->cursor.targrtWide = ui->nowItem->page.jumpPage->cursorLastWide;
}

static void Dialog_AnimationParam_Init(ui_t *ui)
{
    ui->dialog.nowHigh = 0;
    ui->dialog.nowWide = 0;
    ui->dialog.times = 0;
}

static void Scrollbar_Init(ui_t *ui)
{
    ui->scrollbar.value = 0;
}

static void Optionbar_Init(ui_t *ui)
{
    ui->optionbar.nowLenght = 0;
    ui->optionbar.position = 0;
}

/**
 * 绘制对话框
 * @param x 对话框左上角x坐标
 * @param y 对话框左上角y坐标
 * @param w 对话框宽度
 * @param h 对话框高度
 * 该函数首先绘制对话框的边框，然后绘制对话框的背景盒。
 * 使用了OLED显示设备的相关函数来完成绘制操作。
 */
static void Draw_Dialog(ui_t *ui, uint16_t x,uint16_t y,uint16_t Now_w,uint16_t Now_h,int16_t targrtW,int16_t targrtH)
{
    uint8_t bgC = ui->bgColor;
    Disp_SetDrawColor(&bgC);
    Disp_DrawBox(x, y, targrtW, Now_h);
    // 设置绘制背景的颜色，并绘制背景盒
    bgC = bgC^0x01;
    Disp_SetDrawColor(&bgC);
    Disp_DrawLine(x, y, x+Now_w, y);
    Disp_DrawLine(x, y, x, y+Now_h);
    Disp_DrawLine(x+targrtW, y+targrtH, x+targrtW, y+targrtH-Now_h);
    Disp_DrawLine(x+targrtW, y+targrtH, x+targrtW-Now_w, y+targrtH);
}

/**
 * @brief 显示一个按指定尺寸缩放的对话框。
 * 
 * 此函数用于在应用绘制状态时，通过线性动画效果展示一个对话框的缩放过程。函数首先检查当前是否处于应用绘制状态，
 * 如果是，则根据设定的时间和目标尺寸计算当前对话框的宽度和高度，并进行绘制。当动画时间达到预设的对话框显示时间
 * 后，将状态切换到应用运行状态，并返回true。整个过程通过OLED发送缓冲区来更新显示。
 * 
 * @param x 对话框的x坐标。
 * @param y 对话框的y坐标。
 * @param targrtW 目标对话框的宽度。
 * @param targrtH 目标对话框的高度。
 * @return uint8_t 如果动画时间达到预设的对话框显示时间，则返回true；否则返回false。
 */
uint8_t Dialog_Show(ui_t *ui, int16_t x,int16_t y,int16_t targrtW,int16_t targrtH)
{
    // 当前处于应用绘制状态时，处理对话框的缩放动画
    if (ui->menuState == UI_ITEM_DRAWING)
    {
        // 根据当前时间和目标尺寸计算对话框的当前宽度
        ui->dialog.nowWide = (uint16_t )easeInOutCirc(ui->dialog.times, 0, (float)targrtW, UI_DIALOG_SCALE_ANI_TOTAL_TIME);
        // 根据当前时间和目标尺寸计算对话框的当前高度
        ui->dialog.nowHigh = (uint16_t )easeInOutCirc(ui->dialog.times, 0, (float)targrtH, UI_DIALOG_SCALE_ANI_TOTAL_TIME);
        // 绘制当前尺寸的对话框
        Draw_Dialog(ui, x, y, ui->dialog.nowWide, ui->dialog.nowHigh, targrtW, targrtH);
        ui->dialog.times ++;
    }

    // 当动画时间达到预设的对话框显示时间时，切换到应用运行状态
    if ((ui->dialog.nowWide == targrtW) && (ui->dialog.nowHigh == targrtH))
    {
        ui->dialog.times = 0;
        Change_UIState(ui, UI_ITEM_RUNING);
        return true;
    }
    
    Disp_SendBuffer();
    return false;
}

uint8_t Notifications(ui_t *ui, int16_t x,int16_t y,int16_t targrtW,int16_t targrtH)
{
    // 当前处于应用绘制状态时，处理对话框的缩放动画
    if (ui->menuState == UI_ITEM_DRAWING)
    {
        // 根据当前时间和目标尺寸计算对话框的当前宽度
        ui->dialog.nowWide = (uint16_t )easeInOutCirc(ui->dialog.times, 0, (float)targrtW, UI_DIALOG_SCALE_ANI_TOTAL_TIME);
        // 根据当前时间和目标尺寸计算对话框的当前高度
        ui->dialog.nowHigh = (uint16_t )easeInOutCirc(ui->dialog.times, 0, (float)targrtH, UI_DIALOG_SCALE_ANI_TOTAL_TIME);
        // 绘制当前尺寸的对话框
        Draw_Dialog(ui, x, y, ui->dialog.nowWide, ui->dialog.nowHigh, targrtW, targrtH);
        ui->dialog.times ++;
    }

    // 当动画时间达到预设的对话框显示时间时，切换到应用运行状态
    if ((ui->dialog.nowWide == targrtW) && (ui->dialog.nowHigh == targrtH))
    {
        ui->dialog.times = 0;
        char value[20] = {0};
        sprintf(value, "%s OK!", ui->nowItem->itemName);
        Disp_DrawStr(x + 5, y + targrtH/2, value);
        Change_UIState(ui, UI_ITEM_RUNING);
        return true;
    }
    Disp_SendBuffer();
    return false;
}

/**
 * 设置背景颜色
 * @param color 要设置的颜色值，类型为uint8_t
 * 该函数用于将全局背景颜色设置为指定的颜色值。
 */
static void Set_BgColor(ui_t *ui, uint8_t color)
{
    ui->bgColor = color; // 设置背景颜色
}

/**
 * 绘制一个滚动条
 * 该函数根据给定的参数，在OLED屏幕上绘制一个滚动条。滚动条的可见部分的长度
 * 会根据当前值在最小值和最大值之间动态调整。
 * @param x 滚动条左上角的x坐标
 * @param y 滚动条左上角的y坐标
 * @param w 滚动条的宽度
 * @param h 滚动条的高度
 * @param r 滚动条圆角的半径
 * @param data->min 滚动条代表的最小值
 * @param data->max 滚动条代表的最大值
 * @param data->step 滚动条的步进值
 * @param NowValue 滚动条当前的值
 */
void Draw_Scrollbar(ui_t *ui, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, float step)
{
    uint8_t color = 0;
    float temp = 0;
    #if ( UI_USE_FREERTOS == 1 )
    if(ui->nowItem->element->data->dataRootMutex != NULL)xSemaphoreTake(*ui->nowItem->element->data->dataRootMutex, portMAX_DELAY);
    #endif
    switch (ui->nowItem->element->data->dataType)
    {
    case UI_DATA_INT:
        // 根据当前值计算滚动条可见部分的长度
        if (((*(int *)(ui->nowItem->element->data->ptr)) <= ui->nowItem->element->data->max) && ((*(int *)(ui->nowItem->element->data->ptr)) >= ui->nowItem->element->data->min))
        {
            (*(int *)(ui->nowItem->element->data->ptr)) += step;
            if ((*(int *)(ui->nowItem->element->data->ptr)) > ui->nowItem->element->data->max)
            {
                (*(int *)(ui->nowItem->element->data->ptr)) = ui->nowItem->element->data->max;
            }
            if ((*(int *)(ui->nowItem->element->data->ptr)) < ui->nowItem->element->data->min)
            {
                (*(int *)(ui->nowItem->element->data->ptr)) = ui->nowItem->element->data->min;
            }
            temp = (float)(abs((*(int *)(ui->nowItem->element->data->ptr)) - ui->nowItem->element->data->min) * ((w - 6)) / (float)((ui->nowItem->element->data->max - ui->nowItem->element->data->min)) + 6);
        }
        break;
    case UI_DATA_FLOAT:
        // 根据当前值计算滚动条可见部分的长度
        if (((*(float *)(ui->nowItem->element->data->ptr)) <= ui->nowItem->element->data->max) && ((*(float *)(ui->nowItem->element->data->ptr)) >= ui->nowItem->element->data->min))
        {
            (*(float *)(ui->nowItem->element->data->ptr)) += step;
            if ((*(float *)(ui->nowItem->element->data->ptr)) > ui->nowItem->element->data->max)
            {
                (*(float *)(ui->nowItem->element->data->ptr)) = ui->nowItem->element->data->max;
            }
            if ((*(float *)(ui->nowItem->element->data->ptr)) < ui->nowItem->element->data->min)
            {
                (*(float *)(ui->nowItem->element->data->ptr)) = ui->nowItem->element->data->min;
            }
            temp = (float)(abs((*(float *)(ui->nowItem->element->data->ptr)) - ui->nowItem->element->data->min) * ((w - 6)) / (float)((ui->nowItem->element->data->max - ui->nowItem->element->data->min)) + 6);
        }
    default:
        break;
    }
    // 绘制滚动条的填充部分
    color = 0;
    Disp_SetDrawColor(&color);
    Disp_DrawBox(x, y, w, h);
    color = 1;
    Disp_SetDrawColor(&color);
    ui->scrollbar.value = (uint16_t )UI_Animation(temp, (float )ui->scrollbar.value, &ui->animation.scrollbar_ani);
    Disp_DrawBox(x, y, ui->scrollbar.value, h);
    #if ( UI_USE_FREERTOS == 1 )
    if(ui->nowItem->element->data->dataRootMutex != NULL)xSemaphoreGive(*ui->nowItem->element->data->dataRootMutex);
    #endif
}

/**
 * @brief 使屏幕上的内容逐渐消失的函数
 * 
 * @param disapper 一个用于控制消失程度的参数，初始值建议为0，每次调用本函数会自动增加
 * @return uint8_t 返回调整后的disapper值，用于下次调用时继续消失过程
 */
static uint8_t UI_Disapper(ui_t *ui, uint8_t disapper)
{ 
    short disapper_temp = 0;
    // 计算屏幕缓冲区的总长度
    int length = 8 * Disp_GetBufferTileHeight() * Disp_GetBufferTileWidth();
    uint8_t *p = Disp_GetBufferPtr(); // 获取屏幕缓冲区的指针

    // 如果背景色为黑色，那么执行与操作，让像素点逐渐变暗从而消失
    if(ui->bgColor==0)
    { 
        for( int i = 0; i < length; i++) 
        { 
            p[i] = p[i] & (rand()%0xff) >> disapper; // 通过与操作使像素点变暗
        } 
    }
    else // 如果背景色不是黑色，执行或操作，让像素点逐渐变亮从而消失
    { 
        for( int i = 0; i < length; i++) 
        { 
            p[i] = p[i] | (rand()%0xff) >> disapper; // 通过或操作使像素点变亮
        } 
    }
    
    disapper += 2; // 每次调用使消失程度增加，以便逐渐完成消失过程
    if(disapper >= 8) // 当消失程度达到最大值时重置为0，准备下一次调用
    { 
        disapper = 0; 
    } 
    
    Disp_SendBuffer(); // 将更新后的缓冲区内容发送到OLED显示设备
    disapper_temp = disapper;
    return disapper_temp; // 返回调整后的disapper值，供外部调用者使用
}

/**
 * @brief 绘制选项位置
 * 
 * 该函数用于在OLED屏幕上动态绘制选项的位置，实现类似选项滑动选择的效果。
 * 根据当前项和下一个项的信息，计算并绘制出选项的滑动过程。
 * 
 * @param nowItem 当前选项项的指针
 * @param next_item 下一个选项项的指针
 * @return uint8_t 如果绘制过程完成（达到设定的时间），返回true；否则返回false。
 */
static uint8_t Draw_TextPage_Optionbar(ui_t *ui, ui_item_t *now_Item, ui_item_t *next_item)
{
    // 根据下一个项的id和位置长度，计算其理论绘制长度
    ui->optionbar.targetLenght = (UI_VER_RES / (float)(next_item->page.location->length)) *next_item->id;
    // 使用线性插值计算当前的绘制长度
    ui->optionbar.nowLenght = (uint16_t )UI_Animation((float )ui->optionbar.targetLenght, (float )ui->optionbar.nowLenght, &ui->animation.optionbar_ani);
    ui->optionbar.position = (uint16_t )UI_Animation((float )UI_VER_RES, (float )ui->optionbar.position, &ui->animation.optionbarPos_ani);
    // 绘制选项移动的指示线
    Disp_DrawLine(UI_HOR_RES - 7, 0, UI_HOR_RES - 7, ui->optionbar.position);
    // 根据计算出的长度，绘制当前选项的高亮框
    if(ui->optionbar.nowLenght > 3)   // 边的长度必须大于圆角宽度+1，不然会显示异常
    Disp_DrawRBox(UI_HOR_RES - 10, 0, 6, ui->optionbar.nowLenght, 2);

    if(ui->optionbar.nowLenght == ui->optionbar.targetLenght && ui->optionbar.position == UI_VER_RES)
    {
        return true;
    }
    return false;
}

static uint8_t Draw_ImagePage_Optionbar(ui_t *ui, ui_item_t *now_Item, ui_item_t *next_item)
{
    // 根据下一个项的id和位置长度，计算其理论绘制长度
    ui->optionbar.targetLenght = (UI_HOR_RES / (float)(next_item->page.location->length)) *next_item->id;
    // 使用线性插值计算当前的绘制长度
    ui->optionbar.nowLenght = (uint16_t )UI_Animation((float )ui->optionbar.targetLenght, (float )ui->optionbar.nowLenght, &ui->animation.optionbar_ani);
    ui->optionbar.position = (uint16_t )UI_Animation((float )UI_HOR_RES, (float )ui->optionbar.position, &ui->animation.optionbarPos_ani);
    // 绘制选项移动的指示线
    Disp_DrawLine(0, 2, ui->optionbar.position, 2);
    // 根据计算出的长度，绘制当前选项的高亮框
    if(ui->optionbar.nowLenght > 3)   // 边的长度必须大于圆角宽度+1，不然会显示异常
    Disp_DrawRBox(0, 0, ui->optionbar.nowLenght, 6, 2);

    if(ui->optionbar.nowLenght == ui->optionbar.targetLenght && ui->optionbar.position == UI_HOR_RES)
    {
        return true;
    }
    return false;
}

static void Calculate_Page_xy(ui_t *ui, ui_page_t *Page, ui_item_t *now_Item, ui_item_t *next_item)
{
    switch (Page->type)
    {
    case UI_PAGE_TEXT:
        // 计算页面滚动的距离
        if (Page->pageState == UI_PAGE_MOVING)
        {
            if ((next_item->id - now_Item->id) > 0)ui->headY -= ((next_item->id - now_Item->id) > (Page->length - UI_VER_RES/ui->textSpace)) ? ((Page->length + 1 - UI_VER_RES/ui->textSpace) *ui->textSpace) : ui->textSpace;
            else ui->headY += ((now_Item->id - next_item->id) > (Page->length - UI_VER_RES/ui->textSpace)) ? ((Page->length + 1 - UI_VER_RES/ui->textSpace) *ui->textSpace) : ui->textSpace;
            Page->pageState = UI_PAGE_STATIC; // 更新页面状态为静态显示
        }

        // 页面切换时重置第一行位置
        if(next_item->page.location != now_Item->page.location)
        {
            if(now_Item->itemType == UI_ITEM_PARENTS)
            {
                now_Item->page.location->jumpX = ui->headX;
                now_Item->page.location->jumpY = ui->headY;
                ui->headY = UI_PAGE_INIT_Y;
                ui->headX = UI_PAGE_INIT_X;
            }
            else if (now_Item->itemType == UI_ITEM_RETURN)
            {
                ui->headY = next_item->page.location->jumpY;
                ui->headX = next_item->page.location->jumpX;
            }
        }
        break;
    case UI_PAGE_ICON:
        // 计算页面滚动的距离
        if (Page->pageState == UI_PAGE_MOVING)
        {
            if ((next_item->id - now_Item->id) > 0)ui->headX -= ((next_item->id - now_Item->id) > (Page->length - UI_HOR_RES/ui->imageSpace)) ? ((Page->length + 1 - UI_HOR_RES/ui->imageSpace) *ui->imageSpace) : ui->imageSpace;
            else ui->headX += ((now_Item->id - next_item->id) > (Page->length - UI_HOR_RES/ui->imageSpace)) ? ((Page->length + 1 - UI_HOR_RES/ui->imageSpace) *ui->imageSpace) : ui->imageSpace;
            Page->pageState = UI_PAGE_STATIC; // 更新页面状态为静态显示
        }

        // 页面切换时重置第一行位置
        if(next_item->page.location != now_Item->page.location)
        {
            if(now_Item->itemType == UI_ITEM_PARENTS)
            {
                now_Item->page.location->jumpX = ui->headX;
                now_Item->page.location->jumpY = ui->headY;
                ui->headX = UI_PAGE_INIT_X;
                ui->headY = UI_PAGE_INIT_Y;
            }
            else if (now_Item->itemType == UI_ITEM_RETURN)
            {
                ui->headX = next_item->page.location->jumpX;
                ui->headY = next_item->page.location->jumpY;
            }
        }
        break;
    default:
        break;
    }
}

static void Calculate_Item_xy(ui_t *ui, ui_page_t *Page)
{
    ui_item_t * Item = Page->item.head; // 从页面的头部开始遍历
    for (uint16_t i = 0; i <= Page->length; i++)
    {
        switch (Page->type)
        {
        case UI_PAGE_TEXT:
            Item->y = ui->headY + i *ui->textSpace;
            break;
        case UI_PAGE_ICON:
            Item->x = ui->headX + i *ui->imageSpace;
            break;
        default:
            break;
        }
        Item = Item->nextItem;
    }
}

static void Calculate_Coordinate(ui_t *ui, ui_page_t *Page, ui_item_t *now_Item, ui_item_t *next_item)
{
    // 初始化或计算页面滚动时的起始绘制位置
    if(ui->menuState == UI_PAGE_RUNING)
    {
        Calculate_Page_xy(ui, Page, now_Item, next_item);
        Calculate_Item_xy(ui, Page);
    }
}

static void Calculate_PageState(ui_t *ui, ui_page_t *Page, ui_item_t *now_Item,ui_item_t *next_item)
{
    if(next_item->page.location != now_Item->page.location)        
    {
        Page->pageState = UI_PAGE_STATIC;
        return ;
    }
    switch (Page->type)
    {
    case UI_PAGE_TEXT:
        if (next_item->y - UI_FONT_HIGHT > (ui->textSpace*(UI_VER_RES/ui->textSpace) - ui->textSpace) || next_item->y - UI_FONT_HIGHT < 0)  // 防止光标溢出可视范围
        {
            Page->pageState = UI_PAGE_MOVING;
        }
        break;
    case UI_PAGE_ICON:
        if (next_item->x > (ui->imageSpace*(UI_HOR_RES/ui->imageSpace) - ui->imageSpace) || next_item->x < 0)  // 防止光标溢出可视范围
        {
            Page->pageState = UI_PAGE_MOVING;
        }
        break;
    default:
        break;
    }
}

static void Calculate_Cursor(ui_t *ui, ui_page_t *Page, ui_item_t *now_Item,ui_item_t *next_item)
{
    if(next_item->page.location != now_Item->page.location)        
    {
        if(now_Item->itemType == UI_ITEM_PARENTS)Cursor_AnimationParam_Init(ui, next_item);
        else if (now_Item->itemType == UI_ITEM_RETURN)Cursor_AnimationParam_Change(ui);
        return ;
    }
    switch (Page->type)
    {
    case UI_PAGE_TEXT:
        // 计算当前项名称的宽度
        ui->cursor.nowWide  = strlen(now_Item->itemName)*UI_FONT_WIDTH + 4;
        ui->cursor.targrtRow = next_item->y - UI_FONT_HIGHT;
        if (ui->cursor.targrtRow > (ui->textSpace*(UI_VER_RES/ui->textSpace) - ui->textSpace) || ui->cursor.targrtRow < 0)  // 防止光标溢出可视范围
        {
            if(abs(now_Item->id - next_item->id) == 1)ui->cursor.targrtRow = now_Item->y - UI_FONT_HIGHT;
        }
        break;
    case UI_PAGE_ICON:
        // 根据选项的id差值计算目标行位置，并限制在可视范围内
        ui->cursor.targrtColumn = next_item->x;
        if (ui->cursor.targrtColumn > (ui->imageSpace*(UI_HOR_RES/ui->imageSpace) - ui->imageSpace) || ui->cursor.targrtColumn < 0)  // 防止光标溢出可视范围
        {
            if(abs(now_Item->id - next_item->id) == 1)ui->cursor.targrtColumn = now_Item->x;
        }
        break;
    default:
        break;
    }
}

static void Draw_TextPage(ui_t *ui, ui_page_t *Page, ui_item_t *now_Item, ui_item_t *next_item)
{
    ui_item_t * temp_item = Page->item.head; // 从页面的头部开始遍历

    if(ui->nowItem->page.location != next_item->page.location)
    {
        for (uint16_t i = 0; i <= Page->length; i++)
        {
            temp_item->animationY = 0;
            temp_item = temp_item->nextItem;
        }
    }
    for (uint16_t i = 0; i <= Page->length; i++)
    {
        temp_item->animationY = (int16_t )UI_Animation((float )temp_item->y, (float )temp_item->animationY, &ui->animation.textPage_ani);
        if(temp_item->animationY >= -UI_FONT_HIGHT && temp_item->animationY <= UI_VER_RES + UI_FONT_HIGHT) //超出屏幕范围则不绘制
        {
            if(temp_item->itemType == UI_ITEM_DATA && temp_item->element != NULL)
            {
                char Data[20] = {0}; // 用于临时存储数据字符串
                Disp_SetClipWindow(UI_DATA_X0, UI_DATA_Y0, UI_DATA_X1, UI_DATA_Y1);
                // 格式化并绘制数据
                switch (temp_item->element->data->dataType)
                {
                case UI_DATA_INT:
                    snprintf(Data, sizeof(Data), "%d", *(int *)(temp_item->element->data->ptr));
                    break;
                case UI_DATA_FLOAT:
                    snprintf(Data, sizeof(Data), "%.2f", *(float *)(temp_item->element->data->ptr));
                    break;
                case UI_DATA_SWITCH:
                    Disp_DrawRFrame(UI_HOR_RES - 36, temp_item->animationY - UI_FONT_HIGHT, UI_FONT_HIGHT, UI_FONT_HIGHT, 2);
                    // 绘制开关状态
                    if(*(uint8_t *)temp_item->element->data->ptr == true)Disp_DrawRBox(UI_HOR_RES - 36 + 2, temp_item->animationY - UI_FONT_HIGHT + 2, UI_FONT_HIGHT - 4, UI_FONT_HIGHT - 4, 2);
                    break;
                case UI_DATA_STRING:
                    strncpy(Data, (char *)(temp_item->element->data->ptr), sizeof(Data));
                    break;
                default:
                    break;
                }
                Disp_DrawStr(UI_HOR_RES - 36, temp_item->animationY, Data);
            }
            Disp_SetClipWindow(UI_TITLE_X0, UI_TITLE_Y0, UI_TITLE_X1, UI_TITLE_Y1);

            #if ( UI_TITLE_ROLL == 1 )
            // 根据temp_item的滚动状态选择不同的操作
            switch (temp_item->rollState)
            {
            case UI_ITEM_ROLL_STOP: // 如果项目处于静止状态
                // 检查项目名称是否需要开始滚动
                if(strlen(temp_item->itemName) * UI_FONT_WIDTH > (UI_TITLE_X1 - UI_TITLE_X0))
                    temp_item->rollState = UI_ITEM_ROLL_FORWARD; // 如果名称宽度大于项目区域宽度，改变状态为向前滚动
                break;
            case UI_ITEM_ROLL_FORWARD: // 如果项目处于向前滚动状态
                temp_item->x --; // 向左移动项目
                // 检查是否需要改变滚动方向
                if((strlen(temp_item->itemName) * UI_FONT_WIDTH + temp_item->x) < (UI_TITLE_X1 - UI_TITLE_X0))
                    temp_item->rollState = UI_ITEM_ROLL_BACKWARD; // 如果项目移出左边界，改变状态为向后滚动
                break;
            case UI_ITEM_ROLL_BACKWARD: // 如果项目处于向后滚动状态
                temp_item->x ++; // 向右移动项目
                // 检查项目是否完全回到视图内
                if(temp_item->x > 0)
                    temp_item->rollState = UI_ITEM_ROLL_STOP; // 如果项目完全回到视图内，改变状态为向前滚动
                break;
            default: // 默认情况下不做任何操作
                break;
            }
            #endif

            Disp_DrawStr(temp_item->x, temp_item->animationY, temp_item->itemName); // 绘制项目名称
        }
        temp_item = temp_item->nextItem;
    }
    uint8_t color = 2;
    Disp_SetDrawColor(&color); // 设置特定的颜色，通常用于高亮显示
    // 根据目标位置和当前位置，以及PID算法计算并更新当前选项的位置和宽度
    ui->cursor.nowRow = (int )UI_Animation((float )ui->cursor.targrtRow, (float )ui->cursor.nowRow, &ui->animation.cursor_ani);
    ui->cursor.nowWide = (int )UI_Animation((float )ui->cursor.targrtWide, (float )ui->cursor.nowWide, &ui->animation.cursor_ani);
    // 绘制选中项的高亮边框
    Disp_DrawRBox(ui->headX + 1, ui->cursor.nowRow + 1, ui->cursor.nowWide, UI_FONT_HIGHT, 4);
    Disp_SetMaxClipWindow();
}

static void Draw_ImagePage(ui_t *ui, ui_page_t *Page, ui_item_t *nowItem, ui_item_t *next_item)
{
    static int16_t tital_x = 0;
    ui_item_t * temp_item = Page->item.head; // 从页面的头部开始遍历
    uint8_t color = 2;
    Draw_ImagePage_Optionbar(ui, nowItem, next_item);
    if(ui->nowItem->page.location != next_item->page.location)
    {
        for (uint16_t i = 0; i <= Page->length; i++)
        {
            temp_item->animationX = 0;
            temp_item = temp_item->nextItem;
        }
    }
    for (uint16_t i = 0; i <= Page->length; i++)
    {
        temp_item->animationX = (int16_t )UI_Animation((float )temp_item->x, (float )temp_item->animationX, &ui->animation.imagePage_ani);
        if(temp_item->animationX >= -UI_IMG_WIDTH && temp_item->animationX <= UI_HOR_RES + UI_IMG_WIDTH) //超出屏幕范围则不绘制
        {
            color = ui->bgColor^0x01;
            Disp_SetDrawColor(&color);
            Disp_DrawXBMP(temp_item->animationX, 12, UI_IMG_WIDTH, UI_IMG_HEIGHT, temp_item->logo);
            color = 2;
            Disp_SetDrawColor(&color);
            Disp_DrawRBox(temp_item->animationX, 12, UI_IMG_WIDTH, UI_IMG_HEIGHT, 4);
        }
        
        temp_item = temp_item->nextItem;
    }

    #if ( UI_TITLE_ROLL == 1 )
    // 根据temp_item的滚动状态选择不同的操作
    switch (next_item->rollState)
    {
    case UI_ITEM_ROLL_STOP: // 如果项目处于静止状态
        // 检查项目名称是否需要开始滚动
        if(strlen(next_item->itemName) * UI_FONT_WIDTH > UI_HOR_RES)
            next_item->rollState = UI_ITEM_ROLL_FORWARD; // 如果名称宽度大于项目区域宽度，改变状态为向前滚动
        else tital_x = 0;
        break;
    case UI_ITEM_ROLL_FORWARD: // 如果项目处于向前滚动状态
        tital_x --; // 向左移动项目
        // 检查是否需要改变滚动方向
        if((strlen(next_item->itemName) * UI_FONT_WIDTH + tital_x) < UI_HOR_RES)
            next_item->rollState = UI_ITEM_ROLL_BACKWARD; // 如果项目移出左边界，改变状态为向后滚动
        break;
    case UI_ITEM_ROLL_BACKWARD: // 如果项目处于向后滚动状态
        tital_x ++; // 向右移动项目
        // 检查项目是否完全回到视图内
        if(tital_x > 0)
            next_item->rollState = UI_ITEM_ROLL_STOP; // 如果项目完全回到视图内，改变状态为向前滚动
        break;
    default: // 默认情况下不做任何操作
        break;
    }
    #endif

    color = ui->bgColor^0x01;;
    Disp_SetDrawColor(&color); // 设置特定的颜色，通常用于高亮显示
    Disp_DrawStr(tital_x, UI_VER_RES - 2, next_item->itemName);
    // 根据目标位置和当前位置，以及PID算法计算并更新当前选项的位置和宽度
    ui->cursor.nowColumn = (int )UI_Animation((float )ui->cursor.targrtColumn, (float )ui->cursor.nowColumn, &ui->animation.cursor_ani);
    // 绘制选中项的高亮边框
    Disp_DrawBox(ui->cursor.nowColumn, UI_VER_RES - 17, UI_IMG_WIDTH, 2);
}

/**
 * 绘制菜单界面
 * 该函数负责在 OLED 屏幕上绘制菜单界面，包括计算各项的位置、绘制背景、选项及其高亮显示。
 * 根据不同的菜单状态（如页面移动、选项切换），动态调整选项的显示位置，实现平滑的动画效果。
 * @param pos 当前页面位置
 * @param Page 当前页面结构体
 * @param LineSpacing 行间距
 * @param nowItem 当前选中项
 * @param next_item 下一个将要选中的项
 */
static void Draw_UI(ui_t *ui, ui_page_t *Page, ui_item_t *nowItem,ui_item_t *next_item)
{
    Disp_SetFont(UI_FONT);
    Disp_ClearBuffer(); // 清除屏幕缓冲区

    // 计算页面状态
    if(ui->menuState == UI_PAGE_RUNING)
    {
        Calculate_PageState(ui, Page, nowItem, next_item);
    }

    // 计算下一个将要选中项的名称宽度
    if(strlen(next_item->itemName)*UI_FONT_WIDTH > (UI_TITLE_X1 - UI_TITLE_X0))
    ui->cursor.targrtWide = UI_TITLE_X1 - UI_TITLE_X0;
    else ui->cursor.targrtWide = strlen(next_item->itemName)*UI_FONT_WIDTH;
    uint8_t color = ui->bgColor;
    // 开始绘制菜单界面
    Disp_SetDrawColor(&color); // 设置背景颜色
    Disp_DrawBox(0, 0, 128, 64); // 绘制屏幕背景框
    color = color^0x01;
    Disp_SetDrawColor(&color); // 设置绘制颜色为高亮或低亮
    Calculate_Coordinate(ui, Page, nowItem, next_item); // 绘制前计算最终坐标
    // 初始化或更新动画参数及页面状态
    if(ui->menuState == UI_PAGE_RUNING)
    {
        Calculate_Cursor(ui, Page, nowItem, next_item);
    }

    if(Page->type == UI_PAGE_TEXT)
    {
        Draw_TextPage_Optionbar(ui, nowItem, next_item); // 绘制选项及其位置
        Draw_TextPage(ui, Page, nowItem, next_item);
    }
    else if(Page->type == UI_PAGE_ICON)
    {
        Draw_ImagePage_Optionbar(ui, nowItem, next_item); // 绘制选项及其位置
        Draw_ImagePage(ui, Page, nowItem, next_item);
    }

    Disp_SendBuffer(); // 将缓冲区的内容发送到OLED屏幕显示

    // 更新菜单状态为绘制中
    Change_UIState(ui, UI_PAGE_DRAWING);
}

void Create_element(ui_item_t *item, ui_element_t *element)
{
    if(item == NULL || element == NULL)return ;

    item->element = element;
}

/**
 * @brief 根据菜单方向运行处理菜单逻辑
 * 
 * @param Dir 菜单操作方向，包括上、下、进入等操作
 */
static void Process_UI_Run(ui_t *ui, UI_ACTION Action)
{
    uint8_t disapper = 0;
    switch (ui->menuState) // 根据当前菜单状态进行不同的操作
    {
        case UI_PAGE_RUNING:
            switch (Action) // 根据操作方向更新菜单项
            {
                case UI_ACTION_UP:
                    // 向上移动菜单项，确保当前项和上一项非空
                    if (ui->nowItem != NULL && ui->nowItem->lastItem != NULL) 
                    {
                        Draw_UI(ui, ui->nowItem->page.location, ui->nowItem, ui->nowItem->lastItem);
                        ui->oldItem = ui->nowItem;
                        ui->nowItem = ui->nowItem->lastItem;
                    }
                    break;
                case UI_ACTION_DOWN:
                    // 向下移动菜单项，确保当前项和下一项非空
                    if (ui->nowItem != NULL && ui->nowItem->nextItem != NULL) 
                    {
                        Draw_UI(ui, ui->nowItem->page.location, ui->nowItem, ui->nowItem->nextItem);
                        ui->oldItem = ui->nowItem;
                        ui->nowItem = ui->nowItem->nextItem;
                    }
                    break;
                case UI_ACTION_ENTER:
                    // 当前项非空且为父项时，进入下一级菜单
                    if(ui->nowItem != NULL && ui->nowItem->itemType == UI_ITEM_PARENTS)
                    {
                        // 避免重复状态改变
                        if(ui->action != UI_ACTION_ENTER) Change_UIState(ui, UI_PAGE_RUNING);

                        for (size_t i = 0; i < 8; i++) // 执行UI淡出操作
                        {
                            disapper = UI_Disapper(ui ,disapper);
                        }
                        
                        // 如果存在跳转页面且不为空，则绘制跳转页面并更新当前项
                        if(ui->nowItem->page.jumpPage != NULL && ui->nowItem->page.jumpPage->item.head != NULL) 
                        {
                            Optionbar_Init(ui);
                            Draw_UI(ui, ui->nowItem->page.jumpPage, ui->nowItem, ui->nowItem->page.jumpPage->item.head);
                            ui->nowItem->page.location->item.lastJumpItem = ui->nowItem;
                            ui->oldItem = ui->nowItem;
                            ui->nowItem = ui->nowItem->page.jumpPage->item.head;
                        }
                    }
                    else if (ui->nowItem != NULL && ui->nowItem->itemType == UI_ITEM_RETURN)
                    {
                        // 避免重复状态改变
                        if(ui->action != UI_ACTION_ENTER) Change_UIState(ui, UI_PAGE_RUNING);

                        for (size_t i = 0; i < 8; i++) // 执行UI淡出操作
                        {
                            disapper = UI_Disapper(ui ,disapper);
                        }
                        
                        // 如果存在跳转页面，则绘制跳转页面并更新当前项
                        if(ui->nowItem->page.jumpPage != NULL) 
                        {
                            Draw_UI(ui, ui->nowItem->page.jumpPage->item.lastJumpItem->page.location, ui->nowItem, ui->nowItem->page.jumpPage->item.lastJumpItem);
                            ui->oldItem = ui->nowItem;
                            ui->nowItem = ui->nowItem->page.jumpPage->item.lastJumpItem;
                        }
                    }
                    else // 如果当前项为空或非父项，则进入应用绘制状态
                    {
                        UI_Disapper(ui, 1);
                        Change_UIState(ui, UI_ITEM_DRAWING);
                    }
                    break;
                default:
                    Draw_UI(ui, ui->nowItem->page.location, ui->nowItem, ui->nowItem);
                    break;
            }
            break;
        case UI_ITEM_EXIT:
            // 退出应用时的初始化操作，并返回菜单运行状态
            Dialog_AnimationParam_Init(ui);
            Scrollbar_Init(ui);
            Change_UIState(ui, UI_PAGE_RUNING);
            for (size_t i = 0; i < 8; i++)
            {
                disapper = UI_Disapper(ui, disapper); // 执行UI淡出操作
            }
            if(ui->nowItem != NULL) // 确保now_item非空
            {
                Draw_UI(ui, ui->nowItem->page.location, ui->nowItem, ui->nowItem);
            }
            break;
        case UI_PAGE_DRAWING:
            // 如果当前正在绘制菜单，则根据方向进行状态更新和菜单重绘
            if(ui->nowItem != NULL && ui->oldItem != NULL)
            {
                Draw_UI(ui, ui->nowItem->page.location, ui->oldItem, ui->nowItem);
                if (Action != UI_ACTION_NONE)
                {
                    Change_UIState(ui, UI_PAGE_RUNING);
                    Process_UI_Run(ui, Action);
                }
            }
            break;
        default:
            break;
    }
}

/**
 * @brief 处理应用程序的运行状态。
 * 对给定的项目(item)根据其类型(UI_ITEM_TYPE)和当前的菜单状态(Direction)执行相应的操作。
 * @param item 指向要处理的项目的指针。
 * @param Direction 当前菜单的方向或状态。
 */
static void Process_App_Run(ui_t *ui, ui_item_t *item, UI_ACTION Action)
{
    if (item == NULL) return; // 检查空指针，避免未定义行为

    ui->action = Action; // 设置项目的状态为当前菜单状态

    switch (item->itemType) // 根据项目类型执行不同的操作
    {
    case UI_ITEM_DATA:
        if(item->element != NULL && item->element->data != NULL)
        {
            if(item->element->data->actionType == UI_DATA_ACTION_RO)
            {
                Change_UIState(ui, UI_ITEM_EXIT); // 如果项目状态为进入菜单，则改变菜单状态为函数退出
                break;
            }
            else
            {
                switch (item->element->data->dataType)
                {
                case UI_DATA_INT:
                case UI_DATA_FLOAT:
                    if (item->itemFunction == NULL)ParameterSetting_Widget(ui);
                    else (item->itemFunction)(ui); // 执行项目的函数
                    if(ui->action == UI_ACTION_ENTER)
                    {
                        if(ui->nowItem->element->data->functionType == UI_DATA_FUNCTION_EXIT_EXECUTE)
                        {
                            if(ui->nowItem->element->data->function != NULL)ui->nowItem->element->data->function(ui);
                            #if ( UI_USE_FREERTOS == 1 )
                            if(ui->nowItem->element->data->dataRootTask != NULL)vTaskResume(*ui->nowItem->element->data->dataRootTask);
                            #endif
                        }
                        Change_UIState(ui, UI_ITEM_EXIT); // 如果项目状态为进入菜单，则改变菜单状态为函数退出
                    }
                    break;
                case UI_DATA_SWITCH:
                    Switch_Widget(ui);
                    Change_UIState(ui, UI_ITEM_EXIT); // 改变菜单状态为函数退出
                    break;
                default:
                    UI_LOG("Unknow data type\n");
                    break;
                }
            }
            break;
        }
        Change_UIState(ui, UI_ITEM_EXIT);
        break;
    case UI_ITEM_LOOP_FUNCTION:
        if (item->itemFunction != NULL)(item->itemFunction)(ui); // 执行项目的函数
        if(ui->action == UI_ACTION_ENTER)Change_UIState(ui, UI_ITEM_EXIT); // 如果项目状态为进入菜单，则改变菜单状态为函数退出
        break;
    case UI_ITEM_WAVE:
        if (item->itemFunction == NULL)Wave_Widget(ui);
        else (item->itemFunction)(ui); // 执行项目的函数
        if(ui->action == UI_ACTION_ENTER)Change_UIState(ui, UI_ITEM_EXIT); // 如果项目状态为进入菜单，则改变菜单状态为函数退出
        break;
    case UI_ITEM_WORD:
        if (item->itemFunction == NULL)Text_Widget(ui);
        else (item->itemFunction)(ui);
        if(ui->action == UI_ACTION_ENTER)Change_UIState(ui, UI_ITEM_EXIT); // 如果项目状态为进入菜单，则改变菜单状态为函数退出
        break;
    case UI_ITEM_ONCE_FUNCTION:
        if (item->itemFunction != NULL && item->functionState == false)
        {
            (item->itemFunction)(ui); // 如果项目有函数，则执行该函数
            item->functionState = true;
        }
        item->functionState = false;
        #if (UI_ONCEFUNCTION_TIP == 0)
        Change_UIState(ui, UI_ITEM_EXIT); // 改变菜单状态为函数退出
        #endif
        #if (UI_ONCEFUNCTION_TIP == 1)
        // 执行完成后，弹窗提醒
        if (Notifications(ui, 4, 12, UI_HOR_RES - 8, UI_VER_RES - 32))
        {
            Disp_SendBuffer();
        }
        if(ui->action != UI_ACTION_NONE)
        {
            item->functionState = false;
            Change_UIState(ui, UI_ITEM_EXIT); // 改变菜单状态为函数退出
        }
        #endif
        break;
    default:
        break; // 对未知类型不执行任何操作
    }
}

/**
 * 菜单任务处理函数
 * 该函数负责根据当前按钮扫描结果更新菜单状态，并进行相应的绘制或处理操作。
 * 无参数
 * 无返回值
 */
void ui_loop(ui_t *ui)
{
    UI_ACTION Action = indevScan(); // 扫描按钮方向，确定菜单操作方向
    if (ui->menuState == UI_PAGE_INIT && Action != UI_ACTION_NONE)
    {
        ui->menuState = UI_PAGE_RUNING;
        // 初始化状态下，非空检查now_item并绘制当前菜单项
        if (ui->nowItem != NULL)
        {
            Draw_UI(ui, ui->nowItem->page.location, ui->nowItem, ui->nowItem);
        }
        else
        {
            UI_LOG("ui->nowItem is NULL\n"); // 打印错误信息，now_item为空
        }
    }
    else
    {
        switch (ui->menuState)
        {
            case UI_PAGE_INIT:break;
            case UI_ITEM_RUNING:
            case UI_ITEM_DRAWING:
                // 在这两个状态下，处理应用程序运行逻辑
                Process_App_Run(ui, ui->nowItem, Action);
                if (ui->menuState == UI_ITEM_DRAWING)
                {
                    break; // 在绘制状态下，终止进一步流程执行
                }
            case UI_PAGE_RUNING:
            case UI_ITEM_EXIT:
            case UI_PAGE_DRAWING:
                // 处理菜单运行、应用退出和菜单绘制状态
                Process_UI_Run(ui, Action);
                break;

            default:
                break;
        }
    }
}

static void AnimationParam_Init(ui_animation_t *Ani)
{
    Ani->optionbar_ani.kp = 0.35f;
    Ani->optionbar_ani.ki = 0.0f;
    Ani->optionbar_ani.kd = 0.03f;

    Ani->cursor_ani.kp = 0.4f;
    Ani->cursor_ani.ki = 0.1f;
    Ani->cursor_ani.kd = 0.1f;

    Ani->imagePage_ani.kp = 0.35f;
    Ani->imagePage_ani.ki = 0.0f;
    Ani->imagePage_ani.kd = 0.01f;

    Ani->textPage_ani.kp = 0.35f;
    Ani->textPage_ani.ki = 0.0f;
    Ani->textPage_ani.kd = 0.1f;

    Ani->scrollbar_ani.kp = 0.35f;
    Ani->scrollbar_ani.ki = 0.0f;
    Ani->scrollbar_ani.kd = 0.03f;

    Ani->optionbarPos_ani.kp = 0.30f;
    Ani->optionbarPos_ani.ki = 0.0f;
    Ani->optionbarPos_ani.kd = 0.0f;
}

void Create_UI(ui_t *ui, ui_item_t *item)
{
    Create_MenuTree(ui);
    Create_Parameter(ui);
    Create_Text(ui);
    ui->textSpace = UI_TEXT_SPACE;
    ui->imageSpace = UI_IMAGE_SPACE;
    ui->headX = UI_PAGE_INIT_X;
    ui->headY = UI_PAGE_INIT_Y;
    ui->nowItem = item;
    ui->oldItem = item;
    ui->menuState = UI_PAGE_INIT;
    ui->action = UI_ACTION_NONE;
    ui->bgColor = 0;
    AnimationParam_Init(&ui->animation);
}
