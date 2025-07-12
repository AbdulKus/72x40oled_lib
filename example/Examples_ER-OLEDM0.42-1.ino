/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-OLEDM0.42-1
Display is Hardward I2C 2-Wire I2C Interface 
Tested and worked with:
Works with Arduino 1.6.0 IDE  
Test OK : Arduino DUE,Arduino mega2560,Arduino UNO Board 
****************************************************/
#include <Wire.h>
#include "er_oled.h"

/*
  == Hardware connection for 4 PIN module==
    OLED   =>    Arduino
  *1. GND    ->    GND
  *2. VCC    ->    3.3V
  *3. SCL    ->    SCL
  *4. SDA    ->    SDA

 == Hardware connection for 7 PIN module==
 Note:The module needs to be jumpered to an I2C interface.
    OLED   =>    Arduino
  *1. GND    ->    GND
  *2. VCC    ->    3.3V
  *3. SCL    ->    SCL
  *4. SDA    ->    SDA
  *5. RES    ->    8 
  *6. DC     ->    GND 
  *7. CS     ->    GND  
*/

uint8_t oled_buf[WIDTH * HEIGHT / 8];

void setup() {
  Serial.begin(9600);
  Serial.print("OLED Example\n");
  Wire.begin();
  
  /* display an image of bitmap matrix */
  er_oled_begin();
  er_oled_clear(oled_buf);
  er_oled_bitmap(0, 0, PIC1, 72, 40, oled_buf);
  er_oled_display(oled_buf);
  delay(3000);  
  command(0xa7);//--set Negative display 
  delay(3000);
  command(0xa6);//--set normal display
  
  er_oled_clear(oled_buf);
  er_oled_bitmap(0, 0, PIC2, 72, 40, oled_buf);
  er_oled_display(oled_buf);
  delay(3000);
  
  command(0xa7);//--set Negative display 
  delay(3000); 
  command(0xa6);//--set normal display  
  
  er_oled_clear(oled_buf);
  /* display images of bitmap matrix */
  er_oled_bitmap(0, 0, Signal816, 16, 8, oled_buf); 
  er_oled_bitmap(24, 0,Bluetooth88, 8, 8, oled_buf); 
  er_oled_bitmap(40, 0, Msg816, 16, 8, oled_buf); 
  er_oled_bitmap(64, 0, GPRS88, 8, 8, oled_buf); 

  er_oled_char(0, 14, '1' ,12, 1, oled_buf);
  er_oled_char(9, 14, '2', 12, 1, oled_buf);
  er_oled_char(18, 14, ':', 12, 1, oled_buf);
  er_oled_char(27, 14, '0', 12, 1, oled_buf);
  er_oled_char(36, 14, '6', 12, 1, oled_buf);
  er_oled_char(45, 14, ':', 12, 1, oled_buf);
  er_oled_char(54, 14, '1', 12, 1, oled_buf);
  er_oled_char(63, 14, '8', 12, 1, oled_buf);
  
  er_oled_string(6, 28, "buydisplay", 12, 1, oled_buf);
  er_oled_display(oled_buf); 
}

void loop() {

}
