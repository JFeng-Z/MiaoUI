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
