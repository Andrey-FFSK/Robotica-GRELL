#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

int pinos[] = {A0, A1, A2, A3, A4, 6, 5, 9, 10};
int val[] = {0, 1, 1, 1, 0};

Adafruit_SSD1306 dis(128, 64, &Wire, -1);

int temp = 1000;
unsigned long int ant;

void setup()
{
    dis.begin(SSD1306_SWITCHCAPVCC, 0x3D);
    dis.clearDisplay();
    dis.setTextSize(1);
    dis.setTextColor(WHITE);
}

void loop()
{
    if(millis() - ant >= temp){
    ant = millis();
    dis.print("O-NO-N-NE-E");
    for (int i = 0; i < 5; i++)
    {
        dis.print(val[i]);
        if(i < 4){
          dis.print("-");
        }
    }
    dis.display();
    }
}
