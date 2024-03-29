#define in1 5  // Motor Esquerdo Tras, cabo preto
#define in2 6  // Motor Esquerdo Frente, cabo branco
#define in3 9  // Motor Direito Frente, cabo cinza
#define in4 10 // Motor Direito Tras, cabo roxo

int i = 100;
int temp = 1000;
int pinos[] = {5, 6, 9, 10};

void setup()
{
    for (i = 0; i < 4; i++)
        pinMode(pinos[i], OUTPUT);
}

void frente(int velo, int temp)
{
    analogWrite(in2, velo);
    analogWrite(in3, velo);
    delay(temp);
    analogWrite(in2, 0);
    analogWrite(in3, 0);
    delay(10);
}

void reixo(int velo, int temp)
{
    analogWrite(in2, velo);
    analogWrite(in4, velo);
    delay(temp);
    analogWrite(in2, 0);
    analogWrite(in4, 0);
    delay(10);
}

void leixo(int velo, int temp)
{
    analogWrite(in3, velo);
    analogWrite(in1, velo);
    delay(temp);
    analogWrite(in3, 0);
    analogWrite(in1, 0);
    delay(10);
}

void loop()
{
    // Ver foto da pista para conseguir compreender
    // primeira placa
    frente(i, 1600); // frente ate a curva da direita
    // segumda placa
    reixo(i, 1400);  // virar a direita, perfeito para direita
    frente(i, 700);  // frente ate a curva da esuqerda
    leixo(i, 1300);  // virar a esquerda
    frente(i, 800);  // frente ate a curva da esquerda, que é perquena
    leixo(i, 1400);  // virar a esuqerda
    frente(i, 1400); // frente ate a curva da direita
    reixo(i, 1300);  // virar a direita
    frente(i, 1000); // frente ate a curva da direita
    reixo(i, 1400);  // virar a direita,
    frente(i, 700);
    leixo(i, 1500);
    frente(i, 2000);
    // terceira placa
    reixo(i, 1300);
    frente(i, 1400);
    // quarta placa
    leixo(i, 1400);
    frente(i, 1000);
    reixo(i, 1300);
    frente(i, 700);
    reixo(i, 1400);
    frente(i, 800);
    leixo(i, 500);
    frente(i, 500);
    leixo(i, 500);
    frente(i, 100);
    leixo(i, 500);
    frente(i, 100);
    leixo(i, 500);
    frente(i, 950);
    reixo(i, 600);
    frente(i, 1750);
    // quinta placa
    reixo(i, 1300);
    frente(i, 4500);
    // sexta placa
    // setima placa
    reixo(i, 1300);
    // oitava placa
    frente(i, 1000);
    reixo(i, 500);
    frente(i, 700);
    leixo(i, 500);
    frente(i, 300);
    leixo(i, 900);
    frente(i, 900);
    reixo(i, 500);
    frente(i, 700);
    reixo(i, 700);
    frente(i, 950);
    leixo(i, 550);
    frente(i, 1500);
    reixo(i, 1360);

    delay(100000);
}
