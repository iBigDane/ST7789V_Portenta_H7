#ifndef __LCD_DRIVER_H
#define __LCD_DRIVER_H

#include <stdint.h>
#include <stdio.h>
#include <SPI.h>

#define LCD_WIDTH   240
#define LCD_HEIGHT  320

void LCD_SetOrientation(uint8_t Mode);
void LCD_SetCursor(uint16_t X, uint16_t Y);
void LCD_SetWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t  Yend);
void LCD_DrawPaint(uint16_t x, uint16_t y, uint16_t Color);

void LCD_Init(uint8_t cs_pin, uint8_t dc_pin, uint8_t rst_pin);
void LCD_SetBackLight(uint16_t Value);

uint8_t LCD_Clear(uint16_t Color);
void LCD_ClearWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t color);

#define WHITE         0xFFFF
#define BLACK         0x0000    
#define BLUE          0x001F  
#define BRED          0XF81F
#define GRED          0XFFE0
#define GBLUE         0X07FF
#define RED           0xF800
#define MAGENTA       0xF81F
#define GREEN         0x07E0
#define CYAN          0x7FFF
#define YELLOW        0xFFE0
#define BROWN         0XBC40 
#define BRRED         0XFC07 
#define GRAY          0X8430 
#define DARKBLUE      0X01CF  
#define LIGHTBLUE     0X7D7C   
#define GRAYBLUE      0X5458 
#define LIGHTGREEN    0X841F 
#define LGRAY         0XC618 
#define LGRAYBLUE     0XA651
#define LBBLUE        0X2B12

#endif
