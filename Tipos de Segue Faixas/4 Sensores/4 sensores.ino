#include <Ultrasonic.h>

// Definindo as portas dos sensores e da portas H
#define s_oeste 8    // rosa, OUT1 
#define s_noroeste 13 // amarelo, OUT2
#define s_norte 12    // azul, OUT4
#define s_nordeste 11 // vermelho, OUT3                                 
#define s_leste 10    // marrom, OUT5

// Motor 1 = esquerda; Motor 2 = direita
#define mot_in1 3  // preto, esquerda, tras
#define mot_in2 5  // laranja, esquerda, frente
#define mot_in3 6  // branco, direita, frente
#define mot_in4 9 // amarelo, direita, tras

// Usando array para colocar todos os pinos, coloquei os sensores invertido por causa do BitSwift em baixo
int pinos[] = {10, 11, 13, 8, 12, 9, 6, 3, 5};

int j = 180;
Ultrasonic sensor(7, 4); //trig == 7; echo == 4


void setup()
{
  // Colocando os sensores como INPUT, e o resto como OUTPUT
  for (int i = 0; i < 5; i++)
    pinMode(pinos[i], INPUT);
  for (int i = 5; i < 9; i++)
    pinMode(pinos[i], OUTPUT);
    Serial.begin(9600);
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
void desv_d(int velo)
{
  mot1_par();
  mot2_par();
  delay(200);
  mot1_hor(velo);
  mot2_anti(velo);
  delay(800);
  //while(digitalRead(s_norte) == 1){
  mot1_hor(velo);
  mot2_hor(velo);
  delay(2100);
  mot1_anti(velo);
  mot2_hor(velo);
  delay(800);
  mot1_hor(velo);
  mot2_hor(velo);
  delay(2000);
  mot1_anti(velo);
  mot2_hor(velo);
  delay(800);
  //}
}

void loop()
{
  byte leitura = 0; // Definir sempre 0 quando definir algo como o for abaixo
  for (int i = 0; i < 4; i++)
    leitura |= digitalRead(pinos[i]) << i; // Colocando as entrada da tabela da verdade usando um bitshift automatico
  leitura = (~leitura) & (0b00001111); // Colocando um inversor para que funcione com a tabela da verdade, AND uma mascara para ir so os bits que eu quero
  Serial.print(leitura, BIN);
  Serial.print(" sens: ");
  Serial.println(sensor.read());

  if(sensor.read() <= 18){
    desv_d(j);
  }

  // Condições que usa a tabela da verdade, consultar para ver
  if (leitura == 0b0000) // Condição 1
  {
    mot1_hor(j);
    mot2_hor(j);
  }
  else if ((leitura == 0b0010) | (leitura == 0b0001)) // Condição 2
  {
    mot1_hor(j);
    mot2_anti(j);
  }
  else if (leitura == 0b0011) // Condição 4
  {
    mot1_hor(j);
    mot2_hor(j);
    delay(300);
    while(digitalRead(s_norte) == 1){
    mot1_hor(j);
    mot2_anti(j);
    }
    delay(200);
  }
  else if ((leitura == 0b0100) | (leitura == 0b1000)) // Condição 5
  {
    mot1_anti(j);
    mot2_hor(j); 
  }
  else if (leitura == 0b0110 | leitura == 0b1001) // Condição 6, LEMBRANDO DOS PARANTESES
  {
    mot1_par();
    mot2_par();
    delay(200);
  }
  else if (leitura == 0b1100) // Condição 7
  {
    mot1_hor(j);
    mot2_hor(j);
    delay(300);
    while(digitalRead(s_norte) == 1){
    mot1_anti(j);
    mot2_hor(j);
    }
    delay(200);
  }
  else // Condição 8
  {

  }
  /*
  LEMBRAR DAS VARIAVEIS COM ENCRUZILHADA
  COMO ELE VAI PARAR?
  */
}
