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
#ifndef __UI_H__
#define __UI_H__

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
