#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define W 128 // OLED display width, in pixels
#define H 64 // OLED display height, in pixels

Adafruit_SSD1306 display(W, H, &Wire, -1);

int n;
const int cX = 24;
const int cY = H-24;

void setup() {
  	display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  	display.clearDisplay();
  	display.setCursor(0, 0);
  	display.setTextColor(WHITE);

  	n = 0;
}

void loop() {
	display.clearDisplay();
  	display.drawPixel(cX, cY, WHITE);
	setas();

	//seta_ani(0, n);
	//seta_ani(1, n);

	seta_cima(n);
	seta_esquerda(n);
	seta_direita(n);
	seta_baixo(n);

	n = (n>3) ? 0 : n+1;
	display.display();
	//delay(100);
}

void setas() {
	//cima
	display.drawRect(cX-2,cY-9, 5, 6, WHITE);
	display.drawTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);

	//baixo
	display.drawRect(cX-2, cY+4, 5, 6, WHITE);
	display.drawTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);

	//direita
	display.drawRect(cX+4, cY-2, 6, 5, WHITE);
	display.drawTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);

	//esquertfa
	display.drawRect(cX-9, cY-2, 6, 5, WHITE);
	display.drawTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
}

void seta_cima(int n) {
	switch(n) {
		case 0:
			display.drawRect(cX-2,cY-9, 5, 6, WHITE);
			display.drawTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);
			break;
					
		case 1:
			display.drawRect(cX-2,cY-9, 5, 6, WHITE);
			display.fillRect(cX-2,cY-6, 5, 3, WHITE);
			display.drawTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);
			break;
					
		case 2:
			display.fillRect(cX-2,cY-9, 5, 6, WHITE);
			display.drawTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);
			break;

		case 3:
			display.fillRect(cX-2,cY-9, 5, 6, WHITE);
			display.fillTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);
			break;
	}
}

void seta_direita(int n)  {
	switch(n) {
		case 0:
			display.drawRect(cX+4, cY-2, 6, 5, WHITE);
			display.drawTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);
			break;

		case 1:
			display.drawRect(cX+4, cY-2, 6, 5, WHITE);
			display.fillRect(cX+4, cY-2, 3, 5, WHITE);
			display.drawTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);
			break;

		case 2:
			display.fillRect(cX+4, cY-2, 6, 5, WHITE);
			display.drawTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);
			break;

		case 3:
			display.fillRect(cX+4, cY-2, 6, 5, WHITE);
			display.fillTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);
			break;
	}
}

void seta_baixo(int n) {
	switch(n) {
		case 0:
			display.drawRect(cX-2, cY+4, 5, 6, WHITE);
			display.drawTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);
			break;
		
		case 1:
			display.drawRect(cX-2, cY+4, 5, 6, WHITE);
			display.fillRect(cX-2, cY+4, 5, 3, WHITE);
			display.drawTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);
			break;
		
		case 2:
			display.fillRect(cX-2, cY+4, 5, 6, WHITE);
			display.drawTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);
			break;

		case 3:
			display.fillRect(cX-2, cY+4, 5, 6, WHITE);
			display.fillTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);
			break;
	}
}

void seta_esquerda(int n) {
	switch(n) {
		case 0:
			display.drawRect(cX-9, cY-2, 6, 5, WHITE);
			display.drawTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
			break;
		
		case 1:
			display.drawRect(cX-9, cY-2, 6, 5, WHITE);
			display.fillRect(cX-6, cY-2, 3, 5, WHITE);
			display.drawTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
			break;
		
		case 2:
			display.fillRect(cX-9, cY-2, 6, 5, WHITE);
			display.drawTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
			break;

		case 3:
			display.fillRect(cX-9, cY-2, 6, 5, WHITE);
			display.fillTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
			break;
	}
}

/*
// 0 cima
// 1 direita
// 2 baixlo
// 3 esquerda
void seta_ani(const int lado, int n) {

	switch(lado) {
		case 0: //cima
			switch(n) {
				case 0:
					display.drawRect(cX-2,cY-9, 5, 6, WHITE);
					display.drawTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);
					break;
				
				case 1:
					display.drawRect(cX-2,cY-9, 5, 6, WHITE);
					display.fillRect(cX-2,cY-6, 5, 3, WHITE);
					display.drawTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);
					break;
				
				case 2:
					display.fillRect(cX-2,cY-9, 5, 6, WHITE);
					display.drawTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);
					break;

				case 3:
					display.fillRect(cX-2,cY-9, 5, 6, WHITE);
					display.fillTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);
					break;
			}
			break;
		
		case 1: //direita
			switch(n) {
				case 0:
					display.drawRect(cX+4, cY-2, 6, 5, WHITE);
					display.drawTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);
					break;
				
				case 1:
					display.drawRect(cX+4, cY-2, 6, 5, WHITE);
					display.fillRect(cX+4, cY-2, 3, 5, WHITE);
					display.drawTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);
					break;
				
				case 2:
					display.fillRect(cX+4, cY-2, 6, 5, WHITE);
					display.drawTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);
					break;

				case 3:
					display.fillRect(cX+4, cY-2, 6, 5, WHITE);
					display.fillTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);
					break;
			}
			break;
		
		case 2: //baixoç
			switch(n) {
				case 0:
					display.drawRect(cX-2, cY+4, 5, 6, WHITE);
					display.drawTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);
					break;
				
				case 1:
					display.drawRect(cX-2, cY+4, 5, 6, WHITE);
					display.fillRect(cX-2, cY+4, 5, 3, WHITE);
					display.drawTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);
					break;
				
				case 2:
					display.fillRect(cX-2, cY+4, 5, 6, WHITE);
					display.drawTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);
					break;

				case 3:
					display.fillRect(cX-2, cY+4, 5, 6, WHITE);
					display.fillTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);
					break;
			}
			break;

		case 3: //esqurda
			switch(n) {
				case 0:
					display.drawRect(cX-9, cY-2, 6, 5, WHITE);
					display.drawTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
					break;
				
				case 1:
					display.drawRect(cX-9, cY-2, 6, 5, WHITE);
					display.fillRect(cX-6, cY-2, 3, 5, WHITE);
					display.drawTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
					break;
				
				case 2:
					display.fillRect(cX-9, cY-2, 6, 5, WHITE);
					display.drawTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
					break;

				case 3:
					display.fillRect(cX-9, cY-2, 6, 5, WHITE);
					display.fillTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
					break;
			}
			break;
	}
}
*/
