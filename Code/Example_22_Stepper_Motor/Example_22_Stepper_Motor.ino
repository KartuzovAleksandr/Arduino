#include <Stepper.h>
  // кол-во шагов в обороте (максимум 4096)
const int stepsPerRevolution = 1500; 
  // инициализация объекта шагового двигателя
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
void setup() {
    // задание скорости вращения 20 rpm:
  myStepper.setSpeed(20); 
  Serial.begin(9600);
}
void loop() {
     // один оборот по часовой стрелке
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);
    // один оборот против часовой стрелки
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
}
