#ifndef _HAL_DISPLAY_H_
#define _HAL_DISPLAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "ui_conf.h"

void HAL_dispInit(void);
void HAL_Disp_ClearBuffer(void);
void HAL_Disp_SendBuffer(void);
void HAL_Disp_SetFont(const uint8_t  *font);
void HAL_Disp_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
uint16_t HAL_Disp_DrawStr(uint16_t x, uint16_t y, const char *str);
void HAL_Disp_SetDrawColor(void *color);
void HAL_Disp_DrawFrame(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void HAL_Disp_DrawRFrame(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r);
void HAL_Disp_DrawBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
void HAL_Disp_DrawRBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r);
void HAL_Disp_DrawXBMP(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap);
void HAL_Disp_SetContrast(ui_t *ui);
void HAL_Disp_SetPowerSave(ui_t *ui);
uint8_t HAL_Disp_GetBufferTileHeight(void);
uint8_t HAL_Disp_GetBufferTileWidth(void);
uint8_t *HAL_Disp_GetBufferPtr(void);
void HAL_Disp_SetClipWindow(uint16_t clip_x0, uint16_t clip_y0, uint16_t clip_x1, uint16_t clip_y1);
void HAL_Disp_SetMaxClipWindow(void);
void HAL_Disp_SetBufferCurrTileRow(uint8_t row);
uint16_t HAL_Disp_DrawUTF8(uint16_t x, uint16_t y, const char *str);
uint16_t HAL_Disp_GetUTF8Width(const char *str);
void HAL_Disp_UpdateDisplayArea(uint8_t tx, uint8_t ty, uint8_t tw, uint8_t th);

#ifdef __cplusplus
}
#endif

#endif
