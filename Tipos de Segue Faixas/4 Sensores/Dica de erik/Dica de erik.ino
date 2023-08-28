// Dica de erik
#include "Include.h"
#include "Oled.h"

// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = { s_oeste, s_noroeste, s_nordeste, s_leste, s_norte, esq, dir, incli, led_g, mot_in1, mot_in2, mot_in3, mot_in4 };

bool ver = false;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  // Colocando os sensores como INPUT, e o resto como OUTPUT, tudo isso pelo array
  for (int i = 0; i < 8; i++)
    pinMode(pinos[i], INPUT);
  for (int i = 8; i < 12; i++)
    pinMode(pinos[i], OUTPUT);
  Serial.begin(9600);
  servo_garra.attach(7);
  servo_garra.write(garra_cima);
  delay(1000);
  bool ver = false;
}
void loop() {
  display.clearDisplay();
  // Essa parte é o bitSwift, criar uma variavel leitura do tipo byte, porem a gente so usa os bits dessa varaivel, a quantidade de bits depende de quantos sensores estao usando
  byte leitura = 0;  // Definir sempre 0 quando definir algo como o for abaixo
  for (int i = 0; i < 4; i++)
    leitura |= digitalRead(pinos[i]) << i;  // Colocando as entrada da tabela da verdade usando um bitshift automatico, o valor do i depende dos sensores
  leitura = (~leitura) & (0b00001111);      // Colocando um inversor para que funcione com a tabela da verdade, pq o sensor dectectar no branco, AND uma mascara para ir so os bits que eu quero

  if (digitalRead(incli) == 0) {
    vel_esq = 230;
    vel_dir = 210;
  } else {
    int vel_esq = 190;  // PWM usado para a velocidade, min == 0 e max == 255
    int vel_dir = 170;
  }

  if (ult_meio.read() <= 9)  // Se o sensor dectar que esta distancia ativa a função de desviar
  {
    desv_d(vel_esq, vel_dir);
    display.setCursor(0, 0);
    display.println("Desviando obsta");
    display.display();
  }

  // Condições que usa a melhor situação dos sensores, o bit mais da direita é o s_leste e o bit mais na esquerda é o s_oeste
  // Algumas tem if com OR por conta que eles fazem a mesma coisa na condição.
  // Condição de 0011 ou 1100: é o algoritimo de 90 graus, pensando que so vai ativar no 90
  if (leitura == 0b0010)  // Condição 2
  {
    if (ver == false) {
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);

      display.setCursor(0, 0);
      display.println("lei == 0010 / Direita");
      display.display();

      Serial.println("leitura == 0010 / ajustando para direita: ");
    } else {
      display.setCursor(0, 0);
      display.println("lei == 0010 / Tras");
      display.display();
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas) {
        mot1_anti(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("Indo para tras: ");
        Serial.println(enc.read());
      }
      ver = false;
    }

  } else if (leitura == 0b0100)  // Condição 5
  {
    if (ver == false) {
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);

      display.setCursor(0, 0);
      display.println("lei == 0100 / Esquerda");
      display.display();

      Serial.println("leitura == 0100 / ajustando para esquerda");
    } else {
      display.setCursor(0, 0);
      display.println("lei == 0100 / Tras");
      display.display();
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas) {
        mot1_anti(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("Indo para tras: ");
        Serial.println(enc.read());
      }
      ver = false;
    }

  } else if ((leitura == 0b0000) || (leitura == 0b0110))  // Condição 1
  {
    if (ver == false) {
      mot1_hor(vel_esq);
      mot2_hor(vel_dir);

      display.setCursor(0, 0);
      display.println("lei = 0000");
      display.display();

      Serial.println("leitura = 0000; leitura == 0110");
    } else {
      display.setCursor(0, 0);
      display.println("lei == 0000 / Tras");
      display.display();
      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_pas) {
        mot1_anti(vel_esq);
        mot2_anti(vel_dir);
        Serial.print("Indo para tras: ");
        Serial.println(enc.read());
      }
      ver = false;
    }

  } else if ((leitura == 0b1000) || (leitura == 0b1100) || (leitura == 0b1110) || (leitura == 0b1010))  // Condição 4
  {
    if (ver == false) {
      digitalWrite(led_g, 1);
      mot1_par();
      mot2_par();
      delay(1000);
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

      display.println("lei == 0b1000 / Esq_90");
      display.display();
      delay(3000);
      esq_90();  // virar a direita; antes tava encruzilhada();
    }
  }

  else if ((leitura == 0b0001) || (leitura == 0b0011) || (leitura == 0b0111) || (leitura == 0b0101))  // Condição 7
  {
    if (ver == false) {
      digitalWrite(led_g, 1);
      mot1_par();
      mot2_par();
      delay(1000);
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

      display.println("lei == 0001 / Dir_90");
      display.display();

      delay(3000);

      dir_90();  // virar a esquerda; antes era encruzilhada();
    }
  } else if ((leitura == 0b1001) || (leitura == 0b1111) || (leitura == 0b1011) || (leitura == 0b1101))  // ENCRUZILHADA
  {
    if (ver == false) {
      mot1_par();
      mot2_par();
      digitalWrite(led_g, 1);
      delay(1000);
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

      display.println("lei == 0b1111 / Encruzi");
      display.display();

      delay(3000);

      encruzilhada();  // encruzilhada
    }
  }
}
/*
COMO ELE VAI PARAR? ele nao para.
*/
