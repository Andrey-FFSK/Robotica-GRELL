#ifndef _FUNCOES_VARIAVEIS_H
#define _FUNCOES_VARIAVEIS_H
#include <Ultrasonic.h> //Incluindo a biblioteca do ultrasonic de erik simoes
#include <Servo.h> 
#include <Encoder.h>


// Definindo as portas dos sensores e da portas H
#define s_oeste 22    // , OUT1
#define s_noroeste 24 // , OUT2
#define s_norte 27    // , OUT3
#define s_nordeste 25 // , OUT4
#define s_leste 26    // , OUT5

// Motor 1 = Esquerda; Motor 2 = Direita; mot1 que tem encoder
#define mot_in1 12 // amarelo, direita, tras
#define mot_in2 11 // marrom, direita, frente
#define mot_in3 10 // azul, esquerda, frente
#define mot_in4 9  // verde e amarelo, esquerda, tras

// Definindo portas para o sensor de cor
#define led_r 36      // Led vermelho para o sensor de coer
#define led_g 35      // Led verde para o sensor de cor
#define led_b 37      // Led azul para o sensor de cor
#define led_g_meio 44 // Led para o meio
#define esq A0        // Sensor que fica na esq
#define dir A1        // Sensor que fica na dir
#define meio A14      // sensor que fica apontado pra frente no meio
int m_esq = 0;        // Declarando o map e constrain do sensor
int m_dir = 0;
int m_meio = 0;

#define esq_branco 700 // Valor para verificar se e branco ou nao
#define dir_branco 700
#define meio_branco 700

#define esq_cinza 443 // 900 DEU CERTO O VERDE; amtes = 430
#define dir_cinza 225 // 900 DEU CERTO O VERDE; amtes = 220

#define esq_verde 433 // 880 DEU CERTO O VERDE; amtes = cinza - 10
#define dir_verde 215 // 880 DEU CERTO O VERDE; amtes = cinza - 10

// Definindo velocidades e inclinação
#define vel_esq 130   // PWM usado para a velocidade, min == 0 e max == 255
#define vel_dir 110   // PWM da direita
#define incli 52
#define vel_esq_p 100 //
#define vel_esq_g 220 // Valores para um sistema de ir so pra frente
#define vel_dir_p 80  //
#define vel_dir_g 200 //

// Valor para encoders
Encoder enc(3, 2);
int enc_ant = 0;    // Valor do encoder anterior
#define enc_fre 200 // Frente apos ver 90 ou encruzilhada / antes era 300
#define enc_90 900
#define enc_90_p 560
#define enc_peq 300 // Valor que vira para completar com while / antes tava 150 (acho)
#define enc_pas 30 // Valor que vai para atras / antes tava 100
#define enc_pas_p 10

// Variaveis tipo bool para indetif
bool frente = false;
bool direita = false;
bool esquerda = false;

Ultrasonic ult_meio(44, 45); // trig == prim; echo == segun | trig = amarelo e ech = marrom

// Valores para a sala 3
//Servo servo1;
servo1.attach(4);
#define perto 2 // Valor para ficar perto o suficente
#define perto_garra 10
#define esq_switch 51
#define dir_switch 53 // Valor para caso a garra esteja aberta
int pos = 0;
int pos_ant;
#define garra_aberta 10
#define garra_fechada 107
#define cacamba_aberta 107
#define cacamba_fechada 9 

// Inicio das funções, para cada caso
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
  m_esq = map(constrain(analogRead(esq), 578, 811), 578, 811, 0, 1023);
  m_dir = map(constrain(analogRead(dir), 420, 646), 420, 646, 0, 1023);
  m_meio = map(constrain(analogRead(dir), 135, 246), 135, 246, 0, 1023);
}

void cacamba_abrir()
{
  for(pos = pos_ant; pos <= cacamba_aberta; pos++){
    servo1.write(pos);
    delay(10);
    Serial.println("Caçamba - subindo");
  }
  pos_ant = pos;
}

void cacamba_fechar()
{
  for(pos = pos_ant; pos >= cacamba_fechada; pos--){
    servo1.write(pos);
    delay(10);
    Serial.println("Caçamba - decendo");
  }
  pos_ant = pos;
}

void garra_subir()
{
  for(pos = pos_ant; pos <= garra_aberta; pos++)
  {
    servo2.write(pos);
    delay(10);
    Serial.println("Garra - subindo");
  }
  pos_ant = pos;
}

void garra_descer()
{
  for(pos = pos_ant; pos >= garra_fechada; pos--)
  {
    servo2.write(pos);
    delay(10);
    Serial.println("Garra - decendo");
  }
  pos_ant = pos;
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
      Serial.print("Virando para esquerda: ");
      Serial.println(enc.read());
    }
    while (digitalRead(s_norte) == 1)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Virando para esquerda: ");
      Serial.println(enc.read());
    }
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas)
    {
      mot1_anti(vel_esq);
      mot2_anti(vel_dir);
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
      Serial.print("Virando para direita: ");
      Serial.println(enc.read());
    }
    while (digitalRead(s_norte) == 1)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Virando para direita: ");
      Serial.println(enc.read());
    }

    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas)
    {
      mot1_anti(vel_esq);
      mot2_anti(vel_dir);
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
      Serial.print("Indo para frente: ");
      Serial.println(enc.read());
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
      Serial.print("Virando pra esquerda: ");
      Serial.println(enc.read());
    }
    while (digitalRead(s_norte) == 1)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Virando pra esquerda: ");
      Serial.println(enc.read());
    }
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas)
    {
      mot1_anti(vel_esq);
      mot2_anti(vel_dir);
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
        Serial.print("Virando pra esquerda: ");
        Serial.println(enc.read());
      }
      while (digitalRead(s_norte) == 1)
      {
        mot1_anti(vel_esq);
        mot2_hor(vel_dir);
        Serial.print("Virando pra esquerda: ");
        Serial.println(enc.read());
      }
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas)
      {
        mot1_anti(vel_esq);
        mot2_anti(vel_dir);
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
      Serial.print("Virando para direita: ");
      Serial.println(enc.read());
    }
    while (digitalRead(s_norte) == 1)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Virando para direita: ");
      Serial.println(enc.read());
    }
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas)
    {
      mot1_anti(vel_esq);
      mot2_anti(vel_dir);
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
        Serial.print("Virando para direita: ");
        Serial.println(enc.read());
      }
      while (digitalRead(s_norte) == 1)
      {
        mot1_hor(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("Virando para direita: ");
        Serial.println(enc.read());
      }
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas)
      {
        mot1_anti(vel_esq);
        mot2_anti(vel_dir);
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
  Serial.println(enc.read()); // 532
  enc_ant = enc.read();       /*
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

  while ((enc.read() - enc_ant <= enc_90) || (enc.read() - enc_ant >= enc_90_p))
  {
    if (enc.read() - enc_ant <= enc_90)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("dando 90 ");
      Serial.println(enc.read());
    }
    else if (enc.read() - enc_ant >= enc_90_p)
    {
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

void identif_simpl()
{
  if((esquerda = true) && (direita = false))
  {
    esq_90();
  }
  else if((esquerda = false) && (direita = true))
  {
    dir_90();
  }
  else if((esquerda = true) && (direita = true))
  {
    encruzilhada();
  }
}
#endif

// Funções antigas
/*
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
    //digitalWrite(led_g, 1);
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_90)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("virando para esquerda");
      Serial.println(enc.read());
    }/*
    while (analogRead(esq) >= esq_cinza)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.println("virando pra esquerda parte 1 " + String(analogRead(esq)));

    }
    while (analogRead(esq) <= esq_cinza)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.println("virando pra esquerda parte 2 " + String(analogRead(esq)));
    }
    digitalWrite(led_g, 0);

    //delay(100);
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas)
    {
      mot1_anti(vel_esq);
      mot2_anti(vel_dir);
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
    while (analogRead(dir) >= dir_cinza)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("virando para direita");
    }
    while (analogRead(dir) <= dir_cinza)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("virando para direita");
    }
    delay(100);
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas)
    {
      mot1_anti(vel_esq);
      mot2_anti(vel_dir);
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
    while (analogRead(esq) >= esq_cinza)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("virando pra esquerda");
    }
    while (analogRead(esq) <= esq_cinza)
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
      mot2_anti(vel_dir);
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
      while (analogRead(esq) >= esq_cinza)
      {
        mot1_anti(vel_esq);
        mot2_hor(vel_dir);
        Serial.print("virando pra esquerda");
      }
      while (analogRead(esq) <= esq_cinza)
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
        mot2_anti(vel_dir);
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
    while (analogRead(dir) >= dir_cinza)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("virando para direita");
    }
    while (analogRead(dir) <= dir_cinza)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("virando para direita");
    }
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_pas)
    {
      mot1_anti(vel_esq);
      mot2_anti(vel_dir);
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
      while (analogRead(dir) >= dir_branco)
      {
        mot1_hor(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("virando para direita");
      }
      while (analogRead(dir) <= dir_cinza)
      {
        mot1_hor(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("virando para direita");
      }
      delay(100);
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas)
      {
        mot1_anti(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("Indo para tras: ");
        Serial.println(enc.read());
      }
    }
  }
}
*****/
