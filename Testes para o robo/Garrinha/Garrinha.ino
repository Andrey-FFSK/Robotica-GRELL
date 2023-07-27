// Motor 1 = esquerda; Motor 2 = direita
#define mot_in1 3 // preto, esquerda, tras
#define mot_in2 5 // laranja, esquerda, frente
#define mot_in3 6 // branco, direita, frente
#define mot_in4 9 // amarelo, direita, tras

const int j = 180;

int pinos[] = {10, 11, 3, 6, 9, 2};

void setup() {
  Serial.begin(9600);
for (int i = 0; i < 6; i++)
    pinMode(pinos[i], OUTPUT);

}

void loop(){

  Serial.println("jogando garra");
analogWrite(mot_in4, 90);
delay(1000);

  Serial.println("esperando garra");
analogWrite(mot_in4, 0);
delay(3000);

  Serial.println("Puxando garra");
analogWrite(mot_in3, 130);
delay(1400);

  Serial.println("Esperando outra bola");
analogWrite(mot_in3, 0);
delay(5000);

//é direita, in3 == puxa pra dentro, in4 == joga pra fora

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