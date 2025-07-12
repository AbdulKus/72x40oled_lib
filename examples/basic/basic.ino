#include <Wire.h>
#include <SSD1315.h>

SSD1315 display;

void setup(){
    Wire.begin();
    display.begin();
    display.fill(0);
    display.drawBitmap(0,0,PIC1,72,40);
    display.display();
}

void loop(){}
