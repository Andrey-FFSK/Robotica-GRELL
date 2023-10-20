#ifndef _OLED_H
#define _OLED_H
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void setRotation(uint8_t rotation);

#define OLED_W 128 // largura em pixels
#define OLED_H 64  // altura em pixels

#define W 128
#define H 64
#define lw 6
#define lh 8

Adafruit_SSD1306 display(128, 64, &Wire, -1);

namespace OLED {
    // contagem do frame das animacoes
    int FRAME_i;
    inline void frame_incr() { FRAME_i = (FRAME_i < 360) ? FRAME_i+1 : 0; }

    // ====================== SETAS ======================
    int cX = 24; // posicao horizontal do ponto central
    int cY = 40; // posicao vertical do ponto central

    // desenha o ponto central
    inline void ponto() { display.drawPixel(cX, cY, WHITE); }

    // desenha as setas vazias
    void setas() {
        //cima
        display.drawRect(cX-2,cY-9, 5, 6, WHITE);
        display.drawTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);

        //baixo
        display.drawRect(cX-2, cY+4, 5, 6, WHITE);
        display.drawTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);

        //direita
        display.drawRect(cX+4, cY-2, 6, 5, WHITE);
        display.drawTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);

        //esquertfa
        display.drawRect(cX-9, cY-2, 6, 5, WHITE);
        display.drawTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
    }

    // funcoes pras animacoes de cada seta
    void seta_cima() {
        switch(FRAME_i % 4) {
            case 0:
                display.drawRect(cX-2,cY-9, 5, 6, WHITE);
                display.drawTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);
                break;
                        
            case 1:
                display.drawRect(cX-2,cY-9, 5, 6, WHITE);
                display.fillRect(cX-2,cY-6, 5, 3, WHITE);
                display.drawTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);
                break;
                        
            case 2:
                display.fillRect(cX-2,cY-9, 5, 6, WHITE);
                display.drawTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);
                break;

            case 3:
                display.fillRect(cX-2,cY-9, 5, 6, WHITE);
                display.fillTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);
                break;
        }
    }
    void seta_baixo() {
        switch(FRAME_i % 4) {
            case 0:
                display.drawRect(cX-2, cY+4, 5, 6, WHITE);
                display.drawTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);
                break;
            
            case 1:
                display.drawRect(cX-2, cY+4, 5, 6, WHITE);
                display.fillRect(cX-2, cY+4, 5, 3, WHITE);
                display.drawTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);
                break;
            
            case 2:
                display.fillRect(cX-2, cY+4, 5, 6, WHITE);
                display.drawTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);
                break;

            case 3:
                display.fillRect(cX-2, cY+4, 5, 6, WHITE);
                display.fillTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);
                break;
        }
    }
    void seta_esq() {
        switch(FRAME_i % 4) {
            case 0:
                display.drawRect(cX-9, cY-2, 6, 5, WHITE);
                display.drawTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
                break;
            
            case 1:
                display.drawRect(cX-9, cY-2, 6, 5, WHITE);
                display.fillRect(cX-6, cY-2, 3, 5, WHITE);
                display.drawTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
                break;
            
            case 2:
                display.fillRect(cX-9, cY-2, 6, 5, WHITE);
                display.drawTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
                break;

            case 3:
                display.fillRect(cX-9, cY-2, 6, 5, WHITE);
                display.fillTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
                break;
        }
    }
    void seta_dir() {
        switch(FRAME_i % 4) {
            case 0:
                display.drawRect(cX+4, cY-2, 6, 5, WHITE);
                display.drawTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);
                break;

            case 1:
                display.drawRect(cX+4, cY-2, 6, 5, WHITE);
                display.fillRect(cX+4, cY-2, 3, 5, WHITE);
                display.drawTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);
                break;

            case 2:
                display.fillRect(cX+4, cY-2, 6, 5, WHITE);
                display.drawTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);
                break;

            case 3:
                display.fillRect(cX+4, cY-2, 6, 5, WHITE);
                display.fillTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);
                break;
        }
    }

    // ====================== abeias ======================
    const unsigned char abeia[] PROGMEM = {       // abelha maior 32x32
    /*
    0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b1, 0b1, 0b0, 0b0, 0b1, 0b1,
    0b0, 0b0, 0b0, 0b1, 0b1, 0b0, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b0, 0b1, 0b1, 0b1,
    0b0, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
    0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b0, 0b1,
    0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
    0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1, 0b1,
    0b1, 0b1, 0b0, 0b1, 0b0, 0b1, 0b1, 0b0, 0b0, 0b1, 0b1, 0b0, 0b0, 0b0, 0b1, 0b0,
    0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0, 0b0
    */
// '350455639_626222852898743_8997346645438074390_n', 48x48px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00, 0x00, 0x00, 0x18, 0x40, 0x00, 0x00, 
0x00, 0x00, 0x19, 0x40, 0x00, 0x00, 0x40, 0x00, 0x01, 0x4c, 0x00, 0x00, 0x20, 0x00, 0x01, 0x40, 
0x00, 0x10, 0x00, 0x00, 0x11, 0x68, 0x00, 0x02, 0x00, 0x00, 0x41, 0x48, 0x00, 0x08, 0x80, 0x00, 
0x05, 0x50, 0x00, 0x02, 0x00, 0x02, 0x01, 0x00, 0x01, 0x00, 0x00, 0x14, 0x01, 0x20, 0x00, 0x05, 
0xff, 0x00, 0x01, 0x40, 0x00, 0x3f, 0xff, 0xc2, 0x05, 0x00, 0x00, 0xff, 0xff, 0x10, 0x00, 0x80, 
0x01, 0xff, 0xc3, 0xfa, 0x09, 0x00, 0x03, 0xfd, 0x7f, 0xc3, 0xc0, 0x00, 0x03, 0xdf, 0xfc, 0x0f, 
0x83, 0xc0, 0x07, 0xdd, 0x90, 0x18, 0x07, 0xc0, 0x07, 0xfb, 0x82, 0x78, 0x0e, 0x00, 0x07, 0xbb, 
0x00, 0x70, 0x0c, 0x00, 0x07, 0xbb, 0x00, 0x60, 0x1e, 0x00, 0x07, 0xbb, 0x00, 0x00, 0x02, 0x00, 
0x07, 0xbb, 0x00, 0x00, 0x02, 0x00, 0x0f, 0x73, 0x0f, 0xc0, 0x06, 0x00, 0x0f, 0xf3, 0x0f, 0xe0, 
0x1e, 0x00, 0x0f, 0x72, 0x0f, 0x10, 0x3e, 0x00, 0x0f, 0x72, 0x0f, 0x10, 0x32, 0x00, 0x0f, 0x76, 
0x1f, 0xd0, 0x3e, 0x00, 0x0f, 0x66, 0x1f, 0xf0, 0x3e, 0x00, 0x0f, 0x66, 0x1f, 0xe0, 0x7c, 0x00, 
0x07, 0xe6, 0x1f, 0xe0, 0x7e, 0x00, 0x07, 0xe6, 0x0f, 0xe1, 0x7c, 0x00, 0x03, 0xe6, 0x7f, 0xe0, 
0x67, 0x00, 0x06, 0x7e, 0x7f, 0x80, 0x0f, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 
0x00, 0x00, 0x10, 0x00, 0x00, 0x01, 0xd0, 0x00, 0x20, 0x00, 0x00, 0x03, 0x8a, 0xfc, 0x80, 0x00, 
0x00, 0x02, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    /*
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x01, 0xb0,
    0x00, 0x00, 0x00, 0x30, 0x01, 0x00, 0x01, 0xbc, 0x08, 0x20, 0x44, 0x34, 0x00, 0x40, 0x08, 0x28,
    0x00, 0x03, 0x10, 0x20, 0x05, 0xff, 0x80, 0x30, 0x07, 0xfe, 0x20, 0xa0, 0x0f, 0xdf, 0xee, 0x80,
    0x0f, 0xb9, 0x3d, 0x70, 0x1f, 0xe3, 0x73, 0xc0, 0x1d, 0xe0, 0xe3, 0xc0, 0x1f, 0xe0, 0x00, 0xc0,
    0x1f, 0x63, 0xa0, 0x40, 0x1f, 0x67, 0xc1, 0xc0, 0x1f, 0x47, 0x21, 0x40, 0x1b, 0x47, 0xe3, 0xc0,
    0x1f, 0x47, 0xc3, 0xc0, 0x1f, 0x47, 0xc3, 0xc0, 0x0e, 0x5f, 0xdb, 0x80, 0x1b, 0xdf, 0x83, 0xe0,
    0x03, 0x78, 0x00, 0x80, 0x00, 0x3f, 0xce, 0x00, 0x00, 0x6b, 0xf8, 0x00, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    */
    };

    
    const unsigned char abeiapeqena[] PROGMEM = { // abelha menor 16x16
        0x00, 0x00, 0x00, 0x04, 0x00, 0x20, 0x04, 0x2a, 0x2f, 0xc8, 0x3d, 0xc0, 0x3e, 0xec, 0x74, 0x88,
        0x79, 0x88, 0x7b, 0x90, 0x7b, 0x98, 0x3f, 0x98, 0x17, 0x10, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00
    };

    // funcoes pra desenha cada abelha
    inline void abeia_grande(const int x, const int y, int amp = 3, int freq = 16) { 
        display.drawBitmap(x, y + sin(freq * FRAME_i * PI/180)*amp, abeia, 48, 48, WHITE);
    }

    inline void abeia_pequena(const int x, const int y, int amp = 1, int freq = -12) {
        display.drawBitmap(x, y + sin(freq * FRAME_i * PI/180)*amp, abeiapeqena, 16, 16, WHITE);
    }
}

#endif
