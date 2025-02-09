#include "HAL_Display.h"
#include "U8g2lib.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

/**
 * 初始化显示设备。
 * 该函数负责初始化OLED显示器，并设置默认字体。
 * 
 * @无参数
 * @无返回值
 */
void HAL_dispInit(void)
{
    // 初始化U8g2库，为OLED显示做准备
    u8g2.begin();
}

/**
 * 清除OLED显示缓冲区
 * 
 * 该函数用于清空OLED显示器的缓冲区，为新的显示内容做准备。
 * 
 * 参数: 
 * 无
 * 
 * 返回值: 
 * 无
 */
void HAL_Disp_ClearBuffer(void)
{
    u8g2.clearBuffer();  // 清除OLED显示缓冲区的具体实现，使用u8g2库提供的函数。
}

/**
 * 向OLED发送缓冲区数据
 * 该函数无参数。
 * 该函数无返回值。
 */
void HAL_Disp_SendBuffer(void)
{
    /* 将U8G2实例的缓冲区数据发送到OLED设备 */
    u8g2.sendBuffer();
}

/**
 * 设置OLED显示器的字体。
 * 
 * @param font 指向要使用的字体的指针。该字体必须是提前定义并可用的。
 * 
 * 说明：这个函数通过调用u8g2的设置函数，来更改当前OLED显示的字体。
 */
void HAL_Disp_SetFont(const uint8_t  *font)
{
    u8g2.setFont(font);
}

/**
 * 在OLED显示器上绘制一条线。
 * 
 * @param x1 起始点的X坐标。
 * @param y1 起始点的Y坐标。
 * @param x2 终点的X坐标。
 * @param y2 终点的Y坐标。
 * 
 * 该函数调用u8g2的DrawLine函数，使用给定的起始点和终点坐标在OLED显示器上绘制一条线。
 */
void HAL_Disp_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    u8g2.drawLine(x1, y1, x2, y2);
}

/**
 * 在OLED屏幕上绘制字符串
 * 
 * @param x 字符串起始绘制的x坐标
 * @param y 字符串起始绘制的y坐标
 * @param str 要绘制的字符串
 * @return 绘制后的光标位置（一般为字符串的结束位置），具体返回值意义可能依赖于u8g2库的实现
 */
uint16_t HAL_Disp_DrawStr(uint16_t x, uint16_t y, const char *str)
{
    // 调用u8g2库的DrawStr函数，在指定位置绘制字符串
    return u8g2.drawStr(x, y, str);
}

/**
 * 设置OLED显示设备的绘制颜色。
 * 
 * @param color 指定的绘制颜色，使用uint8_t类型表示。颜色的具体编码取决于OLED驱动库的实现。
 * 
 * 该函数通过调用u8g2库的u8g2_SetDrawColor函数，来设置当前绘制的颜色。绘制颜色会影响后续所有绘制操作。
 */
void HAL_Disp_SetDrawColor(void *color)
{
    u8g2.setDrawColor(*(uint8_t *)color);
}

/**
 * 在OLED屏幕上绘制一个框架。
 * 
 * @param x 框架的起始x坐标。
 * @param y 框架的起始y坐标。
 * @param w 框架的宽度。
 * @param h 框架的高度。
 * 
 * 该函数调用u8g2的绘制框架函数，用于在指定位置和尺寸上绘制一个框架。
 */
void HAL_Disp_DrawFrame(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    u8g2.drawFrame(x, y, w, h);
}

/**
 * 在OLED屏幕上绘制一个矩形边框。
 * 
 * @param x 矩形左上角x坐标。
 * @param y 矩形左上角y坐标。
 * @param w 矩形的宽度。
 * @param h 矩形的高度。
 * @param r 矩形圆角的半径。
 * 
 * 该函数调用u8g2的绘制函数，用于在指定位置以指定尺寸和圆角半径绘制一个矩形边框。
 */
void HAL_Disp_DrawRFrame(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r)
{
    u8g2.drawRFrame(x, y, w, h, r);
}

/**
 * 在OLED显示器上绘制一个矩形框。
 * 
 * @param x 矩形框左上角的x坐标。
 * @param y 矩形框左上角的y坐标。
 * @param w 矩形框的宽度。
 * @param h 矩形框的高度。
 * 
 * 该函数调用u8g2的绘制矩形框函数，传入指定的坐标和尺寸，在OLED屏幕上绘制矩形。
 */
void HAL_Disp_DrawBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    u8g2.drawBox(x, y, w, h);
}

/**
 * 在OLED显示器上绘制一个带圆角的矩形。
 * 
 * @param x 矩形左上角的x坐标。
 * @param y 矩形左上角的y坐标。
 * @param w 矩形的宽度。
 * @param h 矩形的高度。
 * @param r 矩形圆角的半径。
 * 
 * 该函数调用u8g2的绘制函数，以指定的坐标和尺寸，在OLED显示器上绘制一个带圆角的矩形。
 */
void HAL_Disp_DrawRBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t r)
{
    u8g2.drawRBox(x, y, w, h, r);
}

/**
 * 在OLED显示器上绘制一个XBM图像。
 * 
 * @param x 图像在显示器上的起始x坐标。
 * @param y 图像在显示器上的起始y坐标。
 * @param w 图像的宽度。
 * @param h 图像的高度。
 * @param bitmap 指向包含XBM图像数据的缓冲区的指针。
 * 
 * 此函数使用u8g2库的u8g2_DrawXBMP函数来绘制图像。图像数据必须是XBM格式的。
 */
void HAL_Disp_DrawXBMP(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint8_t *bitmap)
{
    u8g2.drawXBMP(x, y, w, h, bitmap);
}

/**
 * 设置OLED显示器的对比度。
 * 
 * @param value 对比度值，有效范围通常为0到255，具体取决于硬件的限制。
 * 
 * 该函数通过调用u8g2库中的u8g2_SetContrast函数，来设置OLED显示器的对比度。
 * 使用者需要根据具体的OLED显示器和u8g2配置来选择合适的对比度值。
 */
void HAL_Disp_SetContrast(ui_t *ui)
{
    u8g2.setContrast(*(uint8_t *)ui->nowItem->element->data->ptr);
}

/**
 * 设置OLED电源节省模式
 * 
 * 本函数用于根据输入参数启用或禁用OLED的电源节省模式。当is_enable为1时，启用电源节省模式；
 * 当is_enable为0时，禁用电源节省模式。
 * 
 * @param is_enable 一个无符号字符(uint8_t)，用来控制是否启用电源节省模式。
 *                  当其值为1时，启用电源节省模式；当其值为0时，禁用电源节省模式。
 */
void HAL_Disp_SetPowerSave(ui_t *ui)
{
    u8g2.setPowerSave(*(uint8_t *)ui->nowItem->element->data->ptr);
}

/**
 * 获取OLED缓冲区的 tile 高度。
 * 
 * 该函数不接受参数。
 * 
 * @return 返回OLED缓冲区的tile高度。返回值为uint8_t类型，即无符号8位整数。
 */
uint8_t HAL_Disp_GetBufferTileHeight(void)
{
    return u8g2.getBufferTileHeight();
}

/**
 * 获取OLED缓冲区的单个瓦片宽度。
 * 
 * 该函数查询U8G2图形库当前配置的OLED缓冲区的单个瓦片宽度。瓦片宽度是指OLED屏幕
 * 在显示更新时，一次可以处理的像素宽度。这个值通常取决于OLED屏幕的物理分辨率
 * 和U8G2库的内部处理方式。
 * 
 * @return 返回OLED缓冲区单个瓦片的宽度，单位为字节。
 */
uint8_t HAL_Disp_GetBufferTileWidth(void)
{
    return u8g2.getBufferTileWidth();
}

/**
 * 获取OLED显示缓冲区的指针
 * 
 * 该函数用于获取当前OLED显示设备的显示缓冲区的指针。该缓冲区是一个uint8_t类型的数组，
 * 用于存储即将显示在OLED屏幕上的图像数据。
 * 
 * @return 返回类型为uint8_t*，指向OLED显示缓冲区的起始位置。
 */
uint8_t *HAL_Disp_GetBufferPtr(void)
{
    // 调用u8g2库的函数获取显示缓冲区指针
    return u8g2.getBufferPtr();
}

void HAL_Disp_SetClipWindow(uint16_t clip_x0, uint16_t clip_y0, uint16_t clip_x1, uint16_t clip_y1)
{
    u8g2.setClipWindow(clip_x0, clip_y0, clip_x1, clip_y1);
}

void HAL_Disp_SetMaxClipWindow(void)
{
    u8g2.setMaxClipWindow();
}

void HAL_Disp_SetBufferCurrTileRow(uint8_t row)
{
    u8g2.setBufferCurrTileRow(row);
}

uint16_t HAL_Disp_DrawUTF8(uint16_t x, uint16_t y, const char *str)
{
    return u8g2.drawUTF8(x, y, str);
}

uint16_t HAL_Disp_GetUTF8Width(const char *str)
{
    return u8g2.getUTF8Width(str);
}

void HAL_Disp_UpdateDisplayArea(uint8_t tx, uint8_t ty, uint8_t tw, uint8_t th)
{
    u8g2.updateDisplayArea(tx, ty, tw, th);
}
