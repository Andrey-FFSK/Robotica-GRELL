#include <Ultrasonic.h>

// Definindo as portas dos sensores e da portas H
#define s_oeste 8     // cinza, OUT1
#define s_noroeste 10 // branco, OUT2
#define s_norte 11    // verde, OUT4
#define s_nordeste 12 // preto, OUT3
#define s_leste 13    // azul, OUT5

// Definindo Sensor de cor e led acoplado a ele
#define led_g 2
#define esq A1
#define dir A0

// Motor 1 = esquerda; Motor 2 = direita
#define mot_in1 3 // amarelo, direita, tras
#define mot_in2 5 // branco, direita, frente
#define mot_in3 6 // laranja, esquerda, frente
#define mot_in4 9 // preto, esquerda, tras

// Usando array para colocar todos os pinos, coloquei os sensores invertido por causa do BitSwift em baixo
int pinos[] = {8, 13, 12, 11, 10, A1, A0, 5, 3, 6, 9, 2};
Ultrasonic sensor(7, 4);
// Definindo variaveis
int temp = 500;
int ant = 0;

int o = 150;
float tensaoA0;

void setup()
{
  Serial.begin(9600);
  for (int i; i < 7; i++)
    pinMode(pinos[i], INPUT);
  for (int i = 7; i < 12; i++)
    pinMode(pinos[i], OUTPUT);
}

void loop()
{
  digitalWrite(led_g, 1);


  //analogWrite(mot_in4, o);
  // mot1_hor(o);
  // mot2_hor(o);

  // mot1_anti(o);
  // mot2_anti(o);

  byte leitura = 0;
  for (int i = 0; i < 5; i++)
    leitura |= digitalRead(pinos[i]) << i;
  leitura = (~leitura) & 0b00011111;
  tensaoA0 = (div(A0) * 5) / 1024.0;
  tensaoA0 *= 8.4;
  int m_esq = map(constrain(analogRead(esq), 73, 210), 73, 210, 0, 1023);
  int m_dir = map(constrain(analogRead(dir), 27, 120), 27, 120, 0, 1023);

  Serial.print("Leitura: ");
  Serial.print(leitura, BIN);
  Serial.print("Bits / Tensão: ");
  Serial.print(tensaoA0);
  Serial.print("V / Olho:");
  Serial.print(sensor.read());
  Serial.print("cm / Esq: ");
  Serial.print(m_esq);
  Serial.print("(");
  Serial.print(analogRead(esq));
  Serial.print(") / Dir: ");
  Serial.print(m_dir);
  Serial.print("(");
  Serial.print(analogRead(dir));
  Serial.println(")");
}

float div(uint8_t A0)
{
  float total = 0;
  for (int i = 0; i < 12; i++)
  {
    total += 1.0 * analogRead(A0);
    delay(5);
  }
  return total / (float)12;
}

// Inicio das funções, para cada caso, totalizando 6 funções diferente
void mot1_anti(int velo) // Função para o motor da esquerda girar no sentido anti horario com a velocidade variavel
{
  analogWrite(mot_in4, 0);
  analogWrite(mot_in3, velo);
}
void mot1_hor(int velo) // Função para o motor da esquerda girar no sentido horario com a velocidade variavel
{
  analogWrite(mot_in4, velo);
  analogWrite(mot_in3, 0);
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
