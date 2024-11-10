#ifndef __MENU_H__
#define __MENU_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "ui_conf.h"

void AddItem(const char *name, UI_ITEM_TYPE type, const uint8_t *image, ui_item_t *item, ui_page_t *localPage, ui_page_t *nextPage, ui_item_function function);
void AddPage(const char *name, ui_page_t *page, UI_PAGE_TYPE type);
float UI_Animation(float targrt, float now, ui_animation_param_t *obj);
float easeInOutCirc(float t, float b, float c, float d);
uint8_t Dialog_Show(ui_t *ui, int16_t x,int16_t y,int16_t targrtW,int16_t targrtH);
void Draw_Scrollbar(ui_t *ui, uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r, float step);
void Create_element(ui_item_t *item, ui_element_t *element);
void Create_UI(ui_t *ui, ui_item_t *item);

void ui_loop(ui_t *ui);

#ifdef __cplusplus
}
#endif

#endif
