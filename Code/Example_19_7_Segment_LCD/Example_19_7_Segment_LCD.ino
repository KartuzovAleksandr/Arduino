// шаблоны для цифр от 0 до 9
// 1 = LED on, 0 = LED off, in this order:
// 74HC595 pin     Q0,Q1,Q2,Q3,Q4,Q5,Q6,Q7 
// Mapping to      a,b,c,d,e,f,g of Seven-Segment LED
byte seven_seg_digits[10] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11100110   // = 9
                             };
int latchPin = 3; // ST_CP of 74HC595
int clockPin = 4; // SH_CP of 74HC595
int dataPin = 2;  // DS of 74HC595
void setup() {
    // установка пинов на выход
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
  // отображение цифры на 7-segment display
void sevenSegWrite(byte digit) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
  // the original data (bit pattern)
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]);  
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
}
void loop() {       
  // цикл от 9 до 0
  for (byte digit = 10; digit > 0; --digit) {
    delay(1000);
    sevenSegWrite(digit - 1); 
  }
  delay(3000);
}
