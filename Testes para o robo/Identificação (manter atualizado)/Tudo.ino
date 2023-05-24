int pins[] = {8, 10, 11, 12, 13};

void setup(){
  Serial.begin(9600);
  for(int i; i < 5; i++){
    pinMode(pins[i], INPUT);
  }
}

void loop(){

for(int i; i < 5; i++) Serial.print(digitalRead(pins[i]));
Serial.println();
  
}
