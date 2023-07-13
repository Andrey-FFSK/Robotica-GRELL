#include <Ultrasonic.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define W 128
#define H 64
#define lw 6
#define lh 8

const unsigned char aeia[] PROGMEM = {
    // 'bfcaab3c7ed1666ef086e690ec778ad0, 32x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x90, 0x00, 0x00, 0x01, 0xb0,
    0x00, 0x00, 0x00, 0x30, 0x01, 0x00, 0x01, 0xbc, 0x08, 0x20, 0x44, 0x34, 0x00, 0x40, 0x08, 0x28,
    0x00, 0x03, 0x10, 0x20, 0x05, 0xff, 0x80, 0x30, 0x07, 0xfe, 0x20, 0xa0, 0x0f, 0xdf, 0xee, 0x80,
    0x0f, 0xb9, 0x3d, 0x70, 0x1f, 0xe3, 0x73, 0xc0, 0x1d, 0xe0, 0xe3, 0xc0, 0x1f, 0xe0, 0x00, 0xc0,
    0x1f, 0x63, 0xa0, 0x40, 0x1f, 0x67, 0xc1, 0xc0, 0x1f, 0x47, 0x21, 0x40, 0x1b, 0x47, 0xe3, 0xc0,
    0x1f, 0x47, 0xc3, 0xc0, 0x1f, 0x47, 0xc3, 0xc0, 0x0e, 0x5f, 0xdb, 0x80, 0x1b, 0xdf, 0x83, 0xe0,
    0x03, 0x78, 0x00, 0x80, 0x00, 0x3f, 0xce, 0x00, 0x00, 0x6b, 0xf8, 0x00, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const unsigned char aeiapeqena[] PROGMEM = {
    // 'bfcaab3c7ed1666ef086e690ec778ad0, 16x16px
    0x00, 0x00, 0x00, 0x04, 0x00, 0x20, 0x04, 0x2a, 0x2f, 0xc8, 0x3d, 0xc0, 0x3e, 0xec, 0x74, 0x88,
    0x79, 0x88, 0x7b, 0x90, 0x7b, 0x98, 0x3f, 0x98, 0x17, 0x10, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00};

// Definindo as portas dos sensores e da portas H
#define s_oeste 8     // cinza, OUT1
#define s_noroeste 10 // branco, OUT2
#define s_norte 11    // verde, OUT4
#define s_nordeste 12 // preto, OUT3
#define s_leste 13    // azul, OUT5

// Motor 1 = esquerda; Motor 2 = direita
#define mot_in1 3 // preto, esquerda, tras
#define mot_in2 5 // laranja, esquerda, frente
#define mot_in3 6 // branco, direita, frente
#define mot_in4 9 // amarelo, direita, tras

// Usando array para colocar todos os pinos, coloquei os sensores invertido por causa do BitSwift em baixo
int pinos[] = {8, 13, 12, 11, 10, 5, 3, 6, 9};
Ultrasonic sensor(7, 4);

// Definindo variaveis
int temp = 500;
int ant = 0;

int o = 150;
float tensaoA0;

int n;

Adafruit_SSD1306 display(W, H, &Wire, -1);

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  Serial.begin(9600);
  for (int i; i < 5; i++)
    pinMode(pinos[i], INPUT);
  for (int i = 5; i < 9; i++)
    pinMode(pinos[i], OUTPUT);
  n = 0;
}

void loop()
{
  display.clearDisplay();

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

  display.setCursor(0, lh * 2);
  display.print("Leitura: ");
  for (int i = 11; i <= 15; i++)
    display.print(binString(leitura)[i]);
  display.print(" Bits");

  display.setCursor(0, lh * 3);
  display.print("Tensao: ");
  display.print(tensaoA0);
  display.print(" V");

  display.setCursor(0, lh * 4);
  display.print(sensor.read());
  display.print(" cm");

  display.drawBitmap(W - 32, H - 32 + sin(n * PI / 180) * 3, aeia, 32, 32, WHITE);
  display.drawBitmap(W - 16, -sin(n * PI / 180) * 1.5, aeiapeqena, 16, 16, WHITE);
  display.display();
  n = (n < 360) ? n + 36 : 0;

  display.display();

  Serial.print("Leitura: ");
  Serial.print(leitura, BIN);
  Serial.print("Bits / Tensão: ");
  Serial.print(tensaoA0);
  Serial.print("V / ");
  Serial.print(sensor.read());
  Serial.println("cm");
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

char *binString(unsigned short n)
{
  static char bin[17];
  int x;

  for (x = 0; x < 16; x++)
  {
    bin[x] = n & 0x8000 ? '1' : '0';
    n <<= 1;
  }
  bin[16] = '\0';

  return (bin);
}
