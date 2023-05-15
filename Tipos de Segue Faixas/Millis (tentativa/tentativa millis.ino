#define in1 3 // Motor Esquerdo Tras, cabo amarelo
#define in2 5 // Motor Esquerdo Frente, cabo laranja
#define in3 6 // Motor Direito Frente, cabo vermelho
#define in4 9 // Motor Direito Tras, cabo cinza

int i = 100;
unsigned long int ant = 0;
unsigned long int ant2 = 0;
unsigned long int ant3 = 0;
unsigned long int ant4 = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(in1, OUTPUT); // digital IN1
  pinMode(in2, OUTPUT); // digital IN2
  pinMode(in3, OUTPUT); // digital IN3
  pinMode(in4, OUTPUT); // digital IN4
}

void frente(int velo, int temp)
{
  analogWrite(in2, velo);
  analogWrite(in3, velo);
  if (millis(); -ant >= temp)
  {
    ant = millis();
    analogWrite(in2, 0);
    analogWrite(in3, 0);
  }
}

void reixo(int velo, int temp)
{
  if (millis() - ant2 >= temp)
  {
    ant = millis();
    analogWrite(in2, velo);
    analogWrite(in4, velo);
  }
}

void leixo(int velo, int temp)
{
  if (millis() - ant3 >= temp)
  {
    ant = millis();
    analogWrite(in3, velo);
    analogWrite(in1, velo);
  }
}

void parar(int temp)
{
  if (millis() - ant4 >= temp)
  {
    ant = millis();
    analogWrite(in1, 0);
    analogWrite(in2, 0);
    analogWrite(in3, 0);
    analogWrite(in4, 0);
  }
}

void loop()
{
  // Ver foto da pista para conseguir compreender
  // primeira placa

  frente(i, 500);
  Serial.print("Millis");
  Serial.print("\t");
  Serial.println(millis());
  Serial.print("ant");
  Serial.print("\t");
  Serial.println(ant);
  Serial.print("ant4");
  Serial.print("\t");
  Serial.println(ant4);
  Serial.println();
}
