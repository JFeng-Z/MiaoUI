#include "ui_conf.h"
#include "ui.h"
#include "dispDirver.h"
#include "image.h"
#include "custom.h"
#include "version.h"

/*Page*/
ui_page_t Home_Page, System_Page;
/*item */
ui_item_t HomeHead_Item, SystemHead_Item, System_Item, Github_Item;
ui_item_t Contrast_Item;

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
        AddItem(" -Github", UI_ITEM_WORD, logo_allArray[3], &Github_Item, &Home_Page, NULL, NULL);
}

void MiaoUi_Setup(ui_t *ui)
{
    Create_UI(ui, &HomeHead_Item); // 创建UI, 必须给定一个头项目
    Draw_Home(ui);
}