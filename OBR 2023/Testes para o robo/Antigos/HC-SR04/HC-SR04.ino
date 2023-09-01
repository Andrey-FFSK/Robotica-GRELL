#include <Ultrasonic.h>
#define trig 7
#define echo 4

Ultrasonic sensor(trig, echo);

void setup(){
Serial.begin(9600);
}

void loop(){
Serial.println(sensor.read());
}
