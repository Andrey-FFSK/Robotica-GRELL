// Identificação
#include "Oled.h"
#include "Include.h"

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

// Usando array para colocar todos os pinos, coloquei os sensores invertido por causa do BitSwift em baixo
const int pinos[] = {s_oeste, s_noroeste, s_norte, s_nordeste, s_leste, esq, dir, esq_switch, dir_switch, incli, led_g, led_r, led_b, mot_in1, mot_in2, mot_in3, mot_in4};

float tensaoA0;

int n;

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  Serial.begin(9600);
  for (int i; i < 10; i++)
    pinMode(pinos[i], INPUT);
  for (int i = 10; i < 17; i++)
    pinMode(pinos[i], OUTPUT);
  n = 0;
}

void loop()
{
  display.clearDisplay();

  //digitalWrite(led_r, 1);
  digitalWrite(led_g, 1);
  //digitalWrite(led_b, 1);
  //digitalWrite(led_g_meio, 1);

  //analogWrite(mot_in2, o);

  //mot1_hor(vel_esq);
  //mot2_hor(vel_dir);

  // mot1_anti(vel_esq);
  // mot2_anti(vel_dir);

  byte leitura = 0;
  for (int i = 0; i < 5; i++)
    leitura |= digitalRead(pinos[i]) << i;
  leitura = (~leitura) & 0b00011111;
  tensaoA0 = (div(A0) * 5) / 1024.0;
  tensaoA0 *= 8.4;
  sensi();


  display.setCursor(0, lh * 2);
  display.print("Leitura: ");
  for (int i = 11; i <= 15; i++)
    display.print(binString(leitura)[i]);
  display.print(" Bits");
  /*
  display.setCursor(0, lh * 3);
  display.print("Tensao: ");
  display.print(tensaoA0);
  display.print(" V");*/

  display.setCursor(0, lh * 4);
  display.print("Olho: ");
  display.print(ult_meio.read());
  display.print(" cm");

  display.setCursor(0, lh * 5);
  display.print("Esq: ");
  display.print(m_esq);
  display.print("(");
  display.print(analogRead(esq));
  display.print(")");

  display.setCursor(0, lh * 6);
  display.print("Dir: ");
  display.print(m_dir);
  display.print("(");
  display.print(analogRead(dir));
  display.print(")");

  display.setCursor(0, lh * 7);
  display.print("Meio: ");
  display.print(m_meio);
  display.print("(");
  display.print(analogRead(meio));
  display.print(")");

  display.setCursor(0, lh * 8);
  display.print("Enc: ");
  display.print(enc.read());
  display.print(" pas");

  display.setCursor(0, lh * 9);
  display.print("Incli: ");
  display.print(digitalRead(incli));

  display.drawBitmap(W - 32, H - 32 + sin(n * PI / 180) * 3, aeia, 32, 32, WHITE);
  display.drawBitmap(W - 16, -sin(n * PI / 180) * 1.5, aeiapeqena, 16, 16, WHITE);
  display.display();
  n = (n < 360) ? n + 36 : 0;

  display.display();

  Serial.print("Leitura: ");
  Serial.print(leitura, BIN);
  Serial.print("Bits / Olho: ");
  //Serial.print(tensaoA0);
  //Serial.print("V / Olho:");
  Serial.print(ult_meio.read());
  Serial.print("cm / Esq: ");
  Serial.print(m_esq);
  Serial.print("(");
  Serial.print(analogRead(esq));
  Serial.print(") / Dir: ");
  Serial.print(m_dir);
  Serial.print("(");
  Serial.print(analogRead(dir));
  Serial.print(") / Meio: ");
  Serial.print(m_meio);
  Serial.print("(");
  Serial.print(analogRead(meio));
  Serial.print(") / Enc: ");
  Serial.print(enc.read());
  Serial.print("pas / esq_switch: ");
  Serial.print(digitalRead(esq_switch));
  Serial.print(" / dir_switch: ");
  Serial.print(digitalRead(dir_switch));
  Serial.print(" / Incli: ");
  Serial.print(digitalRead(incli));
  Serial.println(" / ");
  

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
