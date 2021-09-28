int pinRelay = 3;
void setup() {
    Serial.begin(9600);
    pinMode(pinRelay,OUTPUT);
}
void loop() {
  digitalWrite(pinRelay,HIGH);
  Serial.print("LED illumination");
  delay(3000); 
  digitalWrite(pinRelay,LOW);
  Serial.print("LED is off");
  delay(2000);
}
