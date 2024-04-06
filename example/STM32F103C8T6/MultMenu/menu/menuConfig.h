#ifndef _MENUCONFIG_H_
#define _MENUCONFIG_H_

#include "stm32f10x.h"
#include "u8g2.h"
#include "stdbool.h"

#define HOR_RES     128
#define VER_RES     64

//菜单字体
#define MENU_FONT   u8g2_font_profont12_mf
//字体尺寸
#define Font_Size   12
//起始Y坐标
#define FirstLine   Font_Size
//起始X坐标
#define FirstPos    0
//最大可见项目数
#define MaxVisible_Number  4
//最大Y坐标
#define LINE_MAX    Font_Size*MaxVisible_Number
//最小Y坐标
#define LINE_MIN    Font_Size 

typedef struct pid_error
{
    int kp;
    int ki;
    int kd;
    float error;
    float sum_srror;
    float last_error;
}Pid_Error;

//菜单状态枚举
typedef enum menu_state
{
    MENU_RUN,
    APP_RUN,
    APP_BREAK,
    MENU_MOVE,
    CURSOR_STATIC,

    MENU_UP,
    MENU_DOWN,
    MENU_ENTER,
    MENU_NONE
}Menu_State;

typedef enum item_type
{
    HEAD,
    PARENTS,
    LOOP_FUNCTION,
    ONCE_FUNCTION,
    SWITCH,
    DATA
}Item_Type;

typedef struct Page *xpPage;
typedef struct Item *xpItem;
typedef void (*ItemFunction)(xpItem);
typedef struct Page
{
    const char *pageName;
    uint8_t length;
    uint8_t id;
    xpItem parentITem;
    xpItem itemHead;
    xpItem itemTail;
} xPage;

typedef struct Item
{
    const char *ItemName;
    Item_Type ItemType;
    bool SwitchState;
    int *data;
    uint8_t id;
    xpPage location, JumpPage;
    xpItem lastiTem, nextiTem;
    ItemFunction itemFunction;
    Menu_State state;
} xItem;

#endif