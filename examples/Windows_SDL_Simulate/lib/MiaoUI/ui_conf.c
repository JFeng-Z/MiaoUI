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
#include "ui_conf.h"
#include "lib/MiaoUI/core/ui.h"
#include "lib/MiaoUI/display/dispDriver.h"
#include "lib/MiaoUI/images/image.h"
#include "lib/MiaoUI/widget/custom.h"
#include "lib/MiaoUI/version.h"

/*Page*/
ui_page_t Home_Page, System_Page, MPUTask_Page;
/*item */
ui_item_t HomeHead_Item, SystemHead_Item, System_Item, Image_Item, Github_Item, Bilibili_Item, Version_Item, MPUTask_Item, Wave_Item;
ui_item_t MPUTaskHead_Item, MPUTaskLvel_Item, MPUTaskState_Item, SystemHeap_Item, Pitch_Item, Roll_Item, Yaw_Item;
ui_item_t Contrast_Item, Power_Item, MenuColor_Item, CursorAni_Item, Test_Item;

/**
 * 在此建立所需显示或更改的数据
 * 无参数
 * 无返回值
 */
void Create_Parameter(ui_t *ui)
{
    static int Contrast = 255;
    static ui_data_t Contrast_data;
    Contrast_data.name = "Contrast";
    Contrast_data.ptr = &Contrast;
    Contrast_data.function = Disp_SetContrast;
    Contrast_data.functionType = UI_DATA_FUNCTION_STEP_EXECUTE;
    Contrast_data.dataType = UI_DATA_INT;
    Contrast_data.actionType = UI_DATA_ACTION_RW;
    Contrast_data.max = 255;
    Contrast_data.min = 0;
    Contrast_data.step = 5;
    static ui_element_t Contrast_element;
    Contrast_element.data = &Contrast_data;
    Create_element(&Contrast_Item, &Contrast_element);

    static uint8_t power_off = false;
    static ui_data_t Power_switch_data;
    Power_switch_data.ptr = &power_off;
    Power_switch_data.function = Disp_SetPowerSave;
    Power_switch_data.dataType = UI_DATA_SWITCH;
    Power_switch_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t Power_element;
    Power_element.data = &Power_switch_data;
    Create_element(&Power_Item, &Power_element);

    #if ( UI_USE_FREERTOS == 1 )
    extern QueueHandle_t WaveTest_Queue;
    extern TaskHandle_t WaveTestTask_Handle;
    #endif
    extern int Wave_TestData;
    static ui_data_t Wave_data;
    Wave_data.name = "Wave";
    Wave_data.ptr = &Wave_TestData;
    Wave_data.dataType = UI_DATA_INT;
    Wave_data.max = 600;
    Wave_data.min = 0;
    #if ( UI_USE_FREERTOS == 1 )
    Wave_data.dataRootTask = &WaveTestTask_Handle;
    Wave_data.dataRootQueue = &WaveTest_Queue;
    #endif
    static ui_element_t Wave_element;
    Wave_element.data = &Wave_data;
    Create_element(&Wave_Item, &Wave_element);

    #if ( UI_USE_FREERTOS == 1 )
    extern TaskHandle_t MPU6050UpdateTask_Handle;
    static uint8_t PrintTask_State = true;
    static ui_data_t PrintTask_switch_data;
    PrintTask_switch_data.ptr = &PrintTask_State;
    PrintTask_switch_data.dataType = UI_DATA_SWITCH;
    PrintTask_switch_data.actionType = UI_DATA_ACTION_RW;
    PrintTask_switch_data.dataRootTask = &MPU6050UpdateTask_Handle;
    static ui_element_t PrintTask_element;
    PrintTask_element.data = &PrintTask_switch_data;
    Create_element(&MPUTaskState_Item, &PrintTask_element);

    extern SemaphoreHandle_t MPU6050Update_Mutex;
    static int PrintTask_Levl = 1;
    static ui_data_t PrintTask_Levl_data;
    PrintTask_Levl_data.actionType = UI_DATA_ACTION_RW;
    PrintTask_Levl_data.dataType = UI_DATA_INT;
    PrintTask_Levl_data.name = "PrintTask_Levl";
    PrintTask_Levl_data.ptr = &PrintTask_Levl;
    PrintTask_Levl_data.max = 10;
    PrintTask_Levl_data.min = 1;
    PrintTask_Levl_data.step = 1;
    PrintTask_Levl_data.functionType = UI_DATA_FUNCTION_EXIT_EXECUTE;
    PrintTask_Levl_data.function = TaskLvel_Setting;
    PrintTask_Levl_data.dataRootTask = &MPU6050UpdateTask_Handle;
    PrintTask_Levl_data.dataRootMutex = &MPU6050Update_Mutex;
    static ui_element_t PrintTask_Levl_element;
    PrintTask_Levl_element.data = &PrintTask_Levl_data;
    Create_element(&MPUTaskLvel_Item, &PrintTask_Levl_element);

    extern char FreeHeap[20];
    static ui_data_t SystemHeap_data;
    SystemHeap_data.name = "FreeHeap";
    SystemHeap_data.ptr = FreeHeap;
    SystemHeap_data.dataType = UI_DATA_STRING;
    SystemHeap_data.actionType = UI_DATA_ACTION_RO;
    static ui_element_t SystemHeap_element;
    SystemHeap_element.data = &SystemHeap_data;
    Create_element(&SystemHeap_Item, &SystemHeap_element);
    #endif

    static ui_data_t MenuColor_data;
    MenuColor_data.name = "MenuColor";
    MenuColor_data.ptr = &ui->bgColor;
    MenuColor_data.dataType = UI_DATA_SWITCH;
    MenuColor_data.actionType = UI_DATA_ACTION_RW;
    static ui_element_t MenuColor_element;
    MenuColor_element.data = &MenuColor_data;
    Create_element(&MenuColor_Item, &MenuColor_element);

    static ui_data_t CursorAni_data;
    CursorAni_data.name = "CursorAni";
    CursorAni_data.ptr = &ui->animation.cursor_ani.kp;
    CursorAni_data.dataType = UI_DATA_FLOAT;
    CursorAni_data.actionType = UI_DATA_ACTION_RW;
    CursorAni_data.min = 0;
    CursorAni_data.max = 10;
    CursorAni_data.step = 0.1;
    static ui_element_t CursorAni_element;
    CursorAni_element.data = &CursorAni_data;
    Create_element(&CursorAni_Item, &CursorAni_element);

    float Pitch, Roll, Yaw;
    static ui_data_t Pitch_data;
    Pitch_data.name = "Pitch";
    Pitch_data.ptr = &Pitch;
    Pitch_data.dataType = UI_DATA_FLOAT;
    Pitch_data.actionType = UI_DATA_ACTION_RO;
    Pitch_data.max = 360;
    Pitch_data.min = -360;
    static ui_element_t Pitch_element;
    Pitch_element.data = &Pitch_data;
    Create_element(&Pitch_Item, &Pitch_element);

    static ui_data_t Roll_data;
    Roll_data.name = "Roll";
    Roll_data.ptr = &Roll;
    Roll_data.dataType = UI_DATA_FLOAT;
    Roll_data.actionType = UI_DATA_ACTION_RO;
    Roll_data.max = 360;
    Roll_data.min = -360;
    static ui_element_t Roll_element;
    Roll_element.data = &Roll_data;
    Create_element(&Roll_Item, &Roll_element);

    static ui_data_t Yaw_data;
    Yaw_data.name = "Yaw";
    Yaw_data.ptr = &Yaw;
    Yaw_data.dataType = UI_DATA_FLOAT;
    Yaw_data.actionType = UI_DATA_ACTION_RO;
    Yaw_data.max = 360;
    Yaw_data.min = -360;
    static ui_element_t Yaw_element;
    Yaw_element.data = &Yaw_data;
    Create_element(&Yaw_Item, &Yaw_element);
}

/**
 * 在此建立所需显示或更改的文本
 * 无参数
 * 无返回值
 */
void Create_Text(ui_t *ui)
{
    static ui_text_t github_text;
    github_text.font = UI_FONT;
    github_text.fontHight = UI_FONT_HIGHT;
    github_text.fontWidth = UI_FONT_WIDTH;
    github_text.ptr = VERSION_PROJECT_LINK;
    static ui_element_t github_element;
    github_element.text = &github_text;
    Create_element(&Github_Item, &github_element);

    static ui_text_t bilibili_text;
    bilibili_text.font = UI_FONT;
    bilibili_text.fontHight = UI_FONT_HIGHT;
    bilibili_text.fontWidth = UI_FONT_WIDTH;
    bilibili_text.ptr = "Could you trouble to give me a star? Thank you! Thank you! Thank you!";
    static ui_element_t bilibili_element;
    bilibili_element.text = &bilibili_text;
    Create_element(&Bilibili_Item, &bilibili_element);
}

/*
 * 菜单构建函数
 * 该函数不接受参数，也不返回任何值。
 * 功能：静态地构建一个菜单系统。
 */
void Create_MenuTree(ui_t *ui)
{
    AddPage("[HomePage]", &Home_Page, UI_PAGE_ICON);
        AddItem("[HomePage]", UI_ITEM_ONCE_FUNCTION, logo_allArray[0], &HomeHead_Item, &Home_Page, NULL, Draw_Home);
        AddItem(" +System", UI_ITEM_PARENTS, logo_allArray[1], &System_Item, &Home_Page, &System_Page, NULL);
            AddPage("[System]", &System_Page, UI_PAGE_TEXT);
                AddItem("[System]", UI_ITEM_RETURN, NULL, &SystemHead_Item, &System_Page, &Home_Page, NULL);
                AddItem(" -Contrast", UI_ITEM_DATA, NULL, &Contrast_Item, &System_Page, NULL, NULL);
                AddItem(" -Power off", UI_ITEM_DATA, NULL, &Power_Item, &System_Page, NULL, NULL);   
                AddItem(" -This is a testing program", UI_ITEM_DATA, NULL, &Test_Item, &System_Page, NULL, NULL);
                AddItem(" -Menu Color", UI_ITEM_DATA, NULL, &MenuColor_Item, &System_Page, NULL, NULL);   
                AddItem(" -Cursor Ani", UI_ITEM_DATA, NULL, &CursorAni_Item, &System_Page, NULL, NULL);
                #if ( UI_USE_FREERTOS == 1 )     
                AddItem(" -UI Stack", UI_ITEM_DATA, NULL, &SystemHeap_Item, &System_Page, NULL, NULL);
                #endif
                AddItem(" +MPU Task", UI_ITEM_PARENTS, NULL, &MPUTask_Item, &System_Page, &MPUTask_Page, NULL);
                    AddPage("[MPU Task]", &MPUTask_Page, UI_PAGE_TEXT);
                        AddItem("[MPU Task]", UI_ITEM_RETURN, NULL, &MPUTaskHead_Item, &MPUTask_Page, &System_Page, NULL);
                        #if ( UI_USE_FREERTOS == 1 )  
                        AddItem(" -Lvel", UI_ITEM_DATA, NULL, &MPUTaskLvel_Item, &MPUTask_Page, NULL, NULL);
                        AddItem(" -State", UI_ITEM_DATA, NULL, &MPUTaskState_Item, &MPUTask_Page, NULL, NULL);
                        #endif
                        AddItem(" -Pitch", UI_ITEM_DATA, NULL, &Pitch_Item, &MPUTask_Page, NULL, NULL);
                        AddItem(" -Roll", UI_ITEM_DATA, NULL, &Roll_Item, &MPUTask_Page, NULL, NULL);
                        AddItem(" -Yaw", UI_ITEM_DATA, NULL, &Yaw_Item, &MPUTask_Page, NULL, NULL);
        AddItem(" -Image", UI_ITEM_LOOP_FUNCTION, logo_allArray[2], &Image_Item, &Home_Page, NULL, Show_Logo);
        AddItem(" -Github", UI_ITEM_WORD, logo_allArray[3], &Github_Item, &Home_Page, NULL, NULL);
        AddItem(" -This is a testing program", UI_ITEM_WORD, logo_allArray[4], &Bilibili_Item, &Home_Page, NULL, NULL);
        AddItem(" -Version", UI_ITEM_ONCE_FUNCTION, logo_allArray[5], &Version_Item, &Home_Page, NULL, Show_Version);
        AddItem(" -Wave", UI_ITEM_WAVE, logo_allArray[6], &Wave_Item, &Home_Page, NULL, NULL);
}

void MiaoUi_Setup(ui_t *ui)
{
    Create_UI(ui, &HomeHead_Item); // 创建UI, 必须给定一个头项目
    Draw_Home(ui);
}
