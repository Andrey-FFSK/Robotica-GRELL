/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/
#include "EEPROMLogger.h"

#define mim 0 
#define maxx 200

#define pin1 9

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  myservo.attach(pin1);  // attaches the servo on pin 9 to the servo object

   EEPROMLogger::print_log();
   EEPROMLogger::print_debug();
}

void loop() {
  
  /*
  myservo.write(maxx);
  Serial.println(maxx);
  EEPROMLogger::new_line(millis(), EEPROMLogger::ESQ, 0b110);
  delay(3000);

  Serial.println(mim);
  myservo.write(mim);
  EEPROMLogger::new_line(millis(), EEPROMLogger::DIR, 0b011);
  delay(3000);
  /*
  for (pos = mim; pos <= maxx; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = maxx; pos >= mim; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  delay(1000000);*/
}
