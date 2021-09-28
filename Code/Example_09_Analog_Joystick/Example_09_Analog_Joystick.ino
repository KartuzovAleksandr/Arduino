const int SW_pin = 2; // цифровой контакт для чтения нажатия
const int X_pin = 0;  // аналоговый вход координаты Х
const int Y_pin = 1;  // аналоговый вход координаты Y
void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}
void loop() {
  Serial.print("Switch: "); // положение кнопки
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n"); // перевод строки
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin)); // X
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin)); // Y
  Serial.print("\n\n"); // 2 пустых строки
  delay(500);
}
