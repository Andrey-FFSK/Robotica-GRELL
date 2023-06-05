#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
}

void loop() {
  display.clearDisplay();
    display.setTextColor(BLACK);
    display.println(F("FODEUY"));
    display.display();
    delay(100);

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.println(F("FODEUY"));
    display.display();
    delay(100);
}
