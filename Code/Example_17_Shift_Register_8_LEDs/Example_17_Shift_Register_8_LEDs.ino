int tDelay = 100;  // задержка
int latchPin = 11; // (11) ST_CP on 74HC595
int clockPin = 9;  // (9) SH_CP on 74HC595
int dataPin = 12;  // (12) DS on 74HC595
byte leds = 0;
 // обновление данных регистра сдвига
void updateShiftRegister() {
   digitalWrite(latchPin, LOW); // выкл защелку
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH); // вкл защелку
}
void setup()  {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}
void loop() {
  leds = 0; // обнуление данных
  updateShiftRegister();
  delay(tDelay);
  for (int i = 0; i < 8; i++) {
    bitSet(leds, i); // установка битов по очереди
    updateShiftRegister(); // запись в регистр сдвига
    delay(tDelay);
  }
}
