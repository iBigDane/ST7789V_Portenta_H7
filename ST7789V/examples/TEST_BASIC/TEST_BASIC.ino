#include "LCD_Driver.h"

#define STEP 100

uint16_t color;
uint8_t status;
uint16_t timer;

void setup() {
  Serial.begin(9600);
  LCD_Init(5, 3, 10);
  LCD_SetOrientation(0);

  timer = millis();
}

void loop() {
  for (color = 0; color < 0xFFFF; color += STEP) {
    timer = millis();
    status = 0;
    while (!status) status = LCD_Clear(color);
    timer = millis() - timer;
    Serial.println("Color: " + String(color) + ", Time: " + String(timer) + " ms");
  }
}
