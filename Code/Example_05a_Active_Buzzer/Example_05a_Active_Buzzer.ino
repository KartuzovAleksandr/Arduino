int pinBuzzer = 12;
void setup() {
  pinMode(pinBuzzer, OUTPUT);
}
void loop() { 
   digitalWrite(pinBuzzer, HIGH);
   delay(3000); 
   digitalWrite(pinBuzzer, LOW);
   delay(1000);
}
