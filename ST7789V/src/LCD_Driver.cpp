
#include "LCD_Driver.h"

SPISettings settings(32000000, MSBFIRST, SPI_MODE0);
uint8_t cs, dc, rst;

static void LCD_Write_Command(uint8_t data) {
  digitalWrite(cs, 0);
  digitalWrite(dc, 0);
  SPI.transfer(data);
}

static void LCD_WriteData_Byte(uint8_t data) {
  digitalWrite(cs, 0);
  digitalWrite(dc, 1);
  SPI.transfer(data);
  digitalWrite(cs, 1);
}

void LCD_WriteData_Word(uint16_t data) {
  digitalWrite(cs, 0);
  digitalWrite(dc, 1);
  SPI.transfer16(data);
  digitalWrite(cs, 1);
}

void LCD_Init(uint8_t cs_pin, uint8_t dc_pin, uint8_t rst_pin) {
  cs = cs_pin;
  dc = dc_pin;
  rst = rst_pin;

  SPI.begin();
  SPI.beginTransaction(settings);

  pinMode(cs, OUTPUT);
  pinMode(dc, OUTPUT);
  pinMode(rst, OUTPUT);

  digitalWrite(cs, 1);

  digitalWrite(rst, 1);
  delay(50);
  digitalWrite(rst, 0);
  delay(50);
  digitalWrite(rst, 1);
  delay(100);

  LCD_Write_Command(0x01); //Software Reset

  LCD_Write_Command(0x36); //Memory Data Access Control
  LCD_WriteData_Byte(0x00);

  LCD_Write_Command(0x3A); //Interface Pixel Format
  LCD_WriteData_Byte(0x05);

  LCD_Write_Command(0x28); //Display Off

  LCD_Write_Command(0x21); //Display Inversion On

  LCD_Write_Command(0xB2); //Porch Setting
  LCD_WriteData_Byte(0x0C);
  LCD_WriteData_Byte(0x0C);
  LCD_WriteData_Byte(0x00);
  LCD_WriteData_Byte(0x33);
  LCD_WriteData_Byte(0x33);

  LCD_Write_Command(0xB7); //Gate Control
  LCD_WriteData_Byte(0x35);

  LCD_Write_Command(0xBB); //VCOM Setting
  LCD_WriteData_Byte(0x1F);

  LCD_Write_Command(0xC0); //LCM Control
  LCD_WriteData_Byte(0x2C);

  LCD_Write_Command(0xC2); //VDV and VRH Command Enable
  LCD_WriteData_Byte(0x01);

  LCD_Write_Command(0xC3); //VRH Set
  LCD_WriteData_Byte(0x12);

  LCD_Write_Command(0xC4); //VDV Set
  LCD_WriteData_Byte(0x20);

  LCD_Write_Command(0xC6); //Frame Rate Control in Normal Mode
  LCD_WriteData_Byte(0x0F);

  LCD_Write_Command(0xD0); //Power Control 1
  LCD_WriteData_Byte(0xA4);
  LCD_WriteData_Byte(0xA1);

  LCD_Write_Command(0xE0); //Positive Voltage Gamma Control
  LCD_WriteData_Byte(0xD0);
  LCD_WriteData_Byte(0x08);
  LCD_WriteData_Byte(0x11);
  LCD_WriteData_Byte(0x08);
  LCD_WriteData_Byte(0x0C);
  LCD_WriteData_Byte(0x15);
  LCD_WriteData_Byte(0x39);
  LCD_WriteData_Byte(0x33);
  LCD_WriteData_Byte(0x50);
  LCD_WriteData_Byte(0x36);
  LCD_WriteData_Byte(0x13);
  LCD_WriteData_Byte(0x14);
  LCD_WriteData_Byte(0x29);
  LCD_WriteData_Byte(0x2D);

  LCD_Write_Command(0xE1); //Negative Voltage Gamma Control
  LCD_WriteData_Byte(0xD0);
  LCD_WriteData_Byte(0x08);
  LCD_WriteData_Byte(0x10);
  LCD_WriteData_Byte(0x08);
  LCD_WriteData_Byte(0x06);
  LCD_WriteData_Byte(0x06);
  LCD_WriteData_Byte(0x39);
  LCD_WriteData_Byte(0x44);
  LCD_WriteData_Byte(0x51);
  LCD_WriteData_Byte(0x0B);
  LCD_WriteData_Byte(0x16);
  LCD_WriteData_Byte(0x14);
  LCD_WriteData_Byte(0x2F);
  LCD_WriteData_Byte(0x31);
  LCD_Write_Command(0x21);

  LCD_Write_Command(0x11); //Sleep Out

  LCD_Write_Command(0x29); //Display On

  LCD_SetWindow(0, 0, LCD_WIDTH, LCD_HEIGHT);

  LCD_SetOrientation(3);
}

void LCD_SetOrientation(uint8_t Mode) {
  LCD_Write_Command(0x36);
  switch (Mode) {
    case 0:
      LCD_WriteData_Byte(0xA0);
      break;
    case 1:
      LCD_WriteData_Byte(0x60);
      break;
    case 2:
      LCD_WriteData_Byte(0xC0);
      break;
    case 3:
      LCD_WriteData_Byte(0x00);
      break;
  }
}

void LCD_SetWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend) {
  LCD_Write_Command(0x2A); //Column Address Set
  LCD_WriteData_Byte(0x00);
  LCD_WriteData_Byte(Xstart & 0xff);
  LCD_WriteData_Byte((Xend - 1) >> 8);
  LCD_WriteData_Byte((Xend - 1) & 0xff);

  LCD_Write_Command(0x2B); //Row Address Set
  LCD_WriteData_Byte(0x00);
  LCD_WriteData_Byte(Ystart & 0xff);
  LCD_WriteData_Byte((Yend - 1) >> 8);
  LCD_WriteData_Byte((Yend - 1) & 0xff);

  LCD_Write_Command(0x2C); //Memory Write
}

void LCD_SetCursor(uint16_t X, uint16_t Y) {
  LCD_Write_Command(0x2A); //Column Address Set
  LCD_WriteData_Byte(X >> 8);
  LCD_WriteData_Byte(X);
  LCD_WriteData_Byte(X >> 8);
  LCD_WriteData_Byte(X);

  LCD_Write_Command(0x2B); //Row Address Set
  LCD_WriteData_Byte(Y >> 8);
  LCD_WriteData_Byte(Y);
  LCD_WriteData_Byte(Y >> 8);
  LCD_WriteData_Byte(Y);

  LCD_Write_Command(0x2C); //Memory Write
}

uint8_t LCD_Clear(uint16_t Color) {
  unsigned int i, j;
  LCD_SetWindow(0, 0, LCD_WIDTH, LCD_HEIGHT);
  digitalWrite(dc, 1);
  for (i = 0; i < LCD_WIDTH; i++)
    for (j = 0; j < LCD_HEIGHT; j++) {
      SPI.transfer((Color >> 8) & 0xff);
      SPI.transfer(Color);
    }

  return 1;
}

void LCD_ClearWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t color) {
  uint16_t i, j;
  LCD_SetWindow(Xstart, Ystart, Xend, Yend);
  for (i = Ystart; i <= Yend - 1; i++)
    for (j = Xstart; j <= Xend - 1; j++)
      LCD_WriteData_Word(color);
}

void LCD_DrawPaint(uint16_t x, uint16_t y, uint16_t Color) {
  LCD_SetCursor(x, y);
  LCD_WriteData_Word(Color);
}