#define led_r 11
#define led_g 12
#define led_b 10
#define esq A1
#define dir A5

int pin[] = {11, 10, 12, A1, A5};

void setup(){
for(int i = 0; i < 3; i++) pinMode(pin[i], OUTPUT);
for(int i = 3; i < 5; i++) pinMode(pin[i], INPUT);
Serial.begin(9600);
}

void loop(){
 digitalWrite(led_g, 1);
Serial.print("Esq: ");
Serial.print(analogRead(esq));
Serial.print(" | Dir: ");
Serial.println(analogRead(dir));

}
//AZUL RILHANDO QUANDO LIGA
//LEMRAR DO CAO DO US E DA ATERIA, USAR ATERIA
