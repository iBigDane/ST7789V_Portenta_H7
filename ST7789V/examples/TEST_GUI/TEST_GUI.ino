#include "LCD_Driver.h"
#include "GUI_Paint.h"

void setup(void) {
  bootM4();

  LCD_Init(5, 3, 10);
  LCD_Clear(0xFFFF);

  LCD_NewImage(LCD_WIDTH, LCD_HEIGHT, 270, WHITE);
  LCD_DrawString_EN(30, 10, "123", &Font24, YELLOW, RED);

  LCD_DrawRectangle(125, 10, 225, 58, RED, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
  LCD_DrawLine(125, 10, 225, 58, MAGENTA, LINE_STYLE_SOLID, DOT_PIXEL_2X2);
  LCD_DrawLine(225, 10, 125, 58, MAGENTA, LINE_STYLE_SOLID, DOT_PIXEL_2X2);

  LCD_DrawCircle(150, 100, 25, BLUE,  DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
  LCD_DrawCircle(180, 100, 25, BLACK, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
  LCD_DrawCircle(210, 100, 25, RED, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
  LCD_DrawCircle(165, 125, 25, YELLOW, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
  LCD_DrawCircle(195, 125, 25, GREEN, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
}

void loop() {
}
