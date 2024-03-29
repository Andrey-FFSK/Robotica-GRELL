// Definindo as portas dos sensores e da portas H
#define s_oeste 6
#define s_noroeste 5
#define s_norte 4
#define s_nordeste 3
#define s_leste 2

#define mot1_lig 11 // cinza, esquerda
#define mot2_lig 9  // laranja, direita

#define mot2_in2 13 // preto, mot2, atras
#define mot2_in1 12 // azul, mot2, frente
#define mot1_in1 8  // amarelo, mot1, frente
#define mot1_in2 7  // vermelho, mot1, atras

// Usando array para colocar todos os pinos
int pinos[] = {6, 5, 4, 3, 2, 12, 13, 11, 9, 10, 8};

// Definindo variaveis para as funções e o timing, a velocidade vai ser responsavel para colocar no motor1ou2_lig
int temp = 1000;
int velo_t = 255;
int velo_m = 127;

void setup()
{
  // Começando com o Serial.begin e colocando tudo em pinMode OUTPUT
  Serial.begin(9600);
  for (int i = 0; i < 11; i++)
  {
    pinMode(pinos[i], OUTPUT);
  }
}

// Inicio das funções, para cada caso, totalizando 10 funções diferente
void mot1_anti(int velo) // Função para o motor 1 girar no sentido anti horario com a velocidade variavel
{
  analogWrite(mot1_lig, velo);
  digitalWrite(mot1_in1, 0);
  digitalWrite(mot1_in2, 1);
}

void mot1_hor(int velo) // Função para o motor 1 girar no sentido horario com a velocidade variavel
{
  analogWrite(mot1_lig, velo);
  digitalWrite(mot1_in1, 1);
  digitalWrite(mot1_in2, 0);
}

void mot1_par() // Função para o motor 1 ficar parado (mot1_lig LOW)
{
  analogWrite(mot1_lig, 0);
}

void mot2_anti(int velo) // Função para o motor 2 girar no sentido anti horario com a velocidade variavel
{
  analogWrite(mot2_lig, velo);
  digitalWrite(mot2_in1, 0);
  digitalWrite(mot2_in2, 1);
}

void mot2_hor(int velo) // Função para o motor 2 girar no sentido horario com a velocidade variavel
{
  analogWrite(mot2_lig, velo);
  digitalWrite(mot2_in1, 1);
  digitalWrite(mot2_in2, 0);
}

void mot2_par() // Função para o motor 2 ficar parado (mot2_lig LOW)
{
  analogWrite(mot2_lig, 0);
}

void loop()
{
  byte ff[] = {0, 0, 0, 1, 1}; // Não vai funcionar no robo, definindo os sensores, INVERTIDO

  byte leitura = 0; // Definir sempre 0 quando definir algo como o for abaixo
  for (int i = 0; i < 5; i++)
    leitura |= ff[i] << i;      // Colocando as entrada da tabela da verdade usando mm bitshift automatico
  Serial.println(leitura, BIN); // Impimindo no serial para testes, e usando BIN para mostrar em binario

  // Condições que usa a tabela da verdade, consultar para ver
  if (leitura == 0b00000) // Condição 1
  {
    mot1_hor(100);
    mot2_hor(100);
  }
  else if (leitura == 0b00001) // Condição 2
  {
    mot1_hor(100);
    mot2_hor(100);
  }
  else if (leitura == 0b00010) // Condição 3
  {
    mot1_hor(100);
    mot2_hor(100);
  }
  else if (leitura == 0b00011) // Condição 4
  {
    mot1_hor(100);
    mot2_anti(100);
  }
  else if (leitura == 0b00100) // Condição 5
  {
    mot1_hor(100);
    mot2_hor(100);
  }
  else if (leitura == 0b00101) // Condição 6
  {
  }
  else if (leitura == 0b00110) // Condição 7
  {
    mot1_hor(100);
    mot2_hor(100);
  }
  else if (leitura == 0b00111) // Condição 8
  {
    mot1_hor(100); // Ver. frente
    mot2_hor(100);
  }
  else if (leitura == 0b01000) // Condição 9
  {
    mot1_hor(100);
    mot2_hor(100);
  }
  else if (leitura == 0b01001) // Condição 10
  {
    mot1_anti(100);
    mot2_hor(100);
  }
  else if (leitura == 0b01010) // Condição 11
  {
    mot1_hor(100);
    mot2_hor(100);
  }
  else if (leitura == 0b01011) // Condição 12
  {
    mot1_hor(100);
    mot2_anti(100);
  }
  else if (leitura == 0b01100) // Condição 13
  {
    mot1_hor(100);
    mot2_hor(100);
  }
  else if (leitura == 0b01101) // Condição 14
  {
  }
  else if (leitura == 0b01110) // Condição 15
  {
    mot1_hor(100);
    mot2_hor(100);
  }
  else if (leitura == 0b01111) // Condição 16
  {
    mot1_hor(100);
    mot2_anti(100);
  }
  else if (leitura == 0b10000) // Condição 17
  {
    mot1_anti(100);
    mot2_anti(100);
  }
  else if (leitura == 0b10001) // Condição 18
  {
    mot1_anti(100);
    mot2_anti(100);
  }
  else if (leitura == 0b10010) // Condição 19
  {
    mot1_hor(100);
    mot2_anti(100);
  }
  else if (leitura == 0b10011) // Condição 20
  {
    mot1_hor(100);
    mot2_anti(100);
  }
  else if (leitura == 0b10100) // Condição 21
  {
    mot1_hor(100);
    mot2_hor(100);
  }
  else if (leitura == 0b10101) // Condição 22
  {
    mot1_hor(100);
    mot2_hor(100);
  }
  else if (leitura == 0b10110) // Condição 23
  {
  }
  else if (leitura == 0b10111) // Condição 24
  {
    mot1_hor(100);
    mot2_anti(100);
  }
  else if (leitura == 0b11000) // Condição 25
  {
    mot1_anti(100);
    mot2_hor(100);
  }
  else if (leitura == 0b11001) // Condição 26
  {
    mot1_anti(100);
    mot2_hor(100);
  }
  else if (leitura == 0b11010) // Condição 27
  {
    mot1_anti(100);
    mot2_hor(100);
  }
  else if (leitura == 0b11011) // Condição 28
  {
  }
  else if (leitura == 0b11100) // Condição 29
  {
    mot1_anti(100);
    mot2_hor(100);
  }
  else if (leitura == 0b11101) // Condição 30
  {
    mot1_anti(100);
    mot2_hor(100);
  }
  else if (leitura == 0b11110) // Condição 31
  {
  }
  else if (leitura == 0b11111) // Condição 32
  {
    mot1_par();
    mot2_par();
  }
}

/***********************************************
Tem que ajeitar a tabela da verdade
Esse serve como teste e nao vai ser usado para o robo
Lembrar dos input pq nao é certinho

https://circuitdigest.com/microcontroller-projects/arduino-uno-line-follower-robot
https://www.manualdaeletronica.com.br/ponte-h-o-que-e-como-funciona/
https://www.tinkercad.com/things/b8lj8q4rLVm?sharecode=XG58k9cH3BYTgXNEN8JuCELvxrjPnArmHrRolu-5djQ
***********************************************/
