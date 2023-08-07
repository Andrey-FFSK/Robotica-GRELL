#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define W 128 
#define H 64 

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

  switch(n) {
    case 0:
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
			
      break;
		case 1:
			//cima
    	display.drawRect(cX-2,cY-9, 5, 6, WHITE);
			display.fillRect(cX-2,cY-6, 5, 3, WHITE);
    	display.drawTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);

    	//baixo
			display.drawRect(cX-2, cY+4, 5, 6, WHITE);
			display.fillRect(cX-2, cY+4, 5, 3, WHITE);
			display.drawTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);

			//direita
			display.drawRect(cX+4, cY-2, 6, 5, WHITE);
			display.fillRect(cX+4, cY-2, 3, 5, WHITE);
			display.drawTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);

	  	//esquertfa
			display.drawRect(cX-9, cY-2, 6, 5, WHITE);
			display.fillRect(cX-6, cY-2, 3, 5, WHITE);
			display.drawTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
			
    	break;
    case 2:
	    //cima
    	display.fillRect(cX-2,cY-9, 5, 6, WHITE);
    	display.drawTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);

    	//baixo
			display.fillRect(cX-2, cY+4, 5, 6, WHITE);
			display.drawTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);

			//direita
			display.fillRect(cX+4, cY-2, 6, 5, WHITE);
			display.drawTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);

	  	//esquertfa
			display.fillRect(cX-9, cY-2, 6, 5, WHITE);
			display.drawTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
    	break;
    case 3:
    	//cima
    	display.fillRect(cX-2,cY-9, 5, 6, WHITE);
    	display.fillTriangle(cX-4,cY-9, cX+4,cY-9, cX,cY-13, WHITE);

    	//baixo
			display.fillRect(cX-2, cY+4, 5, 6, WHITE);
			display.fillTriangle(cX-4,cY+9, cX+4,cY+9, cX,cY+13, WHITE);

			//direita
			display.fillRect(cX+4, cY-2, 6, 5, WHITE);
			display.fillTriangle(cX+9,cY-4, cX+9,cY+4, cX+13,cY, WHITE);

	  	//esquertfa
			display.fillRect(cX-9, cY-2, 6, 5, WHITE);
			display.fillTriangle(cX-9,cY-4, cX-9,cY+4, cX-13,cY, WHITE);
    	break;
	}

	delay(100);
	n=(n>3)?0:n+1;
	display.display();
}
