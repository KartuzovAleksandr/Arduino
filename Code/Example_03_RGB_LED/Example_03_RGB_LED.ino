// Задаем цифровые выводы для цветов
#define BLUE 3
#define GREEN 5
#define RED 6
void setup() {
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
digitalWrite(RED, HIGH);
digitalWrite(GREEN, LOW);
digitalWrite(BLUE, LOW);
}
// переменные для цветовых составляющих
int redValue;
int greenValue;
int blueValue;
void loop() {
#define delayTime 10 // пауза для плавного изменения цвета
redValue = 255; // начальный цвет
greenValue = 0;
blueValue = 0;
// переход от красного к зеленому цвету
for(int i = 0; i < 255; i += 1) {
    redValue -= 1;
    greenValue += 1;
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    delay(delayTime);
}
redValue = 0;
greenValue = 255;
blueValue = 0;
// переход от зеленого к синему цвету
for(int i = 0; i < 255; i += 1) {
    greenValue -= 1;
    blueValue += 1;
    analogWrite(GREEN, greenValue);
    analogWrite(BLUE, blueValue);
    delay(delayTime);
}
redValue = 0;
greenValue = 0;
blueValue = 255;
// переход от синего к красномуцвету
for(int i = 0; i < 255; i += 1) {
    blueValue -= 1;
    redValue += 1;
    analogWrite(BLUE, blueValue);
    analogWrite(RED, redValue);
    delay(delayTime);
}
}
