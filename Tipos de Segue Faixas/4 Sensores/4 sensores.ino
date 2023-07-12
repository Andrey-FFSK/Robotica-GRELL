#include <Ultrasonic.h> //Incluindo a biblioteca do ultrasonic de erik simoes

// Definindo as portas dos sensores e da portas H
#define s_oeste 8     // cinza, OUT1
#define s_noroeste 13 // branco, OUT2
#define s_norte 12    // verde, OUT4
#define s_nordeste 11 // preto, OUT3
#define s_leste 10    // azul, OUT5

// Motor 2 = esquerda; Motor 1 = direita
#define mot_in1 3 // amarelo, direita, tras
#define mot_in2 5 // branco, direita, frente
#define mot_in3 6 // laranja, esquerda, frente
#define mot_in4 9 // preto, esquerda, tras

// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = {10, 11, 13, 8, 12, 9, 6, 3, 5};

const int j = 180;       // PWM usado para a velocidade, min == 0 e max == 255
Ultrasonic sensor(7, 4); // trig == 7; echo == 4

void setup()
{
  // Colocando os sensores como INPUT, e o resto como OUTPUT, tudo isso pelo array
  for (int i = 0; i < 5; i++)
    pinMode(pinos[i], INPUT);
  for (int i = 5; i < 9; i++)
    pinMode(pinos[i], OUTPUT);
  Serial.begin(9600);
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

void loop()
{
  // Essa parte é o bitSwift, criar uma variavel leitura do tipo byte, porem a gente so usa os bits dessa varaivel, a quantidade de bits depende de quantos sensores estao usando
  byte leitura = 0; // Definir sempre 0 quando definir algo como o for abaixo
  for (int i = 0; i < 4; i++)
    leitura |= digitalRead(pinos[i]) << i; // Colocando as entrada da tabela da verdade usando um bitshift automatico, o valor do i depende dos sensores
  leitura = (~leitura) & (0b00001111);     // Colocando um inversor para que funcione com a tabela da verdade, pq o sensor dectectar no branco, AND uma mascara para ir so os bits que eu quero
  Serial.print(leitura, BIN);
  Serial.print(" sens: ");
  Serial.println(sensor.read());

  if (sensor.read() <= 18)
  { // Se o sensor dectar que esta 18cm de distancia ativa a função de desviar
    // desv_d(j);
  }

  // Condições que usa a melhor situação dos sensores, o bit mais da direita é o s_leste e o bit mais na esquerda é o s_oeste
  // Algumas tem if com OR por conta que eles fazem a mesma coisa na condição.
  // Condição de 0011 ou 1100: é o algoritimo de 90 graus, pensando que so vai ativar no 90
  if (leitura == 0b0000) // Condição 1
  {
    mot1_hor(j);
    mot2_hor(j);
  }
  else if ((leitura == 0b0010) /*| (leitura == 0b0001)*/) // Condição 2
  {
    mot1_hor(j);
    mot2_anti(j);
  }
  else if (leitura == 0b0011) // Condição 4
  {
    mot1_hor(j);
    mot2_hor(j);
    delay(200);
    while (digitalRead(s_norte) == 1)
    {
      mot1_hor(j);
      mot2_anti(j);
    }
    delay(100);
  }
  else if ((leitura == 0b0100) /*| (leitura == 0b1000)*/) // Condição 5
  {
    mot1_anti(j);
    mot2_hor(j);
  }
  else if ((leitura == 0b0110) | (leitura == 0b1001)) // Condição 6
  {
    mot1_par();
    mot2_par();
    delay(100);
  }
  else if (leitura == 0b1100) // Condição 7
  {
    mot1_hor(j);
    mot2_hor(j);
    delay(200);
    while (digitalRead(s_norte) == 1)
    {
      mot1_anti(j);
      mot2_hor(j);
    }
    delay(100);
  }
  else if (leitura == 0b1111)
  {
    mot1_hor(j);
    mot2_hor(j);
    delay(200);
  }
  /*
  LEMBRAR DAS VARIAVEIS COM ENCRUZILHADA
  COMO ELE VAI PARAR?
  */
}
