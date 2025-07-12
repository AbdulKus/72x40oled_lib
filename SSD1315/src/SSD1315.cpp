#include "SSD1315.h"

static void I2C_Write(uint8_t value,uint8_t cmd){
    Wire.beginTransmission(0x3c);
    Wire.write(cmd);
    Wire.write(value);
    Wire.endTransmission();
}

SSD1315::SSD1315(uint8_t rstPin):_rst(rstPin){}

void SSD1315::command(uint8_t c){I2C_Write(c,0x00);} 
void SSD1315::data(uint8_t d){I2C_Write(d,0x40);} 

void SSD1315::begin(){
    pinMode(_rst,OUTPUT);
    digitalWrite(_rst,HIGH);
    delay(10);
    digitalWrite(_rst,LOW);
    delay(10);
    digitalWrite(_rst,HIGH);
    command(0xae);
    command(0xd5);
    command(0x80);
    command(0xa8);
    command(0x27);
    command(0xd3);
    command(0x00);
    command(0xad);
    command(0x30);
    command(0x8d);
    command(0x14);
    command(0x40);
    command(0xa6);
    command(0xa4);
    command(0xa1);
    command(0xc8);
    command(0xda);
    command(0x12);
    command(0x81);
    command(0xaf);
    command(0xd9);
    command(0x22);
    command(0xdb);
    command(0x20);
    command(0xaf);
    clear();
    display();
}

void SSD1315::clear(){
    memset(buffer,0,sizeof(buffer));
}

void SSD1315::fill(uint8_t color){
    memset(buffer,color?0xff:0x00,sizeof(buffer));
}

void SSD1315::drawPixel(int x,int y,uint8_t color){
    if(x<0||x>=SSD1315_WIDTH||y<0||y>=SSD1315_HEIGHT)return;
    uint16_t i=x+(y/8)*SSD1315_WIDTH;
    uint8_t m=1<<(y%8);
    if(color) buffer[i]|=m; else buffer[i]&=~m;
}

void SSD1315::drawRect(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,bool fillRect,bool invert){
    if(x1<x0)swap(x0,x1);if(y1<y0)swap(y0,y1);
    for(uint8_t y=y0;y<=y1;y++){
        for(uint8_t x=x0;x<=x1;x++){
            bool edge=(x==x0||x==x1||y==y0||y==y1);
            if(fillRect||edge){
                uint16_t i=x+(y/8)*SSD1315_WIDTH;
                uint8_t m=1<<(y%8);
                if(invert) buffer[i]^=m; else buffer[i]|=m;
            }
        }
    }
}

void SSD1315::drawBitmap(uint8_t x,uint8_t y,const uint8_t* bmp,uint8_t w,uint8_t h,bool invert){
    uint8_t bw=(w+7)/8;
    for(uint8_t j=0;j<h;j++){
        for(uint8_t i=0;i<w;i++){
            if(pgm_read_byte(bmp+j*bw+i/8)&(128>>(i&7))){
                uint16_t idx=(x+i)+((y+j)/8)*SSD1315_WIDTH;
                uint8_t m=1<<((y+j)%8);
                if(invert) buffer[idx]^=m; else buffer[idx]|=m;
            }
        }
    }
}

static void draw_char(uint8_t x,uint8_t y,char c,uint8_t size,uint8_t mode,uint8_t* buf){
    unsigned char i,j,y0=y;
    char temp;
    unsigned char ch=c-' ';
    for(i=0;i<size;i++){
        if(size==12){
            temp=mode?pgm_read_byte(&Font1206[ch][i]):~pgm_read_byte(&Font1206[ch][i]);
        }else{
            temp=mode?pgm_read_byte(&Font1608[ch][i]):~pgm_read_byte(&Font1608[ch][i]);
        }
        for(j=0;j<8;j++){
            if(temp&0x80) buf[x+(y/8)*SSD1315_WIDTH]|=1<<(y%8);
            else buf[x+(y/8)*SSD1315_WIDTH]&=~(1<<(y%8));
            temp<<=1; y++; if((y-y0)==size){y=y0;x++;break;}
        }
    }
}

void SSD1315::drawChar(uint8_t x,uint8_t y,char c,uint8_t size,bool invert){
    draw_char(x,y,c,size,invert?0:1,buffer);
}

void SSD1315::drawString(uint8_t x,uint8_t y,const char* s,uint8_t size,bool invert){
    while(*s){
        if(x>(SSD1315_WIDTH-size/2)){x=0;y+=size;if(y>(SSD1315_HEIGHT-size))y=0;}
        draw_char(x,y,*s,size,invert?0:1,buffer);
        x+=size/2; s++;}
}

void SSD1315::display(){
    for(uint8_t page=0;page<SSD1315_PAGES;page++){
        command(0xB0+page);
        command(0x0c);
        command(0x11);
        for(uint8_t i=0;i<SSD1315_WIDTH;i++) data(buffer[i+page*SSD1315_WIDTH]);
    }
}

uint8_t* SSD1315::getBuffer(){return buffer;}

#include "font_data.h"
