  #include "Include.h"
  
  #include <Encoder.h>

  void setup() {
    Serial.begin(9600);
  }

  void loop() {  
    while(enc.read() <= 550){
      mot1_hor(vel_esq);
      mot2_anti(vel_dir);
    Serial.println("Indo: " + String(enc.read()));
    }
    while(enc.read() >= 557){
      mot1_anti(vel_esq);
      mot2_hor(vel_dir);
      Serial.println("Voltando: " + String(enc.read()));
    }
    Serial.println(enc.read());
    mot1_par();
    mot2_par();
  }
