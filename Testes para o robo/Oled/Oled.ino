#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>


int pinos[] = {A0, A1, A2, A3, A4, 6, 5, 9, 10};
int val[] = {0, 1, 1, 1, 0};

Adafruit_SSD1306 dis(128, 64, &Wire, -1);

void setup()
{
    dis.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    dis.clearDisplay();
    dis.setTextSize(3);
    dis.setTextColor(WHITE);
    
    dis.setCursor(0, 0);
}

void loop()
{
    dis.print("O\tNO\tN\tNE\tE");
    for (int i = 0; i < 5; i++)
    {
        dis.print(val[i]);
        dis.print("\t");
    }
    dis.display();
}