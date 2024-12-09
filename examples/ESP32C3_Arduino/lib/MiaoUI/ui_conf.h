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
#ifndef _MENUCONFIG_H_
#define _MENUCONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "fonts/fonts.h"

// 屏幕分辨率定义
#define UI_HOR_RES     128 // 水平分辨率
#define UI_VER_RES     64 // 垂直分辨率
// 菜单字体定义
#define UI_FONT   font_menu_main_h12w6
// 字体尺寸定义
#define UI_FONT_HIGHT   12 // 字体高度
// 字体宽度
#define UI_FONT_WIDTH  6
// 文本间距
#define UI_TEXT_SPACE  16
// 起始Y坐标，基于字体大小设定的第一行位置
#define UI_PAGE_INIT_Y   UI_FONT_HIGHT
// 起始X坐标
#define UI_PAGE_INIT_X    0
// 图片大小
#define UI_IMG_WIDTH   30
#define UI_IMG_HEIGHT  30
// 图片间距
#define UI_IMAGE_SPACE   40
// 文本页面标题名称显示区域
#define UI_TITLE_X0     0
#define UI_TITLE_Y0     0 
#define UI_TITLE_X1     (UI_HOR_RES - 42)
#define UI_TITLE_Y1     UI_VER_RES
// 数据显示区域
#define UI_DATA_X0     (UI_HOR_RES - 36)
#define UI_DATA_Y0     0 
#define UI_DATA_X1     (UI_HOR_RES - 12)
#define UI_DATA_Y1     UI_VER_RES
// UI日志输出定义
#define UI_LOG  printf
// 为1时单次任务(UI_ITEM_ONCE_FUNCTION)运行完毕后会弹窗提示
#define UI_ONCEFUNCTION_TIP   0
// 对话框动画持续时间
#define UI_DIALOG_SCALE_ANI_TOTAL_TIME 8
// 为1时标题名称过长时自动滚动
#define UI_TITLE_ROLL  1
// 为1时使用FreeRTOS
#define UI_USE_FREERTOS 0

#if ( UI_USE_FREERTOS == 1 )
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#endif

typedef struct ui_page_t *ui_page_pt;
typedef struct ui_item_t *ui_item_pt;
typedef struct ui_t *ui_pt;
typedef void (*ui_item_function)(ui_pt);

#define ui_data_function ui_item_function

typedef enum
{
    UI_DATA_FUNCTION_EXIT_EXECUTE,   // 退出执行
    UI_DATA_FUNCTION_STEP_EXECUTE    // 步进执行
} UI_DATA_FUNCTION_TYPE;

typedef enum
{
    UI_DATA_INT,      // 整型数据
    UI_DATA_FLOAT,     // 浮点型数据
    UI_DATA_SWITCH,    // 开关类型数据
    UI_DATA_STRING     // 字符串类型数据
} UI_DATA_TYPE;

typedef enum
{
    UI_DATA_ACTION_RO,     // 只读
    UI_DATA_ACTION_RW     // 读写
} UI_DATA_ACTION_TYPE;

typedef struct {
    const char *name;
    void *ptr; // 指向整型数据的指针
    ui_data_function function;
    UI_DATA_FUNCTION_TYPE functionType;
    UI_DATA_TYPE dataType;
    UI_DATA_ACTION_TYPE actionType;
    #if ( UI_USE_FREERTOS == 1 )
    TaskHandle_t *dataRootTask;
    QueueHandle_t *dataRootQueue;
    SemaphoreHandle_t *dataRootMutex;
    #endif
    int max;
    int min;
    float step;
} ui_data_t;

typedef struct {
    const char *ptr;
    const uint8_t *font;
    int fontHight;
    int fontWidth;
} ui_text_t;

typedef struct {
    ui_data_t *data;
    ui_text_t *text;
} ui_element_t;

/**
 * ui_animation_param_t 结构体定义
 * 用于存储PID控制器的误差及调整参数
 */
typedef struct
{
    float kp;         // 比例增益
    float ki;         // 积分增益
    float kd;         // 微分增益
    float error;    // 当前误差
    float sum_error; // 积累的误差
    float last_error; // 上一次的误差
}ui_animation_param_t;
/**
 * @brief 
 * 
 */
typedef struct
{
    ui_animation_param_t optionbar_ani;
    ui_animation_param_t optionbarPos_ani;
    ui_animation_param_t cursor_ani;
    ui_animation_param_t textPage_ani;
    ui_animation_param_t imagePage_ani;
    ui_animation_param_t scrollbar_ani;
}ui_animation_t;

// 菜单状态枚举: 定义了菜单及应用程序的不同运行状态
typedef enum
{
    UI_PAGE_INIT,       // 菜单初始化状态
    UI_PAGE_DRAWING,    // 菜单绘制状态
    UI_PAGE_RUNING,        // 菜单运行状态
    UI_ITEM_RUNING,         // 应用程序运行状态
    UI_ITEM_DRAWING,     // 应用程序绘制状态
    UI_ITEM_EXIT         // 应用程序退出状态
} UI_STATE;

// 页面状态枚举
// 用于表示页面的两种状态：移动和静止
typedef enum
{
    UI_PAGE_MOVING,    // 页面正在移动
    UI_PAGE_STATIC     // 页面处于静止状态
}UI_PAGE_STATE;

// 菜单运动方向枚举
// 这个枚举定义了菜单系统中可能的方向和操作，包括向上、向下、进入和退出等操作。
typedef enum
{
    UI_ACTION_NONE,    // 无操作
    UI_ACTION_UP,      // 向上
    UI_ACTION_DOWN,    // 向下
    UI_ACTION_ENTER   // 进入或选择
} UI_ACTION;

// 菜单项目类型枚举
typedef enum
{
    // 父菜单项: ;代表菜单中的顶级项或父级项，通常不直接与用户交互，而是作为其他菜单项的容器。
    UI_ITEM_PARENTS,        
    // 循环功能项: *代表一种循环执行的功能，在菜单系统中用于循环播放、轮询等操作。
    UI_ITEM_LOOP_FUNCTION,      
    // 一次性功能项: &代表仅执行一次的功能，执行后即被标记为完成，不再重复执行。
    UI_ITEM_ONCE_FUNCTION,      
    // 数据项: ~代表菜单中用于显示或设置数据的项，可以是数值、文本等各种形式的数据。
    UI_ITEM_DATA,               
    // 文本类型: `代表菜单中的文本项，用于显示提示信息或提示用户操作。
    UI_ITEM_WORD,             
    // 波形类型: ^代表菜单中的波形显示项，用于显示波形数据。
    UI_ITEM_WAVE,               
    // 返回键: <代表菜单中的返回键，用于返回上一级菜单。
    UI_ITEM_RETURN              
} UI_ITEM_TYPE;

// 页面类型枚举
typedef enum
{
    // 文本类型
    UI_PAGE_TEXT,
    // 图像类型
    UI_PAGE_ICON
} UI_PAGE_TYPE;


#if ( UI_TITLE_ROLL == 1 )
typedef enum
{
    // 停止滚动
    UI_ITEM_ROLL_STOP,
    // 向前滚动
    UI_ITEM_ROLL_FORWARD,
    // 向后滚动
    UI_ITEM_ROLL_BACKWARD
} UI_ITEM_ROLL_STATE;
#endif

// 光标运动参数
typedef struct
{
    // 当前宽度
    int nowWide;
    // 当前行坐标
    int nowRow;
    // 当前列坐标
    int nowColumn;
    // 目标行坐标
    int targrtRow;
    // 目标列坐标
    int targrtColumn;
    // 目标宽度
    int targrtWide;
} ui_cursor_param_t;

// 对话框运动参数
typedef struct
{
    // 对话框初始宽度
    uint16_t nowWide;
    // 对话框初始高度
    uint16_t nowHigh;
    // 对话框运动时间(次数)
    uint16_t times;
} ui_dialog_param_t;

// 滚动条运动参数
typedef struct
{
    // 滚动条当前长度
    uint16_t nowLenght;
    // 滚动条目标长度
    uint16_t targetLenght;
    // 位置
    uint16_t position;
} ui_optionbar_param_t;

// 滚动条
typedef struct
{
    ui_optionbar_param_t optionbar;
} ui_optionbar_t;

typedef struct
{
    uint16_t value;
} ui_scrollbar_t;

/**
 * 定义一个名为Page的结构体类型
 * 用于表示页面信息
 */
typedef struct ui_page_t {
    const char *pageName;      // 页面名称，使用指针存储
    UI_PAGE_TYPE type;         // 页面类型
    UI_PAGE_STATE pageState;    // 页面的状态
    // 使用内联函数封装成员变量，以提供更高的数据封装性和保护性
    struct {
        ui_item_pt parent;         // 父级项
        ui_item_pt head;           // 头部项
        ui_item_pt tail;           // 尾部项
        ui_item_pt lastJumpItem;
    } item;
    int length;            // 页面长度
    int jumpX;
    int jumpY;
    int cursorLastColumn;
    int cursorLastRow;
    int cursorLastWide;
} ui_page_t;

// 定义一个名为Item的结构体类型
typedef struct ui_item_t {
    const char *itemName; // 结构体成员变量：项目名称，使用const char*类型
    UI_ITEM_TYPE itemType; // 结构体成员变量：项目类型，自定义的Item_Type类型
    #if ( UI_TITLE_ROLL == 1 )
    UI_ITEM_ROLL_STATE rollState;
    #endif
    ui_element_t *element;
    int id; // 结构体成员变量：项目ID，使用uint8_t类型
    // 使用内联函数封装page结构体，以保护成员变量
    struct {
        ui_page_pt location; // 页面位置
        ui_page_pt jumpPage; // 跳转页面
    } page;
    ui_item_pt lastItem, nextItem; // 上一个项目和下一个项目的指针
    ui_item_function itemFunction; // 函数指针，指向一个接受xpItem类型参数的函数
    int16_t x;
    int16_t y;
    int16_t animationX;
    int16_t animationY;
    uint8_t functionState;
    const uint8_t *logo;
} ui_item_t;

/**
 * xMenu结构体定义
 * 用于表示一个菜单的相关信息
 */
typedef struct ui_t {
    ui_item_pt nowItem;          // 当前选中的item
    ui_item_pt oldItem;          // 上一个选中的item
    ui_item_pt lastJumpItem;
    uint8_t bgColor;          // 菜单的背景颜色
    int textSpace;           // 文本间距
    int imageSpace;          // 图片间距
    int headX;
    int headY;
    UI_STATE menuState;     // 菜单的状态
    UI_ACTION action;
    ui_animation_t animation;
    ui_cursor_param_t cursor;
    ui_dialog_param_t dialog;
    ui_optionbar_param_t optionbar;
    ui_scrollbar_t scrollbar;
} ui_t;

void Create_Parameter(ui_t *ui);
void Create_Text(ui_t *ui);
void Create_MenuTree(ui_t *ui);
void MiaoUi_Setup(ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif
