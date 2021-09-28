int sensorPin=A0;  // аналоговый вход для датчика
int ledPin=13;     // втроенный LED Arduino 
int sensorValue=0; // значение датчика
void setup() {
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  sensorValue =  analogRead(sensorPin);
  digitalWrite(ledPin,  HIGH); 
  delay(sensorValue); 
  digitalWrite(ledPin,  LOW);
  delay(sensorValue);
  Serial.println(sensorValue,  DEC);
}
