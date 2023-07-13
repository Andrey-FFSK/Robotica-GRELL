#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define led_r A2
#define led_g 8
#define led_b A2
#define esq A3
#define dir A0

Adafruit_SSD1306 display(128, 64, &Wire, -1);
int pin[] = {A2, 8, A3, A0, A3};

void setup(){

display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
display.setTextColor(WHITE);

for(int i = 0; i < 3; i++) pinMode(pin[i], OUTPUT);
for(int i = 3; i < 5; i++) pinMode(pin[i], INPUT);
Serial.begin(9600);
}

void loop(){
 //digitalWrite(led_r, 1);
 //digitalWrite(led_g, 1);
 //digitalWrite(led_b, 1);
Serial.print("Esq: ");
Serial.print(analogRead(esq));
Serial.print(" | Dir: ");
Serial.println(analogRead(dir));

display.clearDisplay();
display.setCursor(0, 0);
display.print("Esq: ");
display.print(analogRead(esq));
display.print(" | Dir: ");
display.print(analogRead(dir));
display.display();


}
//AZUL RILHANDO QUANDO LIGA
//LEMRAR DO CAO DO US E DA ATERIA, USAR ATERIA
