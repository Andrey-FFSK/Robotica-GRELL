#ifndef _OLED_H
#define _OLED_H
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void setRotation(uint8_t rotation);

#define OLED_W 128 // largura em pixels
#define OLED_H 64  // altura em pixels

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
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x01, 0xb0,
        0x00, 0x00, 0x00, 0x30, 0x01, 0x00, 0x01, 0xbc, 0x08, 0x20, 0x44, 0x34, 0x00, 0x40, 0x08, 0x28,
        0x00, 0x03, 0x10, 0x20, 0x05, 0xff, 0x80, 0x30, 0x07, 0xfe, 0x20, 0xa0, 0x0f, 0xdf, 0xee, 0x80,
        0x0f, 0xb9, 0x3d, 0x70, 0x1f, 0xe3, 0x73, 0xc0, 0x1d, 0xe0, 0xe3, 0xc0, 0x1f, 0xe0, 0x00, 0xc0,
        0x1f, 0x63, 0xa0, 0x40, 0x1f, 0x67, 0xc1, 0xc0, 0x1f, 0x47, 0x21, 0x40, 0x1b, 0x47, 0xe3, 0xc0,
        0x1f, 0x47, 0xc3, 0xc0, 0x1f, 0x47, 0xc3, 0xc0, 0x0e, 0x5f, 0xdb, 0x80, 0x1b, 0xdf, 0x83, 0xe0,
        0x03, 0x78, 0x00, 0x80, 0x00, 0x3f, 0xce, 0x00, 0x00, 0x6b, 0xf8, 0x00, 0x00, 0x00, 0x20, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    const unsigned char abeiapeqena[] PROGMEM = { // abelha menor 16x16
        0x00, 0x00, 0x00, 0x04, 0x00, 0x20, 0x04, 0x2a, 0x2f, 0xc8, 0x3d, 0xc0, 0x3e, 0xec, 0x74, 0x88,
        0x79, 0x88, 0x7b, 0x90, 0x7b, 0x98, 0x3f, 0x98, 0x17, 0x10, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00
    };

    // funcoes pra desenha cada abelha
    inline void abeia_grande(const int x, const int y, int ) { 
        display.drawBitmap(x, y + sin(16 * FRAME_i * PI/180)*3, abeia, 32, 32, WHITE);
    }

    inline void abeia_pequena(const int x, const int y) {
        display.drawBitmap(x, y + sin(16 * FRAME_i * PI/180)*1.5, abeiapeqena, 16, 16, WHITE);
    }
}

#endif
