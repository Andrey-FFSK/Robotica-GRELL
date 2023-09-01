// Sala 3
#include "Include.h"
#include "Oled.h"

const int pinos[] = {s_leste, s_nordeste, s_noroeste, s_oeste, s_norte, esq, dir, led_g, mot_in1, mot_in2, mot_in3, mot_in4};

int enc_atual = 0;
bool pos_esq = false;
bool pos_dir = false;
bool sala3_ver = false;
int ult_esq = 0;
int ult_dir = 0;

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  for (int i = 0; i < 7; i++)
    pinMode(pinos[i], INPUT);
  for (int i = 7; i < 12; i++)
    pinMode(pinos[i], OUTPUT);
  pinMode(incli, INPUT_PULLUP);
  Serial.begin(9600);
  
  
  bool pos;
  
  //servo_garra.attach(7);
  //servo_cacamba.attach(8);
  //servo_garra.write(garra_cima);
  delay(1000);
  
}

void loop()
{
  display.clearDisplay();
  
  if (sala3_ver == false)
  {
    enc_ant = enc.read(); // Andando um pouco pra frante para resetar
    while (enc.read() - enc_ant <= enc_pas)
    {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Andando na frente: ");
      Serial.println(enc.read());
    }
    
    enc_ant = enc.read(); // Virando para esquerda para medir se a parede esta perto
    while (enc_ant - enc.read() <= enc_90)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Girando 90 para esquerda: ");
      Serial.println(enc.read());
    }
    ult_esq = ult_meio.read(); // guardando valor
    display.print("Esq: ");
    display.println(ult_esq);
    display.display();
    enc_ant = enc.read(); // Dando 180 para ver a distancia da parede da direita
    while (enc.read() - enc_ant <= enc_90 * 2)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Girando 180 para direita: ");
      Serial.println(enc.read());
    }
    ult_dir = ult_meio.read();
    display.print("Dir: ");
    display.println(ult_dir);
    display.display();
    enc_ant = enc.read(); // voltando para etapa inicial
    while (enc_ant - enc.read() <= enc_90)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Girando 90 para esquerda: ");
      Serial.println(enc.read());
    }
    mot1_par();
    mot2_par();
    delay(1000);
    if (ult_esq >= ult_dir) // Vendo qual parte é mais perto dele
      pos = true;           // ta mais perto da direita
    else
      pos = false; // ta mais perto da esquerda
    display.print("Pos: ");
    display.print(pos);
    display.display();
    if (pos == false) // ajeitando para a função sala3_pas
    {
      display.print(" / Esquerda");
      display.display();
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_90)
      {
        mot1_anti(vel_esq);
        mot2_hor(vel_dir);
        Serial.print("Girando 90 para esquerda: ");
        Serial.println(enc.read());
      }
    }
    else
    {
      display.print(" / Direita");
      display.display();
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
      Serial.print("Andando na frente: ");
      Serial.println(enc.read());
      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Meio: ");
      display.print(ult_meio.read());
      display.display();
    }
    delay(300); // delay para ele ficar encostado na parede
    sala3_ver = true;
  }
  else // Quando ele ja ter feito a verificada e ter pego valor de pos
  {
    display.setCursor(0, 0);
      display.print("pos: ");
      display.println(pos);
      display.display();
    sala3_pas(); // ver função
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= 5300)
    {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Girando 90 para direita: ");
      Serial.println(enc.read());
      
    }
    /*
    while (ult_meio.read() >= perto_garra)
    {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
    }*/
    mot1_par();
    mot2_par();
    delay(1000);
    display.println("garra subindo");
      display.display();
    garra_subir();
    while (ult_meio.read() >= perto) // preparativo para a sala3_pas
    {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Andando na frente: ");
      Serial.println(enc.read());
    }
    delay(300);
    sala3_verifica();
  }
}

void sala3_frente(int dis, int temp)
{
  if (pos == false) // Vendo qual lado da parede ele estar
  {
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= dis)
    {
      mot1_hor(vel_esq_p);
      mot2_hor(vel_dir_g);
      Serial.print("Andando par frente-esquerda: ");
      Serial.println(enc.read());
      if (ult_meio.read() <= perto)
      {
        enc_ant = 0;
      }
    }
  }
  else if (pos == true)
  {
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= dis)
    {
      mot1_hor(vel_esq_g);
      mot2_hor(vel_dir_p);
      Serial.print("Andando na frente-direita: ");
      Serial.println(enc.read());
      if (ult_meio.read() <= perto)
      {
        enc_ant = 0;
      }
    }
  }
  mot1_par();
  mot2_par();
  delay(temp);
}

void sala3_pas() // Pos = false é esq; Pos = true é dir;
{
  if (pos == false)
  {display.println("virando direita: ");
      display.display();
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_90)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Girando 90 para direita: ");
      Serial.println(enc.read());
      
    }
    garra_descer();
    sala3_frente(enc_fre_sala3, 1500);
    enc_ant = enc.read();
    while (enc.read() - enc_ant <= enc_90)
    {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
      Serial.print("Girando 90 para direita: ");
      Serial.println(enc.read());
    }
    pos = true;
  }
  else if(pos == true)
  {display.println("virando Esquerda: ");
      display.display();
    enc_ant = enc.read();
    while (enc_ant - enc.read() <= enc_90)
    {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.print("Girando 90 para esquerda: ");
      Serial.println(enc.read());
      
    }
    garra_descer();
    sala3_frente(enc_fre_sala3, 1500);
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

void sala3_verifica() // Função para caso ele bater na area de resgate
{
  sensi();
  if (analogRead(meio) <= meio_branco) // Aqui que ele tem que depositar
  {
    depositar();
    if (pos == true) // Esta invertido para ser mais facil
    {
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas)
      {
        mot1_anti(vel_esq);
        mot2_hor(vel_dir);
        Serial.print("Virando para esquerda: ");
        Serial.println(enc.read());
      }
    }
    else if (pos == false)
    {
      enc_ant = enc.read();
      while (enc.read() - enc_ant <= enc_pas)
      {
        mot1_hor(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("Virando para direita: ");
        Serial.println(enc.read());
      }
    }
  }
}
