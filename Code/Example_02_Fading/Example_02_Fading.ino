const int LED=9;
void setup() {
  pinMode(LED, OUTPUT);
}
void loop() {
      // зажигаем светодиод
  for (int i=0; i < 255; i++) {
       analogWrite(LED, i);
       delay(20);         // пауза 20 мсек
  }
      // гасим светодиод
  for (int i=255; i > 0; i--) {
       analogWrite(LED, i);
       delay(20);         // пауза 20 мсек
  }
  delay(500);
}
