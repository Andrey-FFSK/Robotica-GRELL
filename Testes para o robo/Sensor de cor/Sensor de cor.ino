
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define led_g 2
#define esq A1
#define dir A0

Adafruit_SSD1306 display(128, 64, &Wire, -1);
int pin[] = {2, A0, A1};

void setup(){

display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
display.setTextColor(WHITE);

for(int i = 0; i < 1; i++) pinMode(pin[i], OUTPUT);
for(int i = 1; i < 3; i++) pinMode(pin[i], INPUT);
Serial.begin(9600);
}

void loop(){
  digitalWrite(led_g, 1);
  
  Serial.print("Esq: ");
  Serial.println(analogRead(esq));
  Serial.println();
  /*Serial.print(" Dir: ");
  Serial.println(analogRead(dir));*/
  
 int m_esq = map(constrain(analogRead(esq), 30, 180), 30, 180, 0, 1023);
 int m_dir = map(constrain(analogRead(dir), 30, 300), 30, 300, 0, 1023);
Serial.print("Esq: ");
Serial.print(m_esq);
Serial.print(" | Dir: "); 
Serial.println(m_dir);

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
display.println(analogRead(dir));

display.print("Esq: ");
display.print(m_esq);
display.print(" | Dir: "); 
display.print(m_dir);
display.display();


}