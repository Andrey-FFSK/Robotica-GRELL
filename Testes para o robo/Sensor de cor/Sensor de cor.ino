#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define led_r A2
#define led_g 2
#define led_b A1
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
  digitalWrite(led_g, 1);
  //digitalWrite(led_b, 1);
 int c_esq = constrain(analogRead(esq), 800, 1023);
 int m_esq = map(c_esq, 800, 1023, 0, 1023);
Serial.print("Esq: ");
Serial.print(m_esq);
Serial.println(" | Dir: ");
/*
Serial.println();
delay(100);

if(analogRead(esq) > 980){
    Serial.print("Esq = Preto");
}
else if (analogRead(esq) < 910){
    Serial.print("Esq = Branco");
}
else{
    Serial.print("Esq = Verde");
}


if(analogRead(dir) > 980){
    Serial.println(" Dir = Preto");
}
else if (analogRead(dir) < 910){
    Serial.println(" Dir = Branco");
}
else{
    Serial.println(" Dir = Verde");
}*/

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
