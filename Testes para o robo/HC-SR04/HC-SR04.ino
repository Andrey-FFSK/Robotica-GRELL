#include <Ultrasonic.h>
#define trig 12
#define echo 13

Ultrasonic sensor(trig, echo);

void setup(){
Serial.begin(9600);
}

void loop(){
Serial.println(sensor.read());
}