#include <Servo.h>
Servo myservo; // создаем объект Servo (до 12)
int pos = 0;   // начальная позиция сервопривода
void setup() {
  myservo.attach(9); // присоединяем сервопривод к пину D9
}
void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // цикл от 0 до 180 градусов
    myservo.write(pos);                 // поворот на 1 градус
    delay(15);                          // пауза 15 мс
  }
  for (pos = 180; pos >= 0; pos -= 1) { // от 180 до 0 градусов
    myservo.write(pos);              
    delay(15);                       
  }
}
