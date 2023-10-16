// AnalogRead
#include "Declarar.h"
#include "Definir.h" // Dando include nas variaveis e funções
#include "Oled.h"    // Dando include no arquivo que tem as bibliotecas e criando o objeto do display oled

// Usando array para colocar todos os pinos, coloquei os sensores em uma certa posição por causa do BitSwift em baixo
const int pinos[] = {s_oeste, s_norte, s_leste, s_noroeste, s_nordeste, esq, dir, led_g, mot_in1, mot_in2, mot_in3, mot_in4};

byte leitura;

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Protocolo para iniciar o display
  display.setTextColor(WHITE);               // Colocando cor para o texto
  display.setRotation(3);                    // rotacionando a tela para ficar condizente com as setas

  // Colocando os sensores como INPUT, e o resto como OUTPUT, tudo isso pelo array
  for (int i = 0; i < 7; i++) // Usando o array para fazer os pinmode como input
    pinMode(pinos[i], INPUT);
  for (int i = 7; i < 12; i++) // Usando o array para fazer que o resto seja como output
    pinMode(pinos[i], OUTPUT);

  Serial.begin(9600); // Iniciando o serial monitor
}
void loop()
{
  display.clearDisplay();  // Limpando o display no inicio do loop
  display.setCursor(0, 0); // Setando para todos iniciar no inicio da tela

  //  Essa parte é o bitSwift, criar uma variavel leitura do tipo byte, porem a gente so usa os bits dessa varaivel, a quantidade de bits depende de quantos sensores estao usando
  leitura = 0; // Definir sempre 0 quando definir algo como o for abaixo
  for (int i = 0; i < 3; i++)
    leitura |= digitalRead(pinos[i]) << i; // Colocando as entrada da tabela da verdade usando um bitshift automatico, o valor do i depende dos sensores
  leitura = (~leitura) & (0b00000111);     // Colocando um inversor para que funcione com a tabela da verdade, pq o sensor dectectar no branco, AND uma mascara para ir so os bits que eu quero

  OLED::abeia_grande(26 - 24, 85 - 24);
  OLED::abeia_pequena(55 - 8, 75 - 8, 40, -6);
  OLED::setas();
  // display.display();

  if (ult_meio.read() <= 3) // Se o sensor dectar que esta distancia ativa a função de desviar
  {
    if (cont_desv < max_cont_desv)
    {
      display.print("Desviando obsta");
      display.display();
      desv(false); //* esq = false; dir = true
      cont_desv++;
    }
    else
    {
      mot1_par();
      mot2_par();
      delay(100000000);
      // Colocar aqui a habilitacao de area de resgate
    }
  }

  //* Parte em que ele faz o micro ajuste (pensando que o valor maior fica no branco)
  if ((analogRead(s_noroeste) <= analog_esq) && (analogRead(s_nordeste) >= analog_dir)) //! Fazer micro ajuste para esquerda
  {
    if (ver == false)
    {
      mot1_hor();
      mot2_anti();
      display.print("Esquerda");
      OLED::seta_esq();
      Serial.println("leitura == 0010 / ajustando para esquerda");
    }
    else
    {
      display.print("E_Tras");
      enc_re(enc_pas_outro);
      ver = false;
    }
  }
  else if ((analogRead(s_noroeste) >= analog_esq) && (analogRead(s_nordeste) <= analog_dir)) //! Fazer micro ajuste para direita
  {
    if (ver == false)
    {
      mot1_anti();
      mot2_hor();
      display.print("Direita");
      OLED::seta_dir();
      Serial.println("leitura == 0100 / ajustando para direita");
    }
    else
    {
      display.print("D_Tras");
      enc_re(enc_pas_outro);
      ver = false;
    }
  }
  else //! Precisa de else para regular direito
  {
    // Condições que usa a melhor situação dos sensores, o bit mais da direita é o s_leste e o bit mais na esquerda é o s_oeste
    // Alguns nao tem break; porque faz a mesma coisa
    switch (leitura)
    {
    case 0b000:
        /*display.print("000 / ver_branco");
        display.display();
        ver_branco();
      break;*/
    case 0b010: //! Caso de ele ir so pra frente
      if (ver == false)
      {
        mot1_hor();
        mot2_hor();
        display.print("010 / frente");
        OLED::seta_cima();
        Serial.println("leitura = 000; leitura = 010");
      }
      else
      {
        display.print("000 / Tras");
        enc_re(enc_pas_outro);
        ver = false;
      }
      break;
    case 0b100:
    case 0b110: //! Casos de fazer o esquerda 90
      if (ver == false)
      {
        display.print("100 / parar");
        mot1_par();
        mot2_par();
        delay(mot_par);
        ver = true;
      }
      else
      {
        ver = false;
        display.print("100 / Esq_90");
        OLED::seta_esq();
        display.display();
        esq_90();
      }
      break;
    case 0b001:
    case 0b011: //! Casos de fazer o direita 90
      if (ver == false)
      {
        display.print("001 / parar");
        display.display();
        mot1_par();
        mot2_par();
        delay(mot_par);
        ver = true;
      }
      else
      {
        display.print("001 / Dir_90");
        OLED::seta_dir();
        display.display();
        dir_90();
        ver = false;
      }
      break;
    case 0b111: //! Caso de encruzilhada
      if (ver == false)
      {
        display.print("111 / frente");
        mot1_hor();
        mot2_hor();
      }
      else
      {
        display.print("111 / re");
        enc_re(enc_pas_outro);
        ver = false;
      }
      break;
    default:
      break;
    }
  }
  display.display();
  OLED::frame_incr();
}
