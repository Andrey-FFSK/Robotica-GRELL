#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>


Adafruit_SSD1306 display(128, 64, &Wire, -1);
int i;

void setup()
{
    Serial.begin(9600);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextColor(WHITE);
    //display.setFont(3);
    i = 0;
    
}

void loop()
{
  i = (i < 360) ? i+1 : 0;
      display.setCursor(64+cos(i*3.14/180)*25, 32+sin(i*3.14/180)*15);
      display.print(F("L"));
      display.display();
      //delay(10);
      display.clearDisplay();
  /*
  display.setCursor(0, 0); 
    display.print(F("O-NO-N-NE-E"));
    display.display();
  delay(100);
  display.clearDisplay();

  display.setCursor(0, 5); 
    display.print(F("O-NO-N-NE-E"));
    display.display();
  delay(100);
  display.clearDisplay();*/
}
