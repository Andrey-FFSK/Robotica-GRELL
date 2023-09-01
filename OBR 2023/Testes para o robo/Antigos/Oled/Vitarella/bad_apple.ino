// so pega os primeiros 250 frames
// a cada 50 frames aumentava 10% da memoria usada
// 250 frames = 91% m
// ;-;

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "bad_apple.h"

#define W 128
#define H 64

Adafruit_SSD1306 display(W, H, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  for(int i = 0; i < badapple_len; i++) {
    display.clearDisplay();
    display.drawBitmap(W/2 - 16, H/2 - 8, badapple[i], 32, 16, WHITE);
    display.display();
    delay(50);
 }
}

void loop() {  
}