#include <Wire.h>
#include "TinyOLED.h"

TinyOLED oled;

void setup() {
  oled.begin(0x3C);
  
  oled.clear();
  
  oled.drawRect(0, 0, 71, 39, 0, 0);
  
  oled.drawRect(10, 10, 25, 15, 1, 0);
  
  oled.drawRect(30, 20, 50, 30, 1, 1);
  
  oled.drawText(10, 25, "Hi!", 0, 0);
  
  oled.drawPixel(35, 35, 1);
  //oled.drawPixel(36, 35, 1);
  //oled.drawPixel(37, 35, 1);
  oled.testPattern();
}

void loop() {
  //oled.drawPixel(random(72), random(40), 1);
  //oled.drawPixel(random(72), random(40), 2);
}
