#ifndef _FUNCOES_VARIAVEIS_H
#define _FUNCOES_VARIAVEIS_H

#include <Ultrasonic.h> //Incluindo a biblioteca do ultrasonic de erik simoes
#include <Encoder.h>

// Definindo as portas dos sensores e da portas H
#define s_oeste 4     // amarelo, OUT1
#define s_noroeste 8  // branco, OUT2
#define s_norte 11    // verde, OUT3
#define s_nordeste 12 // roxo, OUT4
#define s_leste 13    // verde, OUT5

// Motor 1 = Esquerda; Motor 2 = Direita; mot1 que tem encoder
#define mot_in1 10 // amarelo, direita, tras
#define mot_in2 5  // marrom, direita, frente
#define mot_in3 6  // azul, esquerda, frente
#define mot_in4 9  // verde e amarelo, esquerda, tras

// Definindo portas para o sensor de cor, o pin 7 e o led
#define led_g 7
#define esq A1
#define dir A0
int m_esq = 0;
int m_dir = 0;

#define esq_branco 700
#define dir_branco 700

#define esq_cinza 900 // 900 DEU CERTO O VERDE
#define dir_cinza 900 // 900 DEU CERTO O VERDE

#define esq_verde 880 // 880 DEU CERTO O VERDE
#define dir_verde 880 // 880 DEU CERTO O VERDE

#define vel_esq 130 // PWM usado para a velocidade, min == 0 e max == 255
#define vel_dir 110

int enc_ant = 0;
#define enc_fre 500
#define enc_90 540
#define enc_90_p 560
#define enc_peq 250
#define enc_pas 50

bool frente = false;
bool direita = false;
bool esquerda = false;

Ultrasonic sensor(A2, A3); // trig == 7; echo == 4 | trig = amarel e ech = marrm
Encoder enc(3, 2);

// Inicio das funções, para cada caso, totalizando 6 funções diferente
void mot1_anti(int velo) // Função para o motor da esquerda girar no sentido anti horario com a velocidade variavel
{
  analogWrite(mot_in4, velo);
  analogWrite(mot_in3, 0);
}
void mot1_hor(int velo) // Função para o motor da esquerda girar no sentido horario com a velocidade variavel
{
  analogWrite(mot_in4, 0);
  analogWrite(mot_in3, velo);
}
void mot1_par() // Função para o motor da esquerda ficar parado
{
  analogWrite(mot_in4, 0);
  analogWrite(mot_in3, 0);
}

void mot2_anti(int velo) // Função para o motor da direita girar no sentido anti horario com a velocidade variavel
{
  analogWrite(mot_in2, 0);
  analogWrite(mot_in1, velo);
}
void mot2_hor(int velo) // Função para o motor da direita girar no sentido horario com a velocidade variavel
{
  analogWrite(mot_in2, velo);
  analogWrite(mot_in1, 0);
}
void mot2_par() // Função para o motor da direita ficar parado
{
  analogWrite(mot_in1, 0);
  analogWrite(mot_in2, 0);
}

void sensi()
{
  m_esq = map(constrain(analogRead(esq), 350, 518), 350, 518, 0, 1023);
  m_dir = map(constrain(analogRead(dir), 169, 300), 169, 300, 0, 1023);
}

void desv_d(int velo) // Função para o robo desviar pela direita o obstaculo
{
  mot1_par();
  mot2_par();
  delay(200);
  enc_ant = enc.read();
  while (enc.read() - enc_ant <= enc_90)
  {
    mot1_hor(velo);
    mot2_anti(velo);
    Serial.print("girando 90");
    Serial.println(enc.read());
  }
  // while(digitalRead(s_norte) == 1){
  enc_ant = enc.read();
  while (enc.read() - enc_ant <= 1200)
  {
    mot1_hor(velo);
    mot2_hor(velo);
    Serial.print("andando na frente");
    Serial.println(enc.read());
  }
  enc_ant = enc.read();
  while (enc_ant - enc.read() <= enc_90)
  {
    mot1_anti(velo);
    mot2_hor(velo);
    Serial.print("girando 90 para esquerda");
    Serial.println(enc.read());
  }
  enc_ant = enc.read();
  while (enc.read() - enc_ant <= 1200)
  {
    mot1_hor(velo);
    mot2_hor(velo);
    Serial.print("andando na frente");
    Serial.println(enc.read());
  }
  enc_ant = enc.read();
  while (enc_ant - enc.read() <= enc_90)
  {
    mot1_anti(velo);
    mot2_hor(velo);
    Serial.print("girando 90 para esquerda");
    Serial.println(enc.read());
  }
  enc_ant = enc.read();
  while (enc.read() - enc_ant <= enc_fre)
  {
    mot1_hor(velo);
    mot2_hor(velo);
    Serial.print("andando na frente");
    Serial.println(enc.read());
  }
  //}
}

void encruzilhada()
{
  if ((m_esq <= esq_branco) & (m_dir >= dir_branco)) // Tem 1 quadrado verde na esquerda
  {
    Serial.println("Encruzilhada; Verde na esquerda");
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_fre)
    {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
    }

    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_peq)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("virando para esquerda");
      Serial.println(enc.read());
    }
    while (digitalRead(s_norte) == 1)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
    }
    delay(100);
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Indo para tras: ");
      Serial.println(enc.read());
    }
  }
  else if ((m_esq >= esq_branco) & (m_dir <= dir_branco)) // Tem 1 quadrado verde na direita
  {
    Serial.println("Encruzilhada; Verde na direita");
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_fre)
    {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
    }

    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_peq)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Virando para direita");
      Serial.println(enc.read());
    }
    while (digitalRead(s_norte) == 1)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
    }
    delay(100);
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Indo para tras: ");
      Serial.println(enc.read());
    }
  }
  else if ((m_esq >= esq_branco) & (m_dir >= dir_branco)) // Nao tem quadrado verde
  {
    Serial.println("Encruzilhada; Nao tem verde");
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_fre)
    {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
    }
  }
  else // Tem 2 quadrado verde
  {
    Serial.println("Encruzilhada; 2 verdes");
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_90 * 2)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("dando 180");
      Serial.println(enc.read());
    }
  }
}

void esq_90()
{
  if ((m_esq <= esq_branco) & (m_dir >= dir_branco)) // Tem 1 quadrado verde na esquerda
  {
    Serial.println("leitura == 1100; tem verde");
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_fre)
    {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
    }

    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_peq)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("virando pra esquerda");
      Serial.println(enc.read());
    }
    while (digitalRead(s_norte) == 1)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("virando pra esquerda");
    }
    delay(100);
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Indo para tras: ");
      Serial.println(enc.read());
    }
  }
  else // Nao tem quadrado verde
  {
    Serial.println("leitura == 1100; nao tem verde");
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_fre)
    {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
    }

    if (digitalRead(s_norte) == 1)
    {
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_peq)
      {
        mot1_anti(vel_esq);
        mot2_hor(vel_dir);
        Serial.print("virando pra esquerda");
        Serial.println(enc.read());
      }
      while (digitalRead(s_norte) == 1)
      {
        mot1_anti(vel_esq);
        mot2_hor(vel_dir);
        Serial.print("virando pra esquerda");
      }
      delay(100);
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas)
      {
        mot1_anti(vel_esq);
        mot2_hor(vel_dir);
        Serial.print("Indo para tras: ");
        Serial.println(enc.read());
      }
    }
  }
}

void dir_90()
{
  if ((m_esq >= esq_branco) & (m_dir <= dir_branco)) // Tem 1 quadrado verde na direita
  {
    Serial.println("leitura == 0011; Tem verde");
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_fre)
    {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
    }

    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_peq)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("virando para direita");
      Serial.println(enc.read());
    }
    while (digitalRead(s_norte) == 1)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("virando para direita");
    }
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Indo para tras: ");
      Serial.println(enc.read());
    }
  }
  else // Nao tem quadrado verde
  {
    Serial.println("Leitura == 0011; nao tem verde");
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_fre)
    {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
    }

    if (digitalRead(s_norte) == 1)
    {
      enc_ant = enc.read();
      while (enc.read() - enc_ant <= enc_peq)
      {
        mot1_hor(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("virando para direita");
        Serial.println(enc.read());
      }
      while (digitalRead(s_norte) == 1)
      {
        mot1_hor(vel_esq);
        mot2_anti(vel_dir);
      }
      delay(100);
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas)
      {
        mot1_anti(vel_esq);
        mot2_hor(vel_dir);
        Serial.print("Indo para tras: ");
        Serial.println(enc.read());
      }
    }
  }
}

void identif()
{
  enc_ant = enc.read();
  while (enc.read() - enc_ant <= enc_fre)
  {
    mot1_hor(vel_esq);
    mot2_hor(vel_dir);
  }

  mot1_par();
  mot2_par();
  delay(1000);

  if (digitalRead(s_norte) == 0)
    frente = true;
  Serial.print("valor do frente: ");
  Serial.println(frente);
  delay(2000);
  Serial.println(enc.read()); //532
  enc_ant = enc.read();/*
  while ((enc.read() - enc_ant >= enc_90) || (enc.read() - enc_ant <= enc_90_p))
  {
    if(enc.read() - enc_ant >= enc_90)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      if (digitalRead(s_leste) == 0)
      {
        direita = true;
      }
      Serial.print("dando 90 ");
      Serial.println(enc.read());
    }
    else if(enc_ant - enc.read() <= enc_90_p)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("voltando 90 ");
      Serial.println(enc.read());
    }
  }*/

  while((enc.read() - enc_ant <= enc_90) || (enc.read() - enc_ant >= enc_90_p)){
    if(enc.read() - enc_ant <= enc_90){
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("dando 90 ");
      Serial.println(enc.read());
    }
    else if(enc.read() - enc_ant >= enc_90_p){
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("voltando 90 ");
      Serial.println(enc.read());
    }
  }
  // IR PARA DIREITA UM POUCO, E CASO JA TER VISTO O PRETO IR DIRETO PARA ESQUERDA, EM BASE DE QUANTO ELE FOI PELA DIREITA

  mot1_par();
  mot2_par();
  Serial.print("valor do direita: ");
  Serial.println(direita);
  delay(2000);

  enc_ant = enc.read();
  while (enc.read() - enc_ant <= enc_90)
  {
    mot1_hor(vel_esq);
    mot2_anti(vel_dir);
    Serial.print("dando 180");
    Serial.println(enc.read());
  }

  enc_ant = enc.read();
  while (enc.read() - enc_ant <= enc_90)
  {
    mot1_hor(vel_esq);
    mot2_anti(vel_dir);
    if (digitalRead(s_leste) == 0)
      esquerda = true;
    Serial.print("dando 180");
    Serial.println(enc.read());
  }

  mot1_par();
  mot2_par();
  Serial.print("valor do esquerda: ");
  Serial.println(esquerda);
  delay(2000);

  enc_ant = enc.read();
  while (enc.read() - enc_ant <= enc_90)
  {
    mot1_hor(vel_dir);
    mot2_anti(vel_dir);
    Serial.print("Virando para direita");
    Serial.println(enc.read());
  }

  if ((frente == true & esquerda == true & direita == false) || (frente == false & esquerda == true & direita == false))
  {
    esq_90();
  }
  else if ((frente == true & esquerda == false & direita == true) || (frente == false & esquerda == false & direita == true))
  {
    dir_90();
  }
  else
  {
    encruzilhada();
  }
}
#endif