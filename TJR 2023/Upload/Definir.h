#ifndef _FUNCOES_VARIAVEIS_H
#define _FUNCOES_VARIAVEIS_H
#include "Declarar.h"
#include <Ultrasonic.h>
#include <Encoder.h>
// mpu6050 i2c = 0x68

//* Definindo as portas dos sensores
#define s_oeste 22     //
#define s_noroeste A15 //
#define s_norte 27     //
#define s_nordeste A14 //
#define s_leste 26     //
#define analog_esq 501 // Valor que serve o quanto ele ver o cinza no micro ajuste
#define analog_dir 501 // =

//* Motor 1 = Esquerda; Motor 2 = Direita; mot1 que tem encoder
#define mot_in1 12 // amarelo, direita, tras
#define mot_in2 11 // marrom, direita, frente
#define mot_in3 10 // azul, esquerda, frente
#define mot_in4 9  // verde e amarelo, esquerda, tras

//* Definindo portas para o sensor de cor
#define led_g 29  // Led verde para o sensor de cor
#define esq A0    // Sensor que fica na esq
#define dir A1    // Sensor que fica na dir
bool ver = false; // O Verifica para os switchs
int m_esq = 0;    // Declarando o map e constrain do sensor
int m_dir = 0;

#define esq_branco 700 // Valor para verificar se e branco ou nao
#define dir_branco 700

//* Definindo velocidades
#define vel_esq 140 // PWM usado para a velocidade, min == 0 e max == 255
#define vel_dir 130 //
#define mot_par 50  // Delay para o tempo dele ficar parado

//* Valores com Millis
// int millis_ant = 0;
// #define time_if 8000
// #define time_while 1500

//* Valores para encoders
Encoder enc(3, 2);       // Encoder do motor da esquerda
int enc_ant = 0;         // Valor do encoder anterior
#define enc_fre 140      // Frente apos ver 90 / 170 / 150
#define enc_peq 130      // Valor que vira para completar com while /
#define enc_pas 70       // Valor que vai para atras /
#define enc_pas_outro 40 // Valor que vai para atras na passagem ver /
#define enc_passo 10
// #define enc_fre_encru 200
// #define enc_pas_encru 100
// #define enc_180 1256

//* Valor para verificação de branco
int enc_ant_verb = 0;
bool verb_d = false;
bool verb_e = false;
#define enc_verb_fren 140
#define enc_verb_90 585
#define enc_verb_90_2 enc_verb_90 + 50
// #define enc_verb_90_3 enc_90 - 170
#define enc_verb_gap 1000

//* Valores para desviar obstaculo
int cont_desv = 0;
#define max_cont_desv 99 // Valor de quantidade de obstaculos
#define enc_peq_desv 180
#define frente_1 1100 // Valor que ele se distancia do obstaculo
#define frente_2 1800 // Valor que faz ele ultrapassar o obstaculo
#define frente_3 600  // Valor que faz ele nao se perder em qualquer linha
#define enc_90 580
#define enc_90_2 enc_90 + 50  // Seguunda vez que ele executa o 90 / 70
#define enc_90_3 enc_90 + 110 // E a terceira / 140

Ultrasonic ult_meio(30, 31); // trig == prim; echo == segun | trig = marrom e echo = amarelo

//* Inicio das funções, para cada caso
void mot1_anti(int velo = vel_esq)
{
  analogWrite(mot_in4, velo);
  analogWrite(mot_in3, 0);
}
void mot1_hor(int velo = vel_esq)
{
  analogWrite(mot_in4, 0);
  analogWrite(mot_in3, velo);
}
void mot1_par()
{
  analogWrite(mot_in4, 0);
  analogWrite(mot_in3, 0);
}

void mot2_anti(int velo = vel_dir)
{
  analogWrite(mot_in2, 0);
  analogWrite(mot_in1, velo);
}
void mot2_hor(int velo = vel_dir)
{
  analogWrite(mot_in2, velo);
  analogWrite(mot_in1, 0);
}
void mot2_par()
{
  analogWrite(mot_in1, 0);
  analogWrite(mot_in2, 0);
}

void enc_frente(int enc_valor = enc_passo, int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  enc_ant = enc.read();
  while (enc.read() - enc_ant <= enc_valor)
  {
    mot1_hor(velo_esq);
    mot2_hor(velo_dir);
    Serial.print("Indo frente: ");
    Serial.println(enc.read());
  }
}

void enc_direita(int enc_valor = enc_passo, int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  enc_ant = enc.read();
  while (enc.read() - enc_ant <= enc_valor)
  {
    mot1_hor(velo_esq);
    mot2_anti(velo_dir);
    Serial.print("Virando direita: ");
    Serial.println(enc.read());
  }
}

void enc_esquerda(int enc_valor = enc_passo, int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  enc_ant = enc.read();
  while (enc_ant - enc.read() <= enc_valor)
  {
    mot1_anti(velo_esq);
    mot2_hor(velo_dir);
    Serial.print("Virando esquerda: ");
    Serial.println(enc.read());
  }
}

void enc_re(int enc_valor = enc_passo, int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  enc_ant = enc.read();
  while (enc_ant - enc.read() <= enc_valor)
  {
    mot1_anti(velo_esq);
    mot2_anti(velo_dir);
    Serial.print("Indo atras: ");
    Serial.println(enc.read());
  }
}

void sensi()
{
  m_esq = map(constrain(analogRead(esq), 561, 795), 561, 795, 0, 1023);
  m_dir = map(constrain(analogRead(dir), 405, 629), 405, 629, 0, 1023);
}

void desv(bool esq_dir, int velo_esq = vel_esq, int velo_dir = vel_dir)
{
  enc_re(enc_pas_outro, velo_esq, velo_dir); //* Dando um passo para atras, isso e bom caso a traseira do robo e maior do que na frente
  mot1_par();                                //* Colocando pra parar bem rapido pq sim
  mot2_par();
  delay(mot_par);
  if (esq_dir == false)
  {
    enc_esquerda(enc_90, velo_esq, velo_dir); //* Girando para esquerda
    // Serial.println("false");
  }
  else
  {
    enc_direita(enc_90, velo_esq, velo_dir); //* Girando para direita
  }
  enc_frente(frente_1); //* Se distanciando do obstaculo
  Serial.println("frente feito");
  if (esq_dir == false)
  {
    enc_direita(enc_90_2, velo_esq, velo_dir); //* Virando para direita, com valor reduzido para nao girar demais
  }
  else
  {
    enc_esquerda(enc_90_2, velo_esq, velo_dir); //*Virando para esquerda, com valor reduzido para nao girar demais
  }
  enc_frente(frente_2, velo_esq, velo_dir); //* Passando do obstaculo
  if (esq_dir == false)
  {
    enc_direita(enc_90_3, velo_esq, velo_dir); //* Virando para direita, mesmo moitvo anterior
  }
  else
  {
    enc_esquerda(enc_90_3, velo_esq, velo_dir); //* Virando para esquerda, mesmo moitvo anterior
  }
  enc_frente(frente_3, velo_esq, velo_dir); //* Andando em frente, para ele nao se confundir linhas aleatorias
  while (digitalRead(s_norte) == 1)         //* Terminando com while para ele encontrar a linah correta
  {
    mot1_hor(velo_esq);
    mot2_hor(velo_dir);
    Serial.print("andando para frente: ");
    Serial.println(enc.read());
  }
  enc_frente(enc_peq_desv, velo_esq, velo_dir); //* Se afastando um pouco da linha
  if (esq_dir == false)
  {
    while (digitalRead(s_norte) == 1) //* Virando para direita para se ajeiar na faixa
    {
      mot1_anti(velo_esq);
      mot2_hor(velo_dir);
      Serial.print("Virando direita: ");
      Serial.println(enc.read());
    }
  }
  else
  {
    while (digitalRead(s_norte) == 1) //* Virando para esquerda para se ajeiar na faixa
    {
      mot1_hor(velo_esq);
      mot2_anti(velo_dir);
      Serial.print("Virando esquerda: ");
      Serial.println(enc.read());
    }
  }
}

void esq_90()
{
  enc_frente(enc_fre);
  enc_esquerda(enc_peq);
  //while (((analogRead(s_noroeste) >= analog_esq) || (analogRead(s_nordeste) >= analog_dir)) && digitalRead(s_oeste) == 1)
  while ((digitalRead(s_norte) == 1) && (digitalRead(s_oeste) == 1))
  {
    mot1_anti();
    mot2_hor();
  }
  enc_re(enc_pas);
}

void dir_90()
{
  enc_frente(enc_fre);
  enc_direita(enc_peq);
  //while (((analogRead(s_noroeste) >= analog_esq) || (analogRead(s_nordeste) >= analog_dir)) && digitalRead(s_leste) == 1)
  while ((digitalRead(s_norte) == 1) && (digitalRead(s_leste) == 1))
  {
    mot1_hor();
    mot2_anti();
  }
  enc_re(enc_pas);
}

void ver_branco()
{
  enc_frente(enc_verb_fren); // Passinho para frente, talvezs trocar para uma paradinha
  mot1_par();
  mot2_par();
  delay(mot_par);
  enc_ant_verb = enc.read();
  while ((enc.read() - enc_ant_verb <= enc_verb_90) && (digitalRead(s_norte) == 1)) // while para ele ir de passinho ate fazer um 90 verificando se o sensor pega uma linha preta
  {
    enc_direita();
    Serial.println();
    if (digitalRead(s_leste) == 0)
      verb_d = true;
    Serial.print("verb_d = ");
    Serial.println(verb_d);
    delay(10);
    mot1_par();
    mot2_par();
    delay(10);
  }
  mot1_par();
  mot2_par();
  delay(2000);

  if (verb_d == false)
  {
    enc_esquerda(enc_verb_90_2); // Voltando para ficar reto com a linha
    mot1_par();
    mot2_par();
    delay(2000);
    enc_ant_verb = enc.read();
    while (((enc.read() - enc_ant_verb <= enc_verb_90) && (digitalRead(s_norte) == 1))) // while para ele ir de passinho ate fazer um 90 verificando se o sensor pega uma linha preta
    {
      enc_esquerda();
      if (digitalRead(s_oeste) == 0)
        verb_e = true;
      Serial.print("verb_e = ");
      Serial.println(verb_e);
      delay(10);
      mot1_par();
      mot2_par();
      delay(10);
    }
    mot1_par();
    mot2_par();
    delay(2000);
    if (verb_e == false)
    {
      enc_direita(enc_verb_90_2); // Voltando para ficar reto na linha, pode ser que coloque a versao 3
      enc_frente(enc_verb_gap);   // Apos verificar tudo, imaginando que e um gap entao ultrapassando
    }
  }
}

/*
void encruzilhada() {
  enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_fre_encru) {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
    }

  if ((m_esq <= esq_branco) & (m_dir >= dir_branco))  // Tem 1 quadrado verde na esquerda
  {
    Serial.println("Encruzilhada; Verde na esquerda");

    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_peq) {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Virando para esquerda: ");
      Serial.println(enc.read());
    }
    while ((digitalRead(s_norte) == 1) && (digitalRead(s_oeste) == 1)) {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Virando para esquerda: ");
      Serial.println(enc.read());
    }

    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas_encru) {
      mot1_anti(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Indo para tras: ");
      Serial.println(enc.read());
    }
  } else if ((m_esq >= esq_branco) & (m_dir <= dir_branco))  // Tem 1 quadrado verde na direita
  {
    Serial.println("Encruzilhada; Verde na direita");

    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_peq) {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Virando para direita: ");
      Serial.println(enc.read());
    }
    while ((digitalRead(s_norte) == 1) && (digitalRead(s_leste) == 1)) {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Virando para direita: ");
      Serial.println(enc.read());
    }

    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas_encru) {
      mot1_anti(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Indo para tras: ");
      Serial.println(enc.read());
    }
  } else if ((m_esq >= esq_branco) & (m_dir >= dir_branco))  // Nao tem quadrado verde
  {
    Serial.println("Encruzilhada; Nao tem verde");
  } else  // Tem 2 quadrado verde
  { /*
    enc_ant = enc.read(); // Fazendo o maior percuso com encoder
    while (enc.read() - enc_ant <= enc_180) {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Virando para direita: ");
      Serial.println(enc.read());
    }
    while(digitalRead(s_norte) == 1) // Termiando com while para se endireitar na faixa
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Virando para direita: ");
      Serial.println(enc.read());
    }
  }
}*/
#endif
