#ifndef __GUI_PAINT_H
#define __GUI_PAINT_H

#include "LCD_Driver.h"
#include "fonts.h"

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#elif defined(__IMXRT1052__) || defined(__IMXRT1062__)
// PROGMEM is defefind for T4 to place data in specific memory section
#undef PROGMEM
#define PROGMEM
#else
#define PROGMEM
#endif

/**
   Image attributes
**/
typedef struct {
  uint8_t *Image;
  uint16_t Width;
  uint16_t Height;
  uint16_t WidthMemory;
  uint16_t HeightMemory;
  uint16_t Color;
  uint16_t Rotate;
  uint16_t Mirror;
  uint16_t WidthByte;
  uint16_t HeightByte;
} PAINT;
extern volatile PAINT Paint;

/**
   Display rotate
**/
#define ROTATE_0            0
#define ROTATE_90           90
#define ROTATE_180          180
#define ROTATE_270          270

/**
   Display Flip
**/
typedef enum {
  MIRROR_NONE  = 0x00,
  MIRROR_HORIZONTAL = 0x01,
  MIRROR_VERTICAL = 0x02,
  MIRROR_ORIGIN = 0x03,
} MIRROR_IMAGE;
#define MIRROR_IMAGE_DFT MIRROR_NONE

/**
   image color
**/

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


#define IMAGE_BACKGROUND    WHITE
#define FONT_FOREGROUND     BLACK
#define FONT_BACKGROUND     WHITE

/**
   The size of the point
**/
typedef enum {
  DOT_PIXEL_1X1  = 1,   // 1 x 1
  DOT_PIXEL_2X2  ,    // 2 X 2
  DOT_PIXEL_3X3  ,    // 3 X 3
  DOT_PIXEL_4X4  ,    // 4 X 4
  DOT_PIXEL_5X5  ,    // 5 X 5
  DOT_PIXEL_6X6  ,    // 6 X 6
  DOT_PIXEL_7X7  ,    // 7 X 7
  DOT_PIXEL_8X8  ,    // 8 X 8
} DOT_PIXEL;
#define DOT_PIXEL_DFT  DOT_PIXEL_1X1  //Default dot pilex

/**
   Point size fill style
**/
typedef enum {
  DOT_FILL_AROUND  = 1,   // dot pixel 1 x 1
  DOT_FILL_RIGHTUP  ,     // dot pixel 2 X 2
} DOT_STYLE;
#define DOT_STYLE_DFT  DOT_FILL_AROUND  //Default dot pilex

/**
   Line style, solid or dashed
**/
typedef enum {
  LINE_STYLE_SOLID = 0,
  LINE_STYLE_DOTTED,
} LINE_STYLE;

/**
   Whether the graphic is filled
**/
typedef enum {
  DRAW_FILL_EMPTY = 0,
  DRAW_FILL_FULL,
} DRAW_FILL;

/**
   Custom structure of a time attribute
**/
typedef struct {
  uint16_t Year;  //0000
  uint8_t  Month; //1 - 12
  uint8_t  Day;   //1 - 30
  uint8_t  Hour;  //0 - 23
  uint8_t  Min;   //0 - 59
  uint8_t  Sec;   //0 - 59
} PAINT_TIME;
extern PAINT_TIME sPaint_time;

//init and Clear
void LCD_NewImage(uint16_t Width, uint16_t Height, uint16_t Rotate, uint16_t Color);
void LCD_SelectImage(uint8_t *image);
void LCD_SetRotate(uint16_t Rotate);
void LCD_SetMirroring(uint8_t mirror);
void LCD_SetPixel(uint16_t Xpoint, uint16_t Ypoint, uint16_t Color);

void LCD_ClearWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color);

//Drawing
void LCD_DrawPoint(uint16_t Xpoint, uint16_t Ypoint, uint16_t Color, DOT_PIXEL Dot_Pixel, DOT_STYLE Dot_FillWay);
void LCD_DrawLine(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color, LINE_STYLE Line_Style, DOT_PIXEL Dot_Pixel);
void LCD_DrawRectangle(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color, DRAW_FILL Filled , DOT_PIXEL Dot_Pixel);
void LCD_DrawCircle(uint16_t X_Center, uint16_t Y_Center, uint16_t Radius, uint16_t Color, DRAW_FILL Draw_Fill , DOT_PIXEL Dot_Pixel);

//Display string
void LCD_DrawChar(uint16_t Xstart, uint16_t Ystart, const char Acsii_Char, sFONT* Font, uint16_t Color_Background, uint16_t Color_Foreground);
void LCD_DrawString(uint16_t Xstart, uint16_t Ystart, const char * pString, sFONT* Font, uint16_t Color_Background, uint16_t Color_Foreground);
void LCD_DrawNum(uint16_t Xpoint, uint16_t Ypoint, int32_t Nummber, sFONT* Font, uint16_t Color_Background, uint16_t Color_Foreground);
void LCD_DrawTime(uint16_t Xstart, uint16_t Ystart, PAINT_TIME *pTime, sFONT* Font, uint16_t Color_Background, uint16_t Color_Foreground);

//pic
void LCD_DrawImage(const unsigned char *image, uint16_t Startx, uint16_t Starty, uint16_t Endx, uint16_t Endy);

#endif
