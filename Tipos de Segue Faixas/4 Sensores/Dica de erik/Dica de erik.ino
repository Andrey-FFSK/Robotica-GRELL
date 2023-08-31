// Dica de erik
#include "Include.h"  // Dando include nas variaveis e funções
#include "Oled.h"     // Dando include no arquivo que tem as bibliotecas e criando o objeto do display oled

// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = { s_oeste, s_noroeste, s_nordeste, s_leste, s_norte, esq, dir, led_g, mot_in1, mot_in2, mot_in3, mot_in4 };

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Protocolo para iniciar o display
  display.setTextColor(WHITE);                // Colocando cor para o texto
  // Colocando os sensores como INPUT, e o resto como OUTPUT, tudo isso pelo array
  for (int i = 0; i < 7; i++)  // Usando o array para fazer os pinmode como input
    pinMode(pinos[i], INPUT);
  for (int i = 7; i < 12; i++)  // Usando o array para fazer que o resto seja como output
    pinMode(pinos[i], OUTPUT);
  //pinMode(incli, INPUT_PULLUP);  // O inclinas é considerado pull_up, para tirar ruidos
  Serial.begin(9600);            // Iniciando o serial monitor
}
void loop() {
  display.clearDisplay();  // Limpando o display no inicio do loop
  // Essa parte é o bitSwift, criar uma variavel leitura do tipo byte, porem a gente so usa os bits dessa varaivel, a quantidade de bits depende de quantos sensores estao usando
  byte leitura = 0;  // Definir sempre 0 quando definir algo como o for abaixo
  for (int i = 0; i < 4; i++)
    leitura |= digitalRead(pinos[i]) << i;  // Colocando as entrada da tabela da verdade usando um bitshift automatico, o valor do i depende dos sensores
  leitura = (~leitura) & (0b00001111);      // Colocando um inversor para que funcione com a tabela da verdade, pq o sensor dectectar no branco, AND uma mascara para ir so os bits que eu quero

  vel_esq = 120;  // valor normal dos motores
  vel_dir = 110;  //

  if (ult_meio.read() <= 3)  // Se o sensor dectar que esta distancia ativa a função de desviar
  {
    display.setCursor(0, 0);  // Pritando no oled
    display.println("Desviando obsta");
    display.display();
    desv(vel_esq, vel_dir);
  }

  // Condições que usa a melhor situação dos sensores, o bit mais da direita é o s_leste e o bit mais na esquerda é o s_oeste
  // Algumas tem if com OR por conta que eles fazem a mesma coisa na condição.
  if (leitura == 0b0010)  // Condição mini ajuste para direita
  {
    if (ver == false) {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);

      /*
      if (millis()  >= time_if) {
        enc_ant = enc.read();
        while (enc.read() - enc_ant <= frentao) {  // indo frentre
          mot1_hor(vel_esq);
          mot2_hor(vel_dir);
          Serial.print("andando na frente");
          Serial.println(enc.read());
        }
        enc_ant = enc.read();
        while (enc_ant - enc.read() <= enc_90) {  // virando esquerda
          mot1_anti(vel_esq);
          mot2_hor(vel_dir);
          Serial.print("girando 90 para esquerda");
          Serial.println(enc.read());
        }
        while (digitalRead(s_norte) == 1) {
          mot1_hor(vel_esq);
          mot2_hor(vel_dir);
          Serial.print("andando para frente");
          Serial.println(enc.read());
        }
        enc_ant = enc.read();
        while (enc.read() - enc_ant <= enc_peq) {  // Se ajeitando na faixa
          mot1_hor(vel_esq);
          mot2_hor(vel_dir);
          Serial.print("andando na frente");
          Serial.println(enc.read());
        }
        while (digitalRead(s_norte) == 1)  // Se ajeitando na faixa
        {
          mot1_anti(vel_esq);
          mot2_hor(vel_dir);
          Serial.print("girando 90 para direita");
          Serial.println(enc.read());
        } /*
        millis_ant = millis();
        
        while (millis() - millis_ant <= time_while) {
          
          }/
          display.setCursor(0, 0);
          vel_esq = 150;                                                         // valor normal dos motores
          vel_dir = 130;                                                         //
          if ((digitalRead(s_noroeste) == 0) || (digitalRead(s_nordeste) == 1))  // VIRAR ESQUERDA
          {
            display.print("ESQUERDA");
            display.display();
            vel_dir = 220;  //
            mot1_hor(vel_esq);
            mot2_hor(vel_dir);
          } else if ((digitalRead(s_noroeste) == 1) || (digitalRead(s_nordeste) == 0))  // VIRAR DIREITA
          {
            display.clearDisplay();
            display.print("DIREITA");
            display.display();
            vel_esq = 240;  //
            mot1_hor(vel_esq);
            mot2_hor(vel_dir);
          } else {
            display.clearDisplay();
            display.println("FRENTE");
            display.display();
            mot1_hor(vel_esq);
            mot2_hor(vel_dir);
          }
        }
      }*/
      display.setCursor(0, 0);
      display.println("0010 / Direita");
      display.display();

      Serial.println("leitura == 0010 / ajustando para direita: ");
    } else {

      display.setCursor(0, 0);
      display.println("0010 / Tras");
      display.display();
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas_outro) {
        mot1_anti(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("Indo para tras: ");
        Serial.println(enc.read());
      }
      ver = false;
    }

  } else if (leitura == 0b0100)  // mini ajuste para esquerda
  {
    if (ver == false) {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);

      /*
      if (millis()  >= time_if) {

        enc_ant = enc.read();
        while (enc.read() - enc_ant <= frentao) {  // Se ajeitando na faixa
          mot1_hor(vel_esq);
          mot2_hor(vel_dir);
          Serial.print("andando na frente");
          Serial.println(enc.read());
        }
        enc_ant = enc.read();
        while (enc_ant - enc.read() <= enc_90) {  // virando direita
          mot1_hor(vel_esq);
          mot2_anti(vel_dir);
          Serial.print("girando 90 para direita");
          Serial.println(enc.read());
        }
        while (digitalRead(s_norte) == 1) {
          mot1_hor(vel_esq);
          mot2_hor(vel_dir);
          Serial.print("andando para frente");
          Serial.println(enc.read());
        }
        enc_ant = enc.read();
        while (enc.read() - enc_ant <= enc_peq) {  // Se ajeitando na faixa
          mot1_hor(vel_esq);
          mot2_hor(vel_dir);
          Serial.print("andando na frente");
          Serial.println(enc.read());
        }
        while (digitalRead(s_norte) == 1)  // Se ajeitando na faixa
        {
          mot1_hor(vel_esq);
          mot2_anti(vel_dir);
          Serial.print("girando 90 para esquerda");
          Serial.println(enc.read());
        }
        /*

        while (millis() - millis_ant <= time_while) {
          display.setCursor(0, 0);
          vel_esq = 130;                                                         // valor normal dos motores
          vel_dir = 110;                                                         //
          if ((digitalRead(s_noroeste) == 0) || (digitalRead(s_nordeste) == 1))  // VIRAR ESQUERDA
          {
            display.clearDisplay();
            display.print("ESQUERDA");
            display.display();
            vel_dir = 220;  //
            mot1_hor(vel_esq);
            mot2_hor(vel_dir);
          } else if ((digitalRead(s_noroeste) == 1) || (digitalRead(s_nordeste) == 0))  // VIRAR DIREITA
          {
            display.clearDisplay();
            display.print("DIREITA");
            display.display();
            vel_esq = 240;  //
            mot1_hor(vel_esq);
            mot2_hor(vel_dir);
          } else {
            display.clearDisplay();
            display.println("FRENTE");
            display.display();
            mot1_hor(vel_esq);
            mot2_hor(vel_dir);
          }
        }
      }*/
      display.setCursor(0, 0);
      display.println("0100 / Esquerda");
      display.display();

      Serial.println("leitura == 0100 / ajustando para esquerda");
    } else {

      display.setCursor(0, 0);
      display.println("0100 / Tras");
      display.display();
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas_outro) {
        mot1_anti(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("Indo para tras: ");
        Serial.println(enc.read());
      }
      ver = false;
    }
  } else if ((leitura == 0b0000) || (leitura == 0b0110))  // Condição de ir reto
  {
    if (ver == false) {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);

      display.setCursor(0, 0);
      display.println("lei = 0000");
      display.display();

      Serial.println("leitura = 0000; leitura = 0110");
    } else {

      display.setCursor(0, 0);
      display.println("0000 / Tras");
      display.display();
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas_outro) {
        mot1_anti(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("Indo para tras: ");
        Serial.println(enc.read());
      }
      ver = false;
    }
  }  else if ((leitura == 0b1000) || (leitura == 0b1100) || (leitura == 0b1110) || (leitura == 0b1010))  // Condição 90 esq
  {
    if (ver == false) {

      digitalWrite(led_g, 1);
      mot1_par();
      mot2_par();
      delay(400);
      sensi();
      digitalWrite(led_g, 0);
      ver = true;
    } else {

      ver = false;
      Serial.print("Esq: ");
      Serial.print(m_esq);
      Serial.print("(");
      Serial.print(analogRead(esq));
      Serial.print(") / Dir: ");
      Serial.print(m_dir);
      Serial.print("(");
      Serial.print(analogRead(dir));
      Serial.println(")");

      display.setCursor(0, 0);
      display.print("Esq: ");
      display.print(m_esq);
      display.print("(");
      display.print(analogRead(esq));
      display.println(")");

      display.print("Dir: ");
      display.print(m_dir);
      display.print("(");
      display.print(analogRead(dir));
      display.println(")");

      display.println("1000 / Esq_90");
      display.display();

      esq_90();  // virar a direita; antes tava encruzilhada();
    }
  }

  else if ((leitura == 0b0001) || (leitura == 0b0011) || (leitura == 0b0111) || (leitura == 0b0101))  // Condição de 90 direita
  {
    if (ver == false) {

      digitalWrite(led_g, 1);
      mot1_par();
      mot2_par();
      delay(400);
      sensi();
      digitalWrite(led_g, 0);
      ver = true;
    } else {

      ver = false;
      Serial.print("Esq: ");
      Serial.print(m_esq);
      Serial.print("(");
      Serial.print(analogRead(esq));
      Serial.print(") / Dir: ");
      Serial.print(m_dir);
      Serial.print("(");
      Serial.print(analogRead(dir));
      Serial.println(")");

      display.setCursor(0, 0);
      display.print("Esq: ");
      display.print(m_esq);
      display.print("(");
      display.print(analogRead(esq));
      display.println(")");

      display.print("Dir: ");
      display.print(m_dir);
      display.print("(");
      display.print(analogRead(dir));
      display.println(")");

      display.println("0001 / Dir_90");
      display.display();

      dir_90();  // virar a esquerda; antes era encruzilhada();
    }
  } else if ((leitura == 0b1001) || (leitura == 0b1111) || (leitura == 0b1011) || (leitura == 0b1101))  // ENCRUZILHADA
  {
    if (ver == false) {

      mot1_par();
      mot2_par();
      digitalWrite(led_g, 1);
      delay(400);
      sensi();
      digitalWrite(led_g, 0);
      ver = true;
    } else {

      ver = false;
      Serial.print("Esq: ");
      Serial.print(m_esq);
      Serial.print("(");
      Serial.print(analogRead(esq));
      Serial.print(") / Dir: ");
      Serial.print(m_dir);
      Serial.print("(");
      Serial.print(analogRead(dir));
      Serial.println(")");

      display.setCursor(0, 0);
      display.print("Esq: ");
      display.print(m_esq);
      display.print("(");
      display.print(analogRead(esq));
      display.println(")");

      display.print("Dir: ");
      display.print(m_dir);
      display.print("(");
      display.print(analogRead(dir));
      display.println(")");

      display.println("1111 / Encruzi");
      display.display();

      encruzilhada();  // encruzilhada
    }
  }
}
