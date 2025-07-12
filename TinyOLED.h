#ifndef TinyOLED_h
#define TinyOLED_h

#include <Arduino.h>
#include <Wire.h>

#define OLED_WIDTH 72
#define OLED_HEIGHT 40
#define OLED_PAGES (OLED_HEIGHT/8)

class TinyOLED {
  public:
    TinyOLED();
    void begin(uint8_t address = 0x3C);
    void clear();
    void fill(uint8_t pattern = 0xFF);
    void drawPixel(uint8_t x, uint8_t y, uint8_t color = 1);
    void drawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool fill = false, bool invert = false);
    void drawText(uint8_t x, uint8_t y, const char* text, bool invert = false);
    void setCursor(uint8_t x, uint8_t y);
    void update();
    void testPattern();

  private:
    uint8_t _address;
    uint8_t _cursorX;
    uint8_t _cursorY;
    uint8_t _buffer[OLED_WIDTH * OLED_HEIGHT / 8];
    void sendCommand(uint8_t cmd);
    void sendData(uint8_t data);
    void drawChar(uint8_t x, uint8_t y, char ch, bool invert);
};

#endif
