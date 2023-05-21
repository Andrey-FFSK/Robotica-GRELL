// Definindo as portas dos sensores e da portas H
#define s_oeste A4    // cinza, OUT1 
#define s_noroeste A3 // roxo, OUT2
#define s_norte A2    // verde, OUT4
#define s_nordeste A1 // azul, OUT3                                 
#define s_leste A0    // amarelo, OUT5

// Motor 1 = esquerda; Motor 2 = direita
#define mot_in1 5  // preto, esquerda, tras
#define mot_in2 6  // branco, esquerda, frente 
#define mot_in3 9  // cinza, direita, frente
#define mot_in4 10 // roxo, direita, tras MAL CONTATO 

// Usando array para colocar todos os pinos, coloquei os sensores invertido por causa do BitSwift em baixo
const PROGMEM int pinos[] = {A1, A3, A2, A1, A0, 5, 6, 9, 10};

// Definindo variaveis para as funções e o timing
int i = 150;

void setup()
{
  // Colocando os sensores como INPUT, e o resto como OUTPUT
  for (int i = 0; i < 5; i++)
    pinMode(pinos[i], INPUT);
  for (int i = 5; i < 9; i++)
    pinMode(pinos[i], OUTPUT);
    Serial.begin(9600);
}

// Inicio das funções, para cada caso, totalizando 6 funções diferente
void mot1_anti(int velo) // Função para o motor da esquerda girar no sentido anti horario com a velocidade variavel
{
  analogWrite(mot_in1, velo);
  analogWrite(mot_in2, 0);
}
void mot1_hor(int velo) // Função para o motor da esquerda girar no sentido horario com a velocidade variavel
{
  analogWrite(mot_in1, 0);
  analogWrite(mot_in2, velo);
}
void mot1_par() // Função para o motor da esquerda ficar parado
{
  analogWrite(mot_in1, 0);
  analogWrite(mot_in2, 0);
}

void mot2_anti(int velo) // Função para o motor da direita girar no sentido anti horario com a velocidade variavel
{
  analogWrite(mot_in3, 0);
  analogWrite(mot_in4, velo);
}
void mot2_hor(int velo) // Função para o motor da direita girar no sentido horario com a velocidade variavel
{
  analogWrite(mot_in3, velo);
  analogWrite(mot_in4, 0);
}
void mot2_par() // Função para o motor da direita ficar parado
{
  analogWrite(mot_in3, 0);
  analogWrite(mot_in4, 0);
}

void loop()
{

  byte leitura = 0; // Definir sempre 0 quando definir algo como o for abaixo
  for (int i = 0; i < 2; i++) 
    leitura |= digitalRead(pinos[i]) << i; //Colocando as entrada da tabela da verdade usando um bitshift automatico
  leitura = (~leitura) & 0b00000011;   // Colocando um inversor para que funcione com a tabela da verdade, com uma mascara para ir so os bits que eu quero
  Serial.println(leitura, BIN);   
  Serial.println(digitalRead(A3)); 

  // Condições que usa a tabela da verdade, consultar para ver
  if (leitura == 0b00) // Condição 1, FRENTE
  {
    mot1_hor(i);
    mot2_hor(i);
  }
  else if (leitura == 0b01) // Condição 2, VIRAR DIREITA
  {
    while(s_noroeste == 1){
      mot1_hor(i);
      mot2_anti(i);       
    }
            
  }
  
  else if (leitura == 0b10) // Condição 3, VIRAR ESQUERDA
  { 
    while(s_nordeste == 1){
      mot1_anti(i);
      mot2_hor(i);
    }
       
  }
  
  else if (leitura == 0b11) // Condição 4, PARADO
  {
    mot1_par();
    mot2_par();
  }
//mot1_par();
//mot2_par();

  
}

/***********************************************
Tem que ajeitar a tabela da verdade
// 0b00100. ~0b00000100 & 0b00011111
// x & 1 = x; x & 0 = 0;

https://circuitdigest.com/microcontroller-projects/arduino-uno-line-follower-robot
***********************************************/