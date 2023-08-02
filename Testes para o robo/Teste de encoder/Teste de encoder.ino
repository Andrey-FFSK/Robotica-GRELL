#include <Encoder.h>

// Motor 1 = Direita; Motor 2 = Esquerda
#define mot_in1 10 // amarelo, direita, tras
#define mot_in2 5 // marrom, direita, frente
#define mot_in3 6 // azul, esquerda, frente
#define mot_in4 9 // verde e amarelo, esquerda, tras

Encoder enc(3,2);
const int j = 180;
int enc_ant = 0;

void setup() {

  Serial.begin(9600);
}

void loop() {
      while(enc.read() - enc_ant <= 200){
      mot1_hor(j);
      mot2_hor(j);
      Serial.println(enc.read());
      }
      mot1_par();
      mot2_par();

  /*
  while(enc.read() <= 627){
    mot1_anti(j);
    mot2_hor(j);
  Serial.println(enc.read());
  }
  while(enc.read() >= 629){
    mot2_anti(j);
    mot1_hor();
  }*/
  Serial.println(enc.read());
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