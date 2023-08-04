

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define W 128 // OLED display width, in pixels
#define H 64 // OLED display height, in pixels

Adafruit_SSD1306 display(W, H, &Wire, -1);

int n;
const int cX = 40;
const int cY = 16;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(WHITE);

  n = 0;
}

void loop() {
  display.clearDisplay();
  display.drawPixel(cX, cY, WHITE);
  switch(n) {
    case 0:
      //cima
      display.drawRect(cX-2,cY-8, 5, 6, WHITE);
      display.drawTriangle(cX-4,cY-8, cX+4,cY-8, cX,cY-12, WHITE);

      //baixo
      display.drawRect(cX-2, cY+3, 5, 6, WHITE);
      display.drawTriangle(cX-4,cY+8, cX+4,cY+8, cX,cY+12, WHITE);
      break;
    case 1:
      display.fillRect(16, 48, 5, 3, WHITE);
      display.drawRect(16, 50, 5, 4, WHITE);
      display.drawTriangle(14,54, 22,54, 18,58, WHITE);
      break;
    case 2:
      display.fillRect(16, 48, 5, 6, WHITE);
      display.drawTriangle(14,54, 22,54, 18,58, WHITE);
      break;
    case 3:
      display.fillRect(16, 48, 5, 6, WHITE);
      display.fillTriangle(14,54, 22,54, 18,58, WHITE);
      //n = 0;
      break;
  }
  delay(150);
  n=(n>3)?0:n+1;
  display.display();
}
