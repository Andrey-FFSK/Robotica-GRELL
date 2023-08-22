#include "Include.h"

const int pinos[] = {s_oeste, s_noroeste, s_norte, s_nordeste, s_leste, esq, dir, esq_switch, dir_switch, incli, led_g, led_r, led_b, mot_in1, mot_in2, mot_in3, mot_in4};

int pos = 0; 

void setup() {
  Serial.begin(9600);
for (int i; i < 10; i++)
    pinMode(pinos[i], INPUT);
  for (int i = 10; i < 17; i++)
    pinMode(pinos[i], OUTPUT);

}

void loop()
{
for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo_garra.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo_garra.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }

}
