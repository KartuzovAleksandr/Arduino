/* The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */
#include <LiquidCrystal.h>
  // инициализация библиотеки 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup() {
  lcd.begin(16, 2); // установка колонок и строк LCD
  lcd.print("Hello, World!"); // вывод сообщения
}
void loop() {
    // установить курсов в колонку 0, строку 1
  lcd.setCursor(0, 1);
    // выводим кол-во секунд со старта Arduino
  lcd.print(millis() / 1000);
}
