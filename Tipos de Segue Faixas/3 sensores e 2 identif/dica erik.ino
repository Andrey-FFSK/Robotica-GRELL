
// Definindo as portas dos sensores e da portas H
#define s_oeste 8    // rosa, OUT1 
#define s_noroeste 10 // amarelo, OUT2
#define s_norte 11    // azul, OUT4
#define s_nordeste 12 // vermelho, OUT3                                 
#define s_leste 13    // marrom, OUT5

// Motor 1 = esquerda; Motor 2 = direita
#define mot_in1 3  // preto, esquerda, tras
#define mot_in2 5  // laranja, esquerda, frente
#define mot_in3 6  // branco, direita, frente
#define mot_in4 9 // amarelo, direita, tras

// Usando array para colocar todos os pinos, coloquei os sensores invertido por causa do BitSwift em baixo
int pinos[] = {12, 11, 10, 8, 13, 9, 6, 3, 5};
byte Condicao[] = {{00000},{00001},{00010},{00011},{00100},{00101},{00110},{00111},{01000},{01001},{01010},{01011},{01100},{01101},{01110},{01111},{10000},{10001},{10010},{10011},{10100},{10101},{10110},{10111},{11000},{11001},{11010},{11011},{11100},{11101},{11110},{11111}};

int j = 150;

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
  for (int i = 0; i < 3; i++)
    leitura |= digitalRead(pinos[i]) << i; // Colocando as entrada da tabela da verdade usando um bitshift automatico
  leitura = (~leitura) & (0b00000111); // Colocando um inversor para que funcione com a tabela da verdade, AND uma mascara para ir so os bits que eu quero
  Serial.println(leitura, BIN);
//0 e 3 = frente; 6 e 8 = vazio; 2 e 4 = direita; 5 e 7 = esquerda
  switch(leitura){
    case Condicao[0] | Condicao[2]: mot1_hor(j); mot2_hor(j);  break;
    case Condicao[1] | Condicao[3]:if(s_leste == 1){mot1_hor(j); mot2_hor(j); delay(500); mot1_hor(j); mot2_anti(j); delay(500);} else{mot1_hor(j); mot2_anti(j);} break;
    case Condicao[4] | Condicao[6]:if(s_oeste == 1){ mot1_hor(j); mot2_hor(j) delay(500); mot1_anti(j); mot2_hor(j); delay(500);} else{mot1_anti(j); mot2_hor(j);} break;
  } 
}
