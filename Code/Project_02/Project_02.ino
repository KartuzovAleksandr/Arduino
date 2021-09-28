#include <Servo.h> // подключаем библиотеку для работы с сервоприводом
#define avoidPin1 A1 // задаем имя для порта с ик датчиком
#define avoidPin0 A0 //
#define avoidPin2 A2 //
#define avoidPin3 A3 //
#define TRIG 4 //Устанавливаем пин для ультразвукового датчика
#define ECHO 2 //
Servo servo;

int avoid0; // Определяем дополнительные переменные для ик
int avoid1; //
int avoid2; //
int avoid3; //

int angle = 90;     // Определяем дополнительные переменные для вращения 
int lookLeft = 0;//   серво
int lookRight = 0;//
int lookAhead = 0;//
int timeEcho;

// motor A // Назначаем пины для мотора A
int enA = 8;
int in1 = 12;
int in2 = 11;
// motor B // Назначаем пины для мотора B
int enB = 7;
int in3 = 10;
int in4 = 9;
int mode = 0;

 int i=0; //Случайная переменная, назначенная циклам
 int j=0; //Случайная переменная, назначенная циклам
 int state; //Переменная сигнала от устройства Bluetooth
const int vSpeed=255; // Стандартная скорость может принимать значение от 0-255
void setup() { // инициализация программы

Serial.begin(9600); // начинаем прослушивание порта
servo.attach(13); // назначаем управляющий пин сервомотору

// Определяем контакты
pinMode(avoidPin0, INPUT); // ИК
pinMode(avoidPin1, INPUT); //
pinMode(avoidPin2, INPUT); //
pinMode(avoidPin3, INPUT); //

pinMode(TRIG, OUTPUT);// Датчик расстояния 
pinMode(ECHO, INPUT); //

pinMode(enA, OUTPUT); // Моторы
pinMode(enB, OUTPUT); //
pinMode(in1, OUTPUT); //
pinMode(in2, OUTPUT); // 
pinMode(in3, OUTPUT); //
pinMode(in4, OUTPUT);} //

void loop() {

avoid0 = digitalRead(avoidPin0); // Присваиваем переменным значение датчиков 
avoid1 = digitalRead(avoidPin1); // ИК
avoid2 = digitalRead(avoidPin2); //
avoid3 = digitalRead(avoidPin3); //

 if (state == 'W') { //Реализация переключение режимов
  mode = 1;
}else if(state == 'w'){
  mode = 0;
}

  if(Serial.available() /*> 0*/){ //Устанавливаем соединение и принимаем команды с удаленного устройства
 state = Serial.read();
 }
 Serial.print("vSpeed");
 Serial.println(vSpeed);
 Serial.print("state");
 Serial.println(state);
 
 //Остановите автомобиль, когда соединение Bluetooth отключено.
//(Удалите "//" подстроки для активации.)
// if(digitalRead(BTState)==LOW) { state='S'; }
 //Сохранить входящие данные в переменную " состояние
 if(mode == 0) //Начало режима 1
 {
  //|| avoid2 == 0 || avoid3 == 0
if(avoid0 == 0 || avoid1 == 0 ) // Остановка робота при движении вперед в 
{                                               // в случае возникновения препятствия
stop();
back();
delay(2000);
stop();
}
 /***************************************************/
 //Если входящие данные "F" автомобиль идет вперед.
 if (state == 'F') {
 start();
 }
 /**********************************************/
 //Автомобиль идет вперед влево (по диагонали), если входящие данные " G.
 else if (state == 'G') {
 leftRotate();
 }
 /**********************************************/
 //Если входящие данные' I ' автомобиль идет вперед вправо (по диагонали).
 else if (state == 'I') {
 rightRotate();
 }
 /***************************************************/
 //Автомобиль возвращается, если входящие данные " B.
 else if (state == 'B') {
 back();
 }
 /*********************************************/
 //Если входящие данные 'L' автомобиль идет влево.
 else if (state == 'L') {
 left();
 }
 /********************************************************/
 //Если входящие данные 'R' автомобиль идет вправо
 else if (state == 'R') {
 right();
 }
 /*****************************************************/
 //Остановить автомобиль, если входящие данные' s.
 else if (state == 'S'){
 stop();
 }
}
if(mode == 1) //Начало режима  2
 {if(Serial.available() == 0){ // В случае возникновения разрыва соединения
  mode=0;                              //останавливаем автомобиль
  state = 'S';}
  distanceAhead(); // Проверяем возможность ехать вперед
  if(lookAhead<30){ // если расстояние спереди меньше 30 см останавливаемся
  stop();
  delay(1000);
  back(); // возвращаемся назад
  delay(1000);
  stop();
  delay(1000);
  for(angle=90;angle>=10;angle--){ // 
  servo.write(angle);
  delay(5);
}
distanceRight();// проверяем дистанцию справа и заносим в переменные
delay(100);
for(angle=10;angle<=170;angle++){
servo.write(angle);
delay(5);
}

distanceLeft(); //проверяем дистанцию слева и заносим в переменные
delay(100);
for(angle=170;angle>=90;angle--){
servo.write(angle); // считываем данные 
delay(5);
}

if(lookLeft < lookRight){ //определяем направление движения

right(); // поворачиваем на права и едем
delay(1000);
stop();
}

else{

left(); // поворачиваем на лево и едем
delay(1000);
stop();
}
}
else{
start(); // Если препятствий нет едем
} 
 }
}
//Реализация основных функций движения:
void start() // Робот едет вперед
{
// motor A
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(enA, vSpeed);
// motor B
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);

analogWrite(enB,vSpeed);
//delay(2000);
}

void stop() // Робот останавливается
{
  Serial.println("Stop");

digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
analogWrite(enA, 0);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
analogWrite(enB,0);
}

void back() // Робот движется назад
{
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
analogWrite(enA, 200);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
analogWrite(enB, 200);
}
void left() // Робот разворачивается против часовой стрелки 
{
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(enA, 200);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
analogWrite(enB, 200);
}
void right() // Робот разворачивается по часовой стрелки
{
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
analogWrite(enA, 200);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
analogWrite(enB, 200);
}

void leftRotate() // Робот едет по диагонали на лево
{
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(enA, 200);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
analogWrite(enB, 200);
}

void rightRotate() // Робот едет по диагонали на право
{
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
analogWrite(enA, 200);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
analogWrite(enB, 200);
}
// Реализация вспомогательных функций:
void distanceLeft(){ // Проверяем дистанцию слева

digitalWrite(TRIG, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG, LOW);
timeEcho = pulseIn(ECHO, HIGH);
lookLeft = timeEcho/58;
}
void distanceAhead(){ // Проверяем дистанцию спереди

digitalWrite(TRIG, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG, LOW);
timeEcho = pulseIn(ECHO, HIGH);
lookAhead = timeEcho/58;

}

void distanceRight(){ // Проверяем дистанцию справа

digitalWrite(TRIG, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG, LOW);
timeEcho = pulseIn(ECHO, HIGH);
lookRight = timeEcho/58;
}
