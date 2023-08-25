#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define W 128
#define H 64
#define r 10
#define sp 10

Adafruit_SSD1306 display(W, H, &Wire, -1);

int n;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  Serial.begin(9600);

  n = 1;
}

void loop() {
  display.clearDisplay();

  display.drawPixel(W/2, H/2, WHITE);
  //display.drawFastVLine(W/2, 0, H, WHITE);
  //display.drawFastHLine(0, H/2, W, WHITE);
  for(int i = 0; i < 360; i++)
    display.drawPixel(W/2 + cos(i * PI/180) * r, H/2 + sin(i * PI/180) * r, WHITE);

  int x = W/2 + cos(n * PI/180) * r;
  int y = H/2 + sin(n * PI/180) * r;

  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" / y: ");
  Serial.println(y);

  display.setCursor(x, y);
  display.setTextColor(WHITE);
  display.print("L");

  n = (n < 360) ? n+sp : 0;

  delay(1);
  display.display();
}