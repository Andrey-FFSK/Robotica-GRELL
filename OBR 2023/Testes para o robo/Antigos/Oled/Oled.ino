#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
     display.setTextColor(WHITE);
}

void loop()
{
    display.print(F("O-NO-N-NE-E"));
    display.display();
}
