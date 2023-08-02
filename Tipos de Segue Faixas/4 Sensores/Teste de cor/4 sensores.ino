#include <Ultrasonic.h> //Incluindo a biblioteca do ultrasonic de erik simoes
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
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

// Definindo portas para o sensor de cor, o pin 2 e o led
#define esq A1
#define dir A0
int m_esq = 0;
int m_dir = 0;


// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = {s_leste, s_nordeste, s_noroeste, s_oeste, s_norte, esq, dir, 7, mot_in1, mot_in2, mot_in3, mot_in4};

const int j = 110; // PWM usado para a velocidade, min == 0 e max == 255
int enc_ant = 0;
const int enc_fre = 450;
const int enc_90 = 420;
const int enc_peq = 150;
Ultrasonic sensor(A2, A3); // trig == 7; echo == 4 | trig = amarel e ech = marrm
Encoder enc(3, 2);

const int esq_branco = 600;
const int dir_branco = 600;

//Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
  /*
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.clearDisplay();*/
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
  digitalWrite(7, 0);

  // Serial.print(leitura, BIN);
  // Serial.print(" sens: ");

  // if (sensor.read() <= 18) desv_d(j); // Se o sensor dectar que esta distancia ativa a função de desviar

  // Condições que usa a melhor situação dos sensores, o bit mais da direita é o s_leste e o bit mais na esquerda é o s_oeste
  // Algumas tem if com OR por conta que eles fazem a mesma coisa na condição.
  // Condição de 0011 ou 1100: é o algoritimo de 90 graus, pensando que so vai ativar no 90
  if (leitura == 0b0000) // Condição 1
  {
    mot1_hor(j);
    mot2_hor(j);
    //display.clearDisplay();
    //display.setCursor(0, 0);
    //display.print("leitura == 0000");
    Serial.println("leitura = 0000");
  }
  else if ((leitura == 0b0010) /*| (leitura == 0b0001)*/) // Condição 2
  {
    mot1_hor(j);
    mot2_anti(j);
    //display.clearDisplay();
    //display.setCursor(0, 0);
    //display.print("leitura == 0010");
    Serial.println("leitura == 0010");
  }
  else if (leitura == 0b0011) // Condição 4
  {
    mot1_anti(j);
    mot2_anti(j);
    delay(50);
    digitalWrite(7, 1);
    mot1_par();
    mot2_par();
    delay(1000);
    m_esq = map(constrain(analogRead(esq), 34, 152), 34, 152, 0, 1023);
    m_dir = map(constrain(analogRead(dir), 27, 133), 27, 133, 0, 1023);
    digitalWrite(7, 0);
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

    if ((m_esq >= esq_branco) & (m_dir <= dir_branco)) // Tem 1 quadrado verde na direita
    {
      Serial.println("leitura == 0011; Tem verde");
      enc_ant = enc.read();
      while (enc.read() - enc_ant <= enc_fre)
      {
        mot1_hor(j);
        mot2_hor(j);
      }

      enc_ant = enc.read();
      while (enc.read() - enc_ant <= enc_peq)
      {
        mot1_hor(j);
        mot2_anti(j);
        Serial.print("virando para direita");
          Serial.println(enc.read());
      }
      while(digitalRead(s_norte) == 1){
        mot1_hor(j);
        mot2_anti(j);
        Serial.print("virando para direita");
      }
    }
    else // Nao tem quadrado verde
    {
      Serial.println("Leitura == 0011; nao tem verde");
      enc_ant = enc.read();
      while (enc.read() - enc_ant <= enc_fre)
      {
        mot1_hor(j);
        mot2_hor(j);
      }

      if (digitalRead(s_norte) == 1)
      {
        enc_ant = enc.read();
        while (enc.read() - enc_ant <= enc_peq)
        {
          mot1_hor(j);
          mot2_anti(j);
          Serial.print("virando para direita");
          Serial.println(enc.read());
        }
        while (digitalRead(s_norte) == 1)
        {
          mot1_hor(j);
          mot2_anti(j);
        }
      }
    }
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

  else if ((leitura == 0b0100) /*| (leitura == 0b1000)*/) // Condição 5
  {
    mot1_anti(j);
    mot2_hor(j);
    Serial.println("leitura == 0100");
  }
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
    digitalWrite(7, 1);
    mot1_par();
    mot2_par();
    delay(1000);
    m_esq = map(constrain(analogRead(esq), 34, 152), 34, 152, 0, 1023);
    m_dir = map(constrain(analogRead(dir), 27, 133), 27, 133, 0, 1023);
    digitalWrite(7, 0);
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

    if ((m_esq <= esq_branco) & (m_dir >= dir_branco)) // Tem 1 quadrado verde na esquerda
    {
      Serial.println("leitura == 1100; tem verde");
      enc_ant = enc.read();
      while (enc.read() - enc_ant <= enc_fre)
      {
        mot1_hor(j);
        mot2_hor(j);
      }

      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_peq)
      {
        mot1_anti(j);
        mot2_hor(j);
        Serial.print("virando pra esquerda");
          Serial.println(enc.read());
      }
      while(digitalRead(s_norte) == 1){
        mot1_anti(j);
        mot2_hor(j);
        Serial.print("virando pra esquerda");
      }
    }
    else // Nao tem quadrado verde
    {
      Serial.println("leitura == 1100; nao tem verde");
      enc_ant = enc.read();
      while (enc.read() - enc_ant <= enc_fre)
      {
        mot1_hor(j);
        mot2_hor(j);
      }

      if (digitalRead(s_norte) == 1)
      {
        enc_ant = enc.read();
        while (enc_ant - enc.read() <= enc_peq)
        {
          mot1_anti(j);
          mot2_hor(j);
          Serial.print("virando pra esquerda");
          Serial.println(enc.read());
        }
        while (digitalRead(s_norte) == 1)
        {
          mot1_anti(j);
          mot2_hor(j);
          Serial.print("virando pra esquerda");
        }
      }
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
  }
  else if (leitura == 0b1111) // ENCRUZILHADA
  {
    mot1_anti(j);
    mot2_anti(j);
    delay(50);
    digitalWrite(7, 1);
    mot1_par();
    mot2_par();
    delay(1000);
    m_esq = map(constrain(analogRead(esq), 34, 152), 34, 152, 0, 1023);
    m_dir = map(constrain(analogRead(dir), 27, 133), 27, 133, 0, 1023);
    digitalWrite(7, 0);
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
    if ((m_esq <= esq_branco) & (m_dir >= dir_branco)) // Tem 1 quadrado verde na esquerda
    {
      Serial.println("Encruzilhada; Verde na esquerda");
      enc_ant = enc.read();
      while (enc.read() - enc_ant <= enc_fre)
      {
        mot1_hor(j);
        mot2_hor(j);
      }

      enc_ant = enc.read();
      while (enc_ant - enc.read() <= enc_peq)
      {
        mot1_anti(j);
        mot2_hor(j);
        Serial.print("virando para esquerda");
        Serial.println(enc.read());
      }
      while (digitalRead(s_norte) == 1)
      {
        mot1_anti(j);
        mot2_hor(j);
      }
    }
    else if ((m_esq >= esq_branco) & (m_dir <= dir_branco)) // Tem 1 quadrado verde na direita
    {
      Serial.println("Encruzilhada; Verde na direita");
      enc_ant = enc.read();
      while (enc.read() - enc_ant <= enc_fre)
      {
        mot1_hor(j);
        mot2_hor(j);
      }

      enc_ant = enc.read();
      while (enc.read() - enc_ant <= enc_peq)
      {
        mot1_hor(j);
        mot2_anti(j);
        Serial.print("Virando para direita");
        Serial.println(enc.read());
      }
      while (digitalRead(s_norte) == 1)
      {
        mot1_hor(j);
        mot2_anti(j);
      }
    }
    else if ((m_esq >= esq_branco) & (m_dir >= dir_branco)) // Nao tem quadrado verde
    {
      Serial.println("Encruzilhada; Nao tem verde");
      enc_ant = enc.read();
      while (enc.read() - enc_ant <= enc_fre)
      {
        mot1_hor(j);
        mot2_hor(j);
      }
    }
    else // Tem 2 quadrado verde
    {
      Serial.println("Encruzilhada; 2 verdes");
      enc_ant = enc.read();
      while (enc.read() - enc_ant <= 800)
      {
        mot1_hor(j);
        mot2_anti(j);
        Serial.print("dando 180");
        Serial.println(enc.read());
      }
    }
  }
}

/*
LEMBRAR DAS VARIAVEIS COM ENCRUZILHADA
nao esta usando while
COMO ELE VAI PARAR?
esquerda alta e direita baixa
*/

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

void desv_d(int velo) // Função para o robo desviar pela direita o obstaculo
{
  mot1_par();
  mot2_par();
  delay(200);
  mot1_hor(velo);
  mot2_anti(velo);
  delay(800);
  // while(digitalRead(s_norte) == 1){
  mot1_hor(velo);
  mot2_hor(velo);
  delay(2100);
  mot1_anti(velo);
  mot2_hor(velo);
  delay(800);
  mot1_hor(velo);
  mot2_hor(velo);
  delay(2000);
  mot1_anti(velo);
  mot2_hor(velo);
  delay(800);
  //}
}
