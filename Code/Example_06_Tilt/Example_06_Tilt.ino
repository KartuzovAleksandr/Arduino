int led=13;      // пин для LED
int buttonpin=2; // пин для чтения индикатора
void  setup() {
  pinMode(led, OUTPUT);      // выходной порт для LED
  pinMode(buttonpin, INPUT); // входной порт для Tilt_Ball_Switch
}
void  loop() { 
  int val=digitalRead(buttonpin);
  if(val==HIGH) {
    digitalWrite(led, HIGH); // зажигаем LED в случае наклона индикатора
  }
  else {
    digitalWrite(led, LOW); // гасим LED 
  }
}
