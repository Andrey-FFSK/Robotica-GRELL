int pins[] = {7,6,5,4,3};

void setup(){
  Serial.begin(9600);
  for(int i; i < 5; i++){
    pinMode(pins[i], INPUT);
  }
}

void loop(){
  Serial.print(digitalRead(7));
  Serial.print(digitalRead(6));
  Serial.print(digitalRead(5));
  Serial.print(digitalRead(4));
  Serial.println(digitalRead(3));
  
}
