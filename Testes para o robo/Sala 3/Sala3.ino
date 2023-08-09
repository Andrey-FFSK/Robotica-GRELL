#include "Include.h"

const int pinos[] = {s_leste, s_nordeste, s_noroeste, s_oeste, s_norte, esq, dir, led_g, mot_in1, mot_in2, mot_in3, mot_in4};

#define perto 2
#define perto_garra 10

#define sensi_meio A3
#define meio_branco 700

#define vel_esq_p 100
#define vel_esq_g 220
#define vel_dir_p 80
#define vel_dir_g 200

int enc_atual = 0;
bool pos_esq = false;
bool pos_dir = false;
bool pos;

Ultrasonic ult_dir(A2, A3);
Ultrasonic ult_esq(A2, A3);

void setup()
{
    for (int i = 0; i < 7; i++)
        pinMode(pinos[i], INPUT);
    for (int i = 7; i < 12; i++)
        pinMode(pinos[i], OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    enc_ant = enc.read(); // Andando um pouco pra frante para resetar
    while (enc.read() - enc_ant <= enc_pas)
    {
        mot1_hor(velo);
        mot2_hor(velo);
        Serial.print("andando na frente");
        Serial.println(enc.read());
    }
    if (ult_esq.read() >= ult_dir.read()) // Vendo qual parte é mais perto dele
        pos = true;                       // ta mais perto da direita
    else
        pos = false; // ta mais perto da esquerda
    if (pos = false) // ajeitando para a função sala3_pas
    {
        enc_ant = enc.read();
        while (enc_ant - enc.read() <= enc_90)
        {
            mot1_anti(vel_esq);
            mot2_hor(vel_dir);
            Serial.print("girando 90 para esquerda");
            Serial.println(enc.read());
        }
    }
    else
    {
        enc_ant = enc.read();
        while (enc.read() - enc_ant <= enc_90)
        {
            mot1_hor(vel_esq);
            mot2_anti(vel_dir);
            Serial.print("Girando 90 para direita: ");
            Serial.println(enc.read());
        }
    }
    while (ult_meio.read() >= perto) // preparativo para a sala3_pas
    {
        mot1_hor(vel_esq);
        mot2_hor(vel_dir);
    }
    sala3_pas(); // ver função
    while (ult_meio.read() >= perto_garra)
    {
        mot1_hor(vel_esq);
        mot2_hor(vel_dir);
    }
    // fechar garra
    while (ult_meio.read() >= perto) // preparativo para a sala3_pas
    {
        mot1_hor(vel_esq);
        mot2_hor(vel_dir);
    }
    sala3_pas();

    /*
    sala3_frente();
    if (sensi_meio <= meio_branco) // chengando em uma parede na frente, podendo ser Area de resgate ou a parede mesmo
    {
        // Area de resgate
        if (pos_esq = true) // Esta no canto esquerdo
        {
            enc_ant = enc.read(); // uma curvinha para direita, e nao bater na area de resgate
            while (enc.read() - enc_ant <= enc_peq)
            {
                mot1_hor(vel_esq);
                mot2_anti(vel_dir);
            }
            while (ult_meio.read()>= perto) // Ficar encostado na parede que fica mais perto da esquerda
            {
                pos_esq = true;
                mot1_hor(vel_esq_p);
                mot2_hor(vel_dir_g);
            }
        }
        else // Esta no canto direito
        {
            enc_ant = enc.read(); // uma curvinha para esquerda, e nao bater na area de resgate
            while (enc_ant - eenc.read() <= enc_peq)
            {
                mot1_anti(vel_esq);
                mot2_hor(vel_dir);
            }
            while (ult_meio.read()>= perto) // Ficar encostado na parede que fica mais perto da direita
            {
                pos_esq = true;
                mot1_hor(vel_esq_g);
                mot2_hor(vel_dir_p);
            }
        }
    }
    else // Parede branca
    {
        // Fecha garra
        if (pos_esq = true) // Ele esta no canto da esquerda
        {
            enc_ant = enc.read();
            while (enc.read() - enc_ant <= enc_90)
            {
                mot1_hor(vel_esq);
                mot2_anti(vel_dir);
                Serial.print("Virando para direita");
                Serial.println(enc.read());
            }
        }
        else // Ele esta no canto da direita
        {
            enc_ant = enc.read();
            while (enc_ant - enc.read() <= enc_90)
            {
                mot1_anti(vel_esq);
                mot2_hor(vel_dir);
                Serial.print("virando para esquerda");
                Serial.println(enc.read());
            }
        }
    }*/
}

void sala3_frente(int dis, int temp)
{
    if (ult_esq.read() >= ult_dir.read()) // Vendo qual lado da parede ele estar
        while (ult_meio.read() >= perto)  // Ficar encostado na parede da esquerda
        {
            pos_esq = true;
            enc_ant = enc.read();
            while (enc.read() - enc_ant <= dis)
            {
                mot1_hor(vel_esq_p);
                mot2_hor(vel_dir_g);
            }
        }
    else
        while (ult_meio.read() >= perto) // Ficar encostado na parede da direita
        {
            pos_dir = true;
            enc_ant = enc.read();
            while (enc.read() - enc_ant <= dis)
            {
                mot1_hor(vel_esq_g);
                mot2_hor(vel_dir_p);
            }
        }
    mot1_par();
    mot2_par();
    delay(temp);
}

void sala3_pas() // Pos = false é esq; Pos = true é dir;
{
    if (pos = false)
    {
        enc_ant = enc.read();
        while (enc.read() - enc_ant <= enc_90)
        {
            mot1_hor(vel_esq);
            mot2_anti(vel_dir);
            Serial.print("Virando para direita");
            Serial.println(enc.read());
        }
        // Abrir garra
        sala3_frente(enc_peq, 1000);
        enc_ant = enc.read();
        while (enc.read() - enc_ant <= enc_90)
        {
            mot1_hor(vel_esq);
            mot2_anti(vel_dir);
            Serial.print("Virando para direita");
            Serial.println(enc.read());
        }
        pos = true;
    }
    else
    {
        enc_ant = enc.read();
        while (enc_ant - enc.read() <= enc_90)
        {
            mot1_anti(vel_esq);
            mot2_hor(vel_dir);
            Serial.print("Girando 90 para esquerda: ");
            Serial.println(enc.read());
        }
        // Abrir garra
        sala3_frente(enc_peq, 1000);
        enc_ant = enc.read();
        while (enc_ant - enc.read() <= enc_90)
        {
            mot1_anti(vel_esq);
            mot2_hor(vel_dir);
            Serial.print("Girando 90 para esquerda: ");
            Serial.println(enc.read());
        }
        pos = false;
    }
}
