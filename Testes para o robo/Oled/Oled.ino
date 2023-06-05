#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int pinos[] = {A0, A1, A2, A3, A4, 6, 5, 9, 10};
int val[] = {0, 1, 1, 1, 0};

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop()
{
    display.println("O-NO-N-NE-E");
    for (int i = 0; i < 5; i++)
    {
        display.print(val[i]);
        if(i < 4){
          display.print("-");
        }
    }
    display.display();
}
