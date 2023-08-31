#ifndef _FUNCOES_VARIAVEIS_H
#define _FUNCOES_VARIAVEIS_H
#include <Ultrasonic.h>  //Incluindo a biblioteca do ultrasonic de erik simoes
#include <Servo.h>
#include <Encoder.h>

// Definindo as portas dos sensores e da portas H
#define s_oeste 22     // , OUT1
#define s_noroeste 24  // , OUT2
#define s_norte 27     // , OUT3
#define s_nordeste 25  // , OUT4
#define s_leste 26     // , OUT5

// Motor 1 = Esquerda; Motor 2 = Direita; mot1 que tem encoder
#define mot_in1 12 // amarelo, direita, tras
#define mot_in2 11  // marrom, direita, frente
#define mot_in3 10  // azul, esquerda, frente
#define mot_in4 9   // verde e amarelo, esquerda, tras

// Definindo portas para o sensor de cor
//#define led_r 98       // Led vermelho para o sensor de coer
#define led_g 29      // Led verde para o sensor de cor
//#define led_b 99     // Led azul para o sensor de cor
//#define led_g_meio 36  // Led para o meio
#define esq A0         // Sensor que fica na esq
#define dir A1         // Sensor que fica na dir
//#define meio A8  // sensor que fica apontado pra frente no meio
bool ver = false;     
int m_esq = 0;         // Declarando o map e constrain do sensor
int m_dir = 0;
//int m_meio = 0;

#define esq_branco 700  // Valor para verificar se e branco ou nao
#define dir_branco 700
//#define meio_branco 50

//#define esq_cinza 500  // 900 DEU CERTO O VERDE; amtes = 430
//#define dir_cinza 500  // 900 DEU CERTO O VERDE; amtes = 220

//#define esq_verde 433  // 880 DEU CERTO O VERDE; amtes = cinza - 10
//#define dir_verde 215  // 880 DEU CERTO O VERDE; amtes = cinza - 10

// Definindo velocidades e inclinação
int vel_esq;  // PWM usado para a velocidade, min == 0 e max == 255
int vel_dir;  // 
#define incli A14
//#define tg 3000
//bool incli_ant;
//int millis_ant;
//#define vel_esq_p 100  //
//#define vel_esq_g 220  // Valores para um sistema de ir so pra frente
//#define vel_dir_p 80   //
//#define vel_dir_g 200  //

// Valor para encoders
Encoder enc(3, 2); //Encoder do motor da esquerda
int enc_ant = 0;     // Valor do encoder anterior
#define enc_fre 250  // Frente apos ver 90 ou encruzilhada / antes era 250 no erik / 98
#define enc_fre_encru 250
#define enc_90 678 
#define enc_peq 150  // Valor que vira para completar com while / antesta tava 200 no erik / 220 -230
#define enc_pas 180   // Valor que vai para atras / antes tava 80 no erik / 80
#define enc_pas_encru 180
#define enc_pas_outro 40
#define enc_180 1256
//#define enc_90_p 560
//#define enc_fre_sala3 500
//#define enc_pas_p 10
//#define enc_gang 900
//#define enc_ramp 900

Ultrasonic ult_meio(30, 31);  // trig == prim; echo == segun | trig = marrom e ech = amarelo

/* Valores para a sala 3
bool sala3 = false;
bool sala3_ver = false;
int conta;
#define conta_max 10
int ult_esq = 0;
int ult_dir = 0;
Servo servo_cacamba;
Servo servo_garra;
//servo_cacamba.attach(8);
//servo_garra.attach(7);
#define perto 5         // Valor para ficar perto o suficente
#define perto_garra 10  // Valor para caso a garra estiver decida
#define esq_switch 51
#define dir_switch 53
int pos = 0;
int pos_ant;
#define servo_delay 2
#define garra_cima 160  // talvez valores invertidos
#define garra_meio 130
#define garra_baixo 35  // esse tbm
#define cacamba_aberta 170
#define cacamba_fechada 40*/

// Inicio das funções, para cada caso
void mot1_anti(int velo)  // Função para o motor da esquerda girar no sentido anti horario com a velocidade variavel
{
  analogWrite(mot_in4, velo);
  analogWrite(mot_in3, 0);
}
void mot1_hor(int velo)  // Função para o motor da esquerda girar no sentido horario com a velocidade variavel
{
  analogWrite(mot_in4, 0);
  analogWrite(mot_in3, velo);
}
void mot1_par()  // Função para o motor da esquerda ficar parado
{
  analogWrite(mot_in4, 0);
  analogWrite(mot_in3, 0);
}

void mot2_anti(int velo)  // Função para o motor da direita girar no sentido anti horario com a velocidade variavel
{
  analogWrite(mot_in2, 0);
  analogWrite(mot_in1, velo);
}
void mot2_hor(int velo)  // Função para o motor da direita girar no sentido horario com a velocidade variavel
{
  analogWrite(mot_in2, velo);
  analogWrite(mot_in1, 0);
}
void mot2_par()  // Função para o motor da direita ficar parado
{
  analogWrite(mot_in1, 0);
  analogWrite(mot_in2, 0);
}

void sensi() {
  m_esq = map(constrain(analogRead(esq), 548, 792), 548, 792, 0, 1023);
  m_dir = map(constrain(analogRead(dir), 422, 648), 422, 648, 0, 1023);
}

void desv(int velo_esq, int velo_dir)  // Função para o robo desviar pela direita o obstaculo
{
  mot1_par();
  mot2_par();
  delay(200);
  enc_ant = enc.read();
  while (enc_ant - enc.read() <= enc_90) { // virando esquerda
    mot1_anti(velo_esq);
    mot2_hor(velo_dir);
    Serial.print("girando 90 para esquerda");
    Serial.println(enc.read());
  }
  enc_ant = enc.read();// indo frente
  while (enc.read() - enc_ant <= 1100) {
    mot1_hor(velo_esq);
    mot2_hor(velo_dir);
    Serial.print("andando na frente");
    Serial.println(enc.read());
  }
  enc_ant = enc.read();
  while (enc.read() - enc_ant <= enc_90 + 40) {
    mot1_hor(velo_esq);
    mot2_anti(velo_dir);
    Serial.print("virando direita");
    Serial.println(enc.read());
  }
  enc_ant = enc.read(); // passando por tudo
  while (enc.read() - enc_ant <= 1600) {
    mot1_hor(velo_esq);
    mot2_hor(velo_dir);
    Serial.print("andando na frente");
    Serial.println(enc.read());
  }
  enc_ant = enc.read(); // virando direita
  while (enc.read() - enc_ant <= enc_90 + 70) {
    mot1_hor(velo_esq);
    mot2_anti(velo_dir);
    Serial.print("virando direita");
    Serial.println(enc.read());
  }
  enc_ant = enc.read();
  while (enc.read() - enc_ant <= 600) { // Se ajeitando na faixa
    mot1_hor(velo_esq);
    mot2_hor(velo_dir);
    Serial.print("andando na frente");
    Serial.println(enc.read());
  }
  while(digitalRead(s_norte) == 1)
  {
    mot1_hor(velo_esq);
    mot2_hor(velo_dir);
    Serial.print("andando para frente");
    Serial.println(enc.read());
  }
  enc_ant = enc.read();
  while (enc.read() - enc_ant <= enc_peq) { // Se ajeitando na faixa
    mot1_hor(velo_esq);
    mot2_hor(velo_dir);
    Serial.print("andando na frente");
    Serial.println(enc.read());
  }
  while(digitalRead(s_norte) == 1) // Se ajeitando na faixa
  {
    mot1_anti(velo_esq);
    mot2_hor(velo_dir);
    Serial.print("girando 90 para esquerda");
    Serial.println(enc.read());
  }
}

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
    while (digitalRead(s_norte) == 1) {
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
    while (digitalRead(s_norte) == 1) {
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
  {
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
}

void esq_90() {
  enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_fre) {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
    }

  if ((m_esq <= esq_branco) & (m_dir >= dir_branco))  // Tem 1 quadrado verde na esquerda
  {
    Serial.println("leitura == 1100; tem verde");

    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_peq) {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Virando pra esquerda: ");
      Serial.println(enc.read());
    }
    while (digitalRead(s_norte) == 1) {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Virando pra esquerda: ");
      Serial.println(enc.read());
    }
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas) {
      mot1_anti(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Indo para tras: ");
      Serial.println(enc.read());
    }
  } else  // Nao tem quadrado verde
  {
    Serial.println("Leitura == 1100; nao tem verde");

    if (digitalRead(s_norte) == 1) {
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_peq) {
        mot1_anti(vel_esq);
        mot2_hor(vel_dir);
        Serial.print("Virando pra esquerda: ");
        Serial.println(enc.read());
      }
      while (digitalRead(s_norte) == 1) {
        mot1_anti(vel_esq);
        mot2_hor(vel_dir);
        Serial.print("Virando pra esquerda: ");
        Serial.println(enc.read());
      }
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas) {
        mot1_anti(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("Indo para tras: ");
        Serial.println(enc.read());
      }
    }
  }
}

void dir_90() {
  enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_fre) {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
    }
  if ((m_esq >= esq_branco) & (m_dir <= dir_branco))  // Tem 1 quadrado verde na direita
  {
    Serial.println("leitura == 0011; Tem verde");

    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_peq) {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Virando para direita: ");
      Serial.println(enc.read());
    }
    while (digitalRead(s_norte) == 1) {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Virando para direita: ");
      Serial.println(enc.read());
    }
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas) {
      mot1_anti(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Indo para tras: ");
      Serial.println(enc.read());
    }
  } else  // Nao tem quadrado verde
  {
    Serial.println("Leitura == 0011; nao tem verde");

    if (digitalRead(s_norte) == 1) {
      enc_ant = enc.read();
      while (enc.read() - enc_ant <= enc_peq) {
        mot1_hor(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("Virando para direita: ");
        Serial.println(enc.read());
      }
      while (digitalRead(s_norte) == 1) {
        mot1_hor(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("Virando para direita: ");
        Serial.println(enc.read());
      }
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas) {
        mot1_anti(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("Indo para tras: ");
        Serial.println(enc.read());
      }
    }
  }
}
#endif
