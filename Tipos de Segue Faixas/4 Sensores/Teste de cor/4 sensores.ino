#include "Include.h"
// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = {s_leste, s_nordeste, s_noroeste, s_oeste, s_norte, esq, dir, 7, mot_in1, mot_in2, mot_in3, mot_in4};


void setup()
{
  /*
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);*/
  // Colocando os sensores como INPUT, e o resto como OUTPUT, tudo isso pelo array
  for (int i = 0; i < 7; i++)
    pinMode(pinos[i], INPUT);
  for (int i = 7; i < 12; i++)
    pinMode(pinos[i], OUTPUT);
  Serial.begin(9600);
}
void loop()
{

  // Funções do sensor de cor ficar mais amplo, SEMPRE MUDAR

  // Essa parte é o bitSwift, criar uma variavel leitura do tipo byte, porem a gente so usa os bits dessa varaivel, a quantidade de bits depende de quantos sensores estao usando
  byte leitura = 0; // Definir sempre 0 quando definir algo como o for abaixo
  for (int i = 0; i < 4; i++)
    leitura |= digitalRead(pinos[i]) << i; // Colocando as entrada da tabela da verdade usando um bitshift automatico, o valor do i depende dos sensores
  leitura = (~leitura) & (0b00001111);     // Colocando um inversor para que funcione com a tabela da verdade, pq o sensor dectectar no branco, AND uma mascara para ir so os bits que eu quero
  digitalWrite(led_g, 1);
  m_esq = map(constrain(analogRead(esq), 350, 518), 350, 518, 0, 1023);
  m_dir = map(constrain(analogRead(dir), 169, 300), 169, 300, 0, 1023);

  // Serial.print(leitura, BIN);
  // Serial.print(" sens: ");

  // if (sensor.read() <= 18) desv_d(j); // Se o sensor dectar que esta distancia ativa a função de desviar
  /*(if (m_esq <= esq_branco)
  {
    mot1_anti(j);
    mot2_hor(j);
    Serial.print("ajustando para direita: ");
    Serial.print(m_esq);
    Serial.print("(");
    Serial.println(analogRead(esq));
  }
  else if (m_dir <= dir_branco)
  {
    mot1_hor(j);
    mot2_anti(j);
    Serial.print("ajustndo para esquerda: ");
    Serial.print(m_dir);
    Serial.print("(");
    Serial.println(analogRead(dir));
  }*/

  // Condições que usa a melhor situação dos sensores, o bit mais da direita é o s_leste e o bit mais na esquerda é o s_oeste
  // Algumas tem if com OR por conta que eles fazem a mesma coisa na condição.
  // Condição de 0011 ou 1100: é o algoritimo de 90 graus, pensando que so vai ativar no 90
  if ((m_dir <= dir_cinza && m_dir >= dir_verde) /*| (leitura == 0b0001)*/) // Condição 2
  {
    mot1_hor(j);
    mot2_anti(j);
    /*
    Serial.println("oi");
    display.clearDisplay();
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
    Serial.println("oia");
    display.display();*/

    Serial.print("leitura == 0010 / ajustando para direita: ");
    Serial.print(m_dir);
    Serial.print("(");
    Serial.print(analogRead(dir));
    Serial.println(")");
  }
  else if ((m_esq <= esq_cinza && m_esq >= esq_verde) /*| (leitura == 0b1000)*/) // Condição 5
  {
    mot1_anti(j);
    mot2_hor(j);
    /*
    display.clearDisplay();
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
    display.display();*/

    Serial.print("leitura == 0100 / ajustando para esquerda");
    Serial.print(m_esq);
    Serial.print("(");
    Serial.print(analogRead(esq));
    Serial.println(")");
  }
  else if (leitura == 0b0000) // Condição 1
  {
    mot1_hor(j);
    mot2_hor(j);
    // display.clearDisplay();
    // display.setCursor(0, 0);
    // display.print("leitura == 0000");
    Serial.println("leitura = 0000");
  }
  else if (leitura == 0b0011) // Condição 4
  {
    mot1_anti(j);
    mot2_anti(j);
    delay(50);
    digitalWrite(led_g, 1);
    mot1_par();
    mot2_par();
    delay(1000);
    m_esq = map(constrain(analogRead(esq), 350, 518), 350, 518, 0, 1023);
  m_dir = map(constrain(analogRead(dir), 169, 300), 169, 300, 0, 1023);
    digitalWrite(led_g, 0);
    /*
    display.clearDisplay();
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
    display.display();*/

    Serial.print("Esq: ");
    Serial.print(m_esq);
    Serial.print("(");
    Serial.print(analogRead(esq));
    Serial.print(") / Dir: ");
    Serial.print(m_dir);
    Serial.print("(");
    Serial.print(analogRead(dir));
    Serial.println(")");

    dir_90();
  }
  /*
    if ((m_dir <= branco) & (m_dir >= preto))
    {
      mot1_hor(j);
      mot2_hor(j);
      delay(300);
      mot1_hor(j);
      mot2_anti(j);
      delay(700);
    }
    else
    {
      mot1_hor(j);
      mot2_hor(j);
      delay(300);
    }*/
  else if ((leitura == 0b0110) | (leitura == 0b1001)) // Condição 6
  {
    mot1_par();
    mot2_par();
    delay(200);
    Serial.println("situação de pane");
  }
  else if (leitura == 0b1100) // Condição 7
  {
    mot1_anti(j);
    mot2_anti(j);
    delay(50);
    digitalWrite(led_g, 1);
    mot1_par();
    mot2_par();
    delay(1000);
    m_esq = map(constrain(analogRead(esq), 350, 518), 350, 518, 0, 1023);
  m_dir = map(constrain(analogRead(dir), 169, 300), 169, 300, 0, 1023);
    digitalWrite(led_g, 0);
    /*
        display.clearDisplay();
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
        display.display();
    */
    Serial.print("Esq: ");
    Serial.print(m_esq);
    Serial.print("(");
    Serial.print(analogRead(esq));
    Serial.print(") / Dir: ");
    Serial.print(m_dir);
    Serial.print("(");
    Serial.print(analogRead(dir));
    Serial.println(")");

    esq_90();
  }

  /*
    if ((m_esq <= branco) & (m_esq >= preto))
    {
      mot1_hor(j);
      mot2_hor(j);
      delay(300);
      mot1_anti(j);
      mot2_hor(j);
      delay(700);
    }
    else
    {
      mot1_hor(j);
      mot2_hor(j);
      delay(300);
    }*/

  else if (leitura == 0b1111) // ENCRUZILHADA
  {
    mot1_anti(j);
    mot2_anti(j);
    delay(50);
    digitalWrite(led_g, 1);
    mot1_par();
    mot2_par();
    delay(1000);
    m_esq = map(constrain(analogRead(esq), 350, 518), 350, 518, 0, 1023);
  m_dir = map(constrain(analogRead(dir), 169, 300), 169, 300, 0, 1023);
    digitalWrite(led_g, 0);
    /*
        display.clearDisplay();
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
        display.display();
    */
    Serial.print("Esq: ");
    Serial.print(m_esq);
    Serial.print("(");
    Serial.print(analogRead(esq));
    Serial.print(") / Dir: ");
    Serial.print(m_dir);
    Serial.print("(");
    Serial.print(analogRead(dir));
    Serial.println(")");

    encruzilhada();
  }
}
/*
LEMBRAR DAS VARIAVEIS COM ENCRUZILHADA
nao esta usando while
COMO ELE VAI PARAR?
esquerda alta e direita baixa
*/
