#include "Include.h"

const int pinos[] = {s_leste, s_nordeste, s_noroeste, s_oeste, s_norte, esq, dir, led_g, mot_in1, mot_in2, mot_in3, mot_in4};

#define ult_esq
#define ult_dir
#define ult_meio
#define perto

#define sensi_meio
#define meio_branco

#define vel_esq_p
#define vel_esq_g
#define vel_dir_p
#define vel_dir_g

int enc_atual bool pos_esq = false;
bool pos_dir = false;

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
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_pas)
    {
        mot1_hor(velo);
        mot2_hor(velo);
        Serial.print("andando na frente");
        Serial.println(enc.read());
    } // Abre garra
    if (ult_esq >= ult_dir)
        while (ult_meio >= perto) // Ficar encostado na parede da esquerda
        {
            pos_esq = true;
            mot1_hor(vel_esq_p);
            mot2_hor(vel_dir_g);
        }
    else
        while (ult_meio >= perto) // Ficar encostado na parede da direita
        {
            pos_dir = true;
            mot1_hor(vel_esq_g);
            mot2_hor(vel_dir_p);
        }
    if (sensi_meio <= meio_branco) // Area de resgate
    {
        if (pos_esq = true) // Esta no canto esquerdo
        {
            enc_ant = enc.read();
            while (enc.read() - enc_ant <= enc_peq)
            {
                mot1_hor(vel_esq);
                mot2_anti(vel_dir);
            }
            while (ult_meio >= perto) // Ficar encostado na parede da esquerda
            {
                pos_esq = true;
                mot1_hor(vel_esq_p);
                mot2_hor(vel_dir_g);
            }
        }
        else // Esta no canto direito
        {
            enc_ant = enc.read();
            while (enc_ant - eenc.read() <= enc_peq)
            {
                mot1_anti(vel_esq);
                mot2_hor(vel_dir);
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
    }
}
