/* Incluindo as bibliotecas necessarias para o Oled
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
*/

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
int pinos[] = {8, 10, 11, 12, 13, 9, 6, 5, 3};

int j = 150;

/* Configurando o display, criando classe chamado dis com as especificações do display
Adafruit_SSD1306 dis(128, 64, &Wire, -1);
*/

void setup()
{
  // Colocando os sensores como INPUT, e o resto como OUTPUT
  for (int i = 0; i < 5; i++)
    pinMode(pinos[i], INPUT);
  for (int i = 5; i < 9; i++)
    pinMode(pinos[i], OUTPUT);
  Serial.begin(9600);
/*
  dis.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Inicio de qualquer display, o medelo do Oled é SSD1306, "0x3c" é inmudavel
  dis.clearDisplay();                    // Limpar o display, tambem inicio de qualquer display
  dis.setTextSize(3);                    // Colocando a fonte do tamanho
  dis.setTextColor(WHITE);               // Colocando a cor do texto
  dis.setCursor(0, 0);                   // Escolhendo onde usar o cursor (quando dar clear ele coloca automaticamente no 0,0)
 */
}
/*
float div(uint8_t A0) {
  float total=0;  
  for (int i = 0; i < 12; i++){
    total += 1.0 * analogRead(A0);
    delay(5);
  }
  return total / (float)12;
}
*/

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

void loop()
{
  /*
  dis.print("O\tNO\tN\tNE\tE");
  for (int i = 0; i < 5; i++)
  {
    dis.print(pinos[i]);
    dis.print("\t");
  }
  dis.display();
  */
  /*
  float tensaoA0 = (div(A0) * 5) / 1024.0;
  tensaoA0 *= 8.4;
  Serial.print("Tensão: ");
  Serial.println(tensaoA0);
  */
 
  byte leitura = 0; // Definir sempre 0 quando definir algo como o for abaixo
  for (int i = 0; i < 5; i++)
    leitura |= digitalRead(pinos[i]) << i; // Colocando as entrada da tabela da verdade usando um bitshift automatico
  leitura = (~leitura) & (0b00011111); // Colocando um inversor para que funcione com a tabela da verdade, AND uma mascara para ir so os bits que eu quero  
  Serial.println(leitura, BIN);   

  // Condições que usa a tabela da verdade, consultar para ver
  if (leitura == 0b00000) // Condição 1
  {
    mot1_hor(j);
    mot2_hor(j);
  }
  else if (leitura == 0b00001) // Condição 2
  {
    mot1_hor(j);
    mot2_anti(j);
  }
  else if (leitura == 0b00010) // Condição 3
  {
    mot1_hor(j);
    mot2_anti(j);
  }
  else if (leitura == 0b00011) // Condição 4
  {
    mot1_hor(j);
    mot2_anti(j);
  }
  else if (leitura == 0b00100) // Condição 5
  {
    mot1_hor(j);
    mot2_hor(j);
  }
  else if (leitura == 0b00101) // Condição 6
  {
  }
  else if (leitura == 0b00110) // Condição 7
  {
    mot1_hor(j);
    mot2_anti(j);
  }
  else if (leitura == 0b00111) // Condição 8
  {
    mot1_hor(j); // Ver. frente
    mot2_anti(j);
  }
  else if (leitura == 0b01000) // Condição 9
  {
    mot1_anti(j);
    mot2_hor(j);
  }
  else if (leitura == 0b01001) // Condição 10
  {
    mot1_anti(j);
    mot2_hor(j);
  }
  else if (leitura == 0b01010) // Condição 11
  {
    mot1_hor(j);
    mot2_hor(j);
  }
  else if (leitura == 0b01011) // Condição 12
  {
    mot1_hor(j);
    mot2_anti(j);
  }
  else if (leitura == 0b01100) // Condição 13
  {
    mot1_anti(j);
    mot2_hor(j);
  }
  else if (leitura == 0b01101) // Condição 14
  {
  }
  else if (leitura == 0b01110) // Condição 15
  {
    mot1_hor(j);
    mot2_hor(j);
  }
  else if (leitura == 0b01111) // Condição 16
  {
    mot1_hor(j);
    mot2_anti(j);
  }
  else if (leitura == 0b10000) // Condição 17
  {
    mot1_anti(j);
    mot2_hor(j);
  }
  else if (leitura == 0b10001) // Condição 18
  {
 
  }
  else if (leitura == 0b10010) // Condição 19
  {
    mot1_hor(j);
    mot2_anti(j);
  }
  else if (leitura == 0b10011) // Condição 20
  {
    mot1_hor(j);
    mot2_anti(j);
  }
  else if (leitura == 0b10100) // Condição 21
  {
    mot1_hor(j);
    mot2_hor(j);
  }
  else if (leitura == 0b10101) // Condição 22
  {
    mot1_hor(j);
    mot2_hor(j);
  }
  else if (leitura == 0b10110) // Condição 23
  {
  }
  else if (leitura == 0b10111) // Condição 24
  {
    mot1_hor(j);
    mot2_anti(j);
  }
  else if (leitura == 0b11000) // Condição 25
  {
    mot1_anti(j);
    mot2_hor(j);
  }
  else if (leitura == 0b11001) // Condição 26
  {
    mot1_anti(j);
    mot2_hor(j);
  }
  else if (leitura == 0b11010) // Condição 27
  {
    mot1_anti(j);
    mot2_hor(j);
  }
  else if (leitura == 0b11011) // Condição 28
  {
  }
  else if (leitura == 0b11100) // Condição 29
  {
    mot1_anti(j);
    mot2_hor(j);
  }
  else if (leitura == 0b11101) // Condição 30
  {
    mot1_anti(j);
    mot2_hor(j);
  }
  else if (leitura == 0b11110) // Condição 31
  {
    mot1_anti(j);
    mot2_hor(j);
  }
  else if (leitura == 0b11111) // Condição 32
  {

  }
}

/***********************************************
Tem que ajeitar a tabela da verdade
// 0b00100. ~0b00000100 & 0b00011111
// x & 1 = x; x & 0 = 0;

https://circuitdigest.com/microcontroller-projects/arduino-uno-line-follower-robot
***********************************************/

/***************************
int che_d(int vel0, int vel1, int temp)
{
bool res = false;
byte leitura;
delay(500);
mot_hor(vel0);
mot_anti(vel1);
delay(temp);
mot_par();
mot_par();
for(int i = 0; i < 5; i++) leitura |= digitalRead(pinos[i]) << i;
return leitura;
res = !res;
mot_anti(vel0);
mot_hor(vel1);
delay(temp);
}

byte leitura;
bool res;
if(res = false)
{
  byte leitura = 0; //Definir sempre 0 quando definir algo como o for abaixo
for(int i = 0; i < 5; i++) leitura |= digitalRead(pinos[i]) << i; //Colocando as entrada da tabela da verdade usando um bitshift automatico
}
******************************/
