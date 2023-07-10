#define led_r A2
#define led_g A3
#define led_b A2
#define esq A4
#define dir A0

int pin[] = {A2, A1, A3, A0, A4};

void setup(){
for(int i = 0; i < 3; i++) pinMode(pin[i], OUTPUT);
for(int i = 3; i < 5; i++) pinMode(pin[i], INPUT);
Serial.begin(9600);
}

void loop(){
 //digitalWrite(led_r, 1);
 //digitalWrite(led_g, 1);
 //digitalWrite(led_b, 1);
Serial.print("Esq: ");
Serial.print(analogRead(esq));
Serial.print(" | Dir: ");
Serial.println(analogRead(dir));

}
//AZUL RILHANDO QUANDO LIGA
//LEMRAR DO CAO DO US E DA ATERIA, USAR ATERIA
