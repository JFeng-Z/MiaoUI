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
#ifndef _DISP_DRIVER_H_
#define _DISP_DRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "ui_conf.h"

void dispInit(void);
void Disp_ClearBuffer(void);
void Disp_SendBuffer(void);
void Disp_SetFont(const uint8_t  *font);
void Disp_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
uint16_t Disp_DrawStr(uint16_t x, uint16_t y, const char *str);
void Disp_SetDrawColor(void *color);
void Disp_DrawFrame(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void Disp_DrawRFrame(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r);
void Disp_DrawBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void Disp_DrawRBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r);
void Disp_DrawXBMP(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap);
void Disp_SetContrast(ui_t *ui);
void Disp_SetPowerSave(ui_t *ui);
uint8_t Disp_GetBufferTileHeight(void);
uint8_t Disp_GetBufferTileWidth(void);
uint8_t *Disp_GetBufferPtr(void);
void Disp_SetClipWindow(uint16_t clip_x0, uint16_t clip_y0, uint16_t clip_x1, uint16_t clip_y1);
void Disp_SetMaxClipWindow(void);
void Disp_SetBufferCurrTileRow(uint8_t row);
uint16_t Disp_DrawUTF8(uint16_t x, uint16_t y, const char *str);
uint16_t Disp_GetUTF8Width(const char *str);
void Disp_UpdateDisplayArea(uint8_t tx, uint8_t ty, uint8_t tw, uint8_t th);

#ifdef __cplusplus
}
#endif

#endif
