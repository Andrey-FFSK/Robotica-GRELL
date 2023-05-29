// Definindo as portas dos sensores e da portas H
#define s_oeste 8    // rosa, OUT1 
#define s_noroeste 10 // amarelo, OUT2
#define s_norte 11    // azul, OUT4
#define s_nordeste 12 // vermelho, OUT3                                 
#define s_leste 13    // marrom, OUT5

// Motor 1 = esquerda; Motor 2 = direita
#define mot_in1 5  // preto, direita, tras
#define mot_in2 3  // laranja, direita, frente 
#define mot_in3 6  // branco, esquerda, frente
#define mot_in4 9 // amarelo, esquerda, tras

// Usando array para colocar todos os pinos, coloquei os sensores invertido por causa do BitSwift em baixo
int pinos[] = {8, 10, 11, 12, 13, 5, 3, 6, 9};

//Definindo variaveis
int temp = 500;
int ant = 0;
int o = 100;

void setup(){
  Serial.begin(9600);
  for(int i; i < 5; i++) pinMode(pinos[i], INPUT);
  for(int i = 5; i < 9; i++) pinMode(pinos[i], OUTPUT);
  
}

void loop(){

mot1_hor(o);
mot2_hor(o);

//mot1_anti(o);
//mot2_anti(o);

if(millis() - ant >= temp){
  ant = millis();
byte leitura = 0;
for(int i = 0; i < 5; i++) leitura |= digitalRead(pinos[i]) << i;
leitura = (~leitura) & 0b00011111;
Serial.println(leitura, BIN);
}
  
}

// Inicio das funções, para cada caso, totalizando 6 funções diferente
void mot1_anti(int velo) // Função para o motor da esquerda girar no sentido anti horario com a velocidade variavel
{
  analogWrite(mot_in3, 0);
  analogWrite(mot_in4, velo);
}
void mot1_hor(int velo) // Função para o motor da esquerda girar no sentido horario com a velocidade variavel
{
  analogWrite(mot_in3, velo);
  analogWrite(mot_in4, 0);
}
void mot1_par() // Função para o motor da esquerda ficar parado
{
  analogWrite(mot_in3, 0);
  analogWrite(mot_in4, 0);
}

void mot2_anti(int velo) // Função para o motor da direita girar no sentido anti horario com a velocidade variavel
{
  analogWrite(mot_in1, velo);
  analogWrite(mot_in2, 0);
}
void mot2_hor(int velo) // Função para o motor da direita girar no sentido horario com a velocidade variavel
{
  analogWrite(mot_in1, 0);
  analogWrite(mot_in2, velo);
}
void mot2_par() // Função para o motor da direita ficar parado
{
  analogWrite(mot_in1, 0);
  analogWrite(mot_in2, 0);
}
