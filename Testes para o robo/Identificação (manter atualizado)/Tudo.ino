#include <Ultrasonic.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define W 128
#define H 64
#define lw 6
#define lh 8

// Definindo as portas dos sensores e da portas H
#define s_oeste 8    // rosa, OUT1 
#define s_noroeste 10 // amarelo, OUT2
#define s_norte 11    // azul, OUT4
#define s_nordeste 12 // vermelho, OUT3                                 
#define s_leste 13    // marrom, OUT5

// Motor 1 = esquerda; Motor 2 = direita
#define mot_in1 3  // preto, esquerda, tras
#define mot_in2 5  // laranja, esquerda, frente
#define mot_in3 6  // branco, direita, frente
#define mot_in4 9 // amarelo, direita, tras

// Usando array para colocar todos os pinos, coloquei os sensores invertido por causa do BitSwift em baixo
int pinos[] = {8, 10, 11, 12, 13, 5, 3, 6, 9};
Ultrasonic sensor(7, 4);

//Definindo variaveis
int temp = 500;
int ant = 0;

int o = 150;
float tensaoA0;

Adafruit_SSD1306 display(W, H, &Wire, -1);

void setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  Serial.begin(9600);
  for(int i; i < 5; i++) pinMode(pinos[i], INPUT);
  for(int i = 5; i < 9; i++) pinMode(pinos[i], OUTPUT);
  
}

void loop(){
  display.clearDisplay();

//mot1_hor(o);
//mot2_hor(o);

//mot1_anti(o);
//mot2_anti(o);

display.setCursor(0, lh*2);
display.print("Leitura: ");
byte leitura = 0;
for(int i = 0; i < 5; i++) leitura |= digitalRead(pinos[i]) << i;
leitura = (~leitura) & 0b00011111;
for(int i = 11; i <= 15; i++) display.print(binString(leitura)[i]);
display.print(" Bits");

tensaoA0 = (div(A0) * 5) / 1024.0;
tensaoA0 *= 8.4;
display.setCursor(0, lh*3);
display.print("Tensao: ");
display.print(tensaoA0);
display.print(" V");

display.setCursor(0, lh*4);
display.print(sensor.read());
display.print(" cm");

display.display();


Serial.print("Leitura: ");
Serial.print(leitura, BIN);
Serial.print("Bits / ");
Serial.print("Tensão: ");
Serial.print(tensaoA0);
Serial.print("V / ");
Serial.print(sensor.read());
Serial.println("cm");

}

float div(uint8_t A0) {
  float total=0;  
  for (int i = 0; i < 12; i++){
    total += 1.0 * analogRead(A0);
    delay(5);
  }
  return total / (float)12;
}  

// Inicio das funções, para cada caso, totalizando 6 funções diferente
void mot1_anti(int velo) // Função para o motor da esquerda girar no sentido anti horario com a velocidade variavel
{
  analogWrite(mot_in1, velo);
  analogWrite(mot_in2, 0);
}
void mot1_hor(int velo) // Função para o motor da esquerda girar no sentido horario com a velocidade variavel
{
  analogWrite(mot_in1, 0);
  analogWrite(mot_in2, velo);
}
void mot1_par() // Função para o motor da esquerda ficar parado
{
  analogWrite(mot_in1, 0);
  analogWrite(mot_in2, 0);
}

void mot2_anti(int velo) // Função para o motor da direita girar no sentido anti horario com a velocidade variavel
{
  analogWrite(mot_in3, 0);
  analogWrite(mot_in4, velo);
}
void mot2_hor(int velo) // Função para o motor da direita girar no sentido horario com a velocidade variavel
{
  analogWrite(mot_in3, velo);
  analogWrite(mot_in4, 0);
}
void mot2_par() // Função para o motor da direita ficar parado
{
  analogWrite(mot_in3, 0);
  analogWrite(mot_in4, 0);
}

char *binString(unsigned short n)
{
    static char bin[17];
    int x;

    for(x=0;x<16;x++)
    {
        bin[x] = n & 0x8000 ? '1' : '0';
        n <<= 1;
    }
    bin[16] = '\0';

    return(bin);
}
