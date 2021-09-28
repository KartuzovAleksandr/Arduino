//----ОБЬЯВЛЕНИЕ ПОРТОВ ЧАСОВ РЕАЛЬНОГО ВРЕМЕНИ-----------------------------------------
#define RST 4
#define DAT 5
#define CLK 6
//----ОБЬЯВЛЕНИЕ ПЕРЕМЕННЫХ ДЛЯ ПРЕДНАСТРОЙКИ-----------------------------------------
#define DHT11PIN   12    // Датчик влачности и температуры воздуха 
#define Miganie 100 // Скорость мигания на LCD экране

//----ОБЬЯВЛЕНИЕ БИБЛИОТЕК И СОПУТСТВУЮЩИХ НАСТРОЕК-----------------------------------------
#include <dht11.h>  // Подключение библиотеки для датчика ВЛАЖНОСТИ И ТЕМПЕРАТУРЫ 
dht11 DHT11;    // Указываем конкретный датчик для библиотеки
#include <iarduino_RTC.h> // подключение библиотеки ЧСЫ РЕАЛЬНОГО ВРЕМЕНИ 
iarduino_RTC time(RTC_DS1302,RST,CLK,DAT); // Задаем правильно название нашего модуля, а также указываем к каким цифровым пинам его подключаем(в нашем случае – 8,6,7)
#include <button_coin.h>    // Подключаем библиотеку для работы с кнопками 
#include <Wire.h>  // Подключаем библиотеку для работы с шиной I2C
#include <EEPROM.h> // подключаем библиотеку для записи данных в энергонезависимую память I2C
#include <LiquidCrystal_I2C.h>  // Подключаем библиотеку для работы с LCD дисплеем по шине 
LiquidCrystal_I2C lcd(0x27,16,2);    // Объявляем объект библиотеки, указывая параметры дисплея (адрес I2C = 0x27, количество столбцов = 16, количество строк = 2)

//----ОБЬЯВЛЕНИЕ КНОПОК ДЛЯ БУДИЛЬНИКА ПОЛИВА-----------------------------------------
//кнопки
#define KNA A2 // Кнопка A 
#define KNB A0 // Кнопка B 
#define KND A1  // Кнопка C
//#define KND 9   // Кнопка D

//----ОБЬЯВЛЕНИЕ ПОРТОВ ДЛЯ ПОДКЛЮЧАЕМЫХ КОМПОНЕНТОВ-----------------------------------------
#define POLIV   11    // Включение реле для полива 
#define PIN  10  // Включение реле Светового дня
#define VENVVER 9 // Включение реле Вентелятора Верх 
#define VENCEN 8 // Включение реле Вентелятора Центр 
#define VENBOTT 7 // Включение реле Вентелятора Низ
//#define PIN A3  // Включение реле

//  ОБЬЯВЛЕНИЕ НАСТРОЕК БИБЛИОТЕКИ РАБОТЫ С КНОПКАМИ ДЛЯ УБИРАНИЯ ДРЕБЕЗГА
#define bouns 5 //Убирание дребезга 
button_coin buttonA(KNA, 0, bouns); // параметры:
button_coin buttonB(KNB, 0, bouns); // параметры:
button_coin buttonC(KND, 0, bouns); // параметры:
//  button_coin buttonD(KND, 0, bouns); // параметры:
//  1-й параметр - номер пина к которому подключена кнопка (0-13)
//  2-й параметр - режим работы кнопки (0-нормально замкнутая на землю; 1-нормальна замкнутая на +5В через сопротивление 1КОм, сопротивление можно не подключать)
//  3-й параметр - время задержки дребезга в миллисекундах

//----ОБЬЯВЛЕНИЕ СИМВОЛОВ ДЛЯ ДИСПЛЕЯ-----------------------------------------
uint8_t OsnovEkran[8][8] = {
{ 0,14,21,23,17,14,0},  //Время
{ 4,4,14,31,0,10,0,21}, //Полив
{4,4,14,14,31,25,25,14},  //Влажность
{0,21,14,31,14,21,0,0}, //Световой день Утро
{31,0,19,20,14,5,25,0}, //Вентелятор верх
{0,0,19,20,14,5,25,0},  //Вентелятор Центр
{0,19,20,14,5,25,0,31}, //Вентелятор низ
{0,14,25,16,25,14,0,0}  //Световой день Ночь
};

uint8_t GlavnoeMenu[8][8] = {
{0,0,17,17,31,17,17,0}, //н
{0,0,18,21,29,21,18,0}, //ю
{31,17,17,17,17,17,17,0}, //П
{0,0,15,9,9,9,17,0},  //л
{0,0,17,19,21,25,17,0}, //и
{0,0,24,20,28,18,28,0}, //в
{0,0,17,17,25,21,25,0}, //ы
{0,0,31,4,4,4,4,0}  //т
};

uint8_t MenuPoliv[8][8] = {
{0,0,17,17,15,1,1,0}, //ч
{0,0,31,4,4,4,4,0}, //т
{0,0,16,16,28,18,28,0}, //ь
{0,0,31,17,17,17,17,0}, //п
{0,0,15,9,9,9,17,0},  //л
{0,0,17,19,21,25,17,0}, //и
{0,0,24,20,28,18,28,0}, //в
{0,0,18,20,24,20,18,0}  //к
};

uint8_t MenuSvet[6][8] = {
{0,0,24,20,28,18,28,0}, //в
{0,0,31,4,4,4,4,0}, //т
{0,0,18,20,24,20,18,0}, //к
{0,0,15,9,9,9,17,0},  //л
{0,0,17,17,25,21,25,0}, //ы
{17,17,17,15,1,1,1,0} //Ч
};

uint8_t EkranPoliv[5][8] = {
{31,17,17,17,17,17,17,0}, //П
{0,0,15,9,9,9,17,0},  //л
{0,0,17,19,21,25,17,0}, //и
{0,0,24,20,28,18,28,0}, //в
{0,0,18,20,24,20,18,0}  //к
};

void setup() {
//delay(50);
lcd.init(); // Инициализация дисплея 
lcd.backlight(); // Подключение подсветки
time.begin(); //подключение часов
pinMode(POLIV, OUTPUT); //Настройка порта реле для полива 
digitalWrite(POLIV, HIGH);
//digitalWrite(POLIV, LOW);
pinMode(PIN, OUTPUT); //Настройка порта реле для Светового дня (лампа) 
digitalWrite(PIN, HIGH);
pinMode(VENVVER, OUTPUT); //Настройка порта реле для Светового дня (лампа) 
digitalWrite(VENVVER, HIGH);
pinMode(VENCEN, OUTPUT);  //Настройка порта реле для Светового дня (лампа) 
digitalWrite(VENCEN, HIGH);
pinMode(VENBOTT, OUTPUT); //Настройка порта реле для Светового дня (лампа) 
digitalWrite(VENBOTT, HIGH);
/* //Настройка портов кнопок pinMode(KNA, INPUT); pinMode(KNB, INPUT); pinMode(KNC, INPUT); pinMode(KND, INPUT);*/
}

void loop() { 
  digitalWrite(POLIV, HIGH); 
  FunVistavVremen(); 
  FunGlavEkran(); 
  FunRegulVentiliator(); 
  FunPoliv();
  FunSvet(); 
  digitalWrite(POLIV, HIGH);
}

//  ФУНКЦИЯ СВЕТОВОГО ДНЯ   
void FunSvet() {
if (time.Hours >= EEPROM.read(4) && time.Hours < EEPROM.read(5)) digitalWrite(PIN, LOW);
  else
    digitalWrite(PIN, HIGH);
}

//  ФУНКЦИЯ ПОЛИВА  
void FunPoliv() {
if (time.Hours==EEPROM.read(1) && time.minutes==EEPROM.read(2) && time.seconds==00) /*&& time.weekday!=0 && time.weekday!=6*/
{
  lcd.clear();
  lcd.createChar(1, EkranPoliv[0]);
  lcd.createChar(2, EkranPoliv[1]); 
  lcd.createChar(3, EkranPoliv[2]); 
  lcd.createChar(4, EkranPoliv[3]); 
  lcd.createChar(5, EkranPoliv[4]);
  lcd.setCursor(0, 0);  // Устанавливаем курсор в позицию (0 столбец, 0 строка) lcd.print("\1o\2\3\4 ce\5");
  for (byte i=0; i<(EEPROM.read(3));i++) {
    lcd.setCursor(6, 0); lcd.print(" "); digitalWrite(POLIV, LOW); lcd.setCursor(6, 0);
    lcd.print(EEPROM.read(3)-i); delay (1000);
  }
  digitalWrite(POLIV, HIGH);
}
}

//---------------------ФУНКЦИЯ РЕГУЛИРОВКИ ТЕМПЕРАТУРЫ----------------------------------
void FunRegulVentiliator() {
//  > считывается данные датчика
  int chk = DHT11.read(DHT11PIN);
  unsigned int temperat =(float)DHT11.temperature; 
  if (temperat < 18) {
    lcd.setCursor(13, 0); // Устанавливаем курсор в позицию (0 столбец, 0 строка) 
    lcd.print(" ");
    digitalWrite(VENVVER, HIGH);
  }
  else {
    lcd.setCursor(13, 0); // Устанавливаем курсор в позицию (0 столбец, 0 строка) lcd.print("\5");
    digitalWrite(VENVVER, LOW);
  }
  if (temperat > 30) {
    lcd.setCursor(15, 0); // Устанавливаем курсор в позицию (0 столбец, 0 строка) lcd.print("\7");
    digitalWrite(VENBOTT, LOW);
  }
  else {
    lcd.setCursor(15, 0); // Устанавливаем курсор в позицию (0 столбец, 0 строка) lcd.print(" ");
    digitalWrite(VENBOTT, HIGH);
  }
  buttonC.but();
  bool cenVen = buttonC.trigger_let; 
  if (cenVen == 0) {
    lcd.setCursor(14, 0); // Устанавливаем курсор в позицию (0 столбец, 0 строка) lcd.print("\6");
    digitalWrite(VENCEN, LOW);
  }
  else {
    lcd.setCursor(14, 0); // Устанавливаем курсор в позицию (0 столбец, 0 строка) lcd.print(" ");
    digitalWrite(VENCEN, HIGH);
  }
}

//---------------------ФУНКЦИЯ Отображение информации ГЛАВНОГО ЭКРАНА----------------------------------
void FunGlavEkran() {
  //  > считывается данные датчика
  int chk = DHT11.read(DHT11PIN);
  lcd.createChar(1, OsnovEkran[0]); 
  lcd.createChar(2, OsnovEkran[1]); 
  lcd.createChar(3, OsnovEkran[2]); 
  lcd.createChar(4, OsnovEkran[3]); 
  lcd.createChar(5, OsnovEkran[4]); 
  lcd.createChar(6, OsnovEkran[5]); 
  lcd.createChar(7, OsnovEkran[6]); 
  lcd.createChar(8, OsnovEkran[7]);
  lcd.setCursor(0, 0);  // Устанавливаем курсор в позицию (0 столбец, 0 строка) 
  lcd.print(time.gettime("H:i"));
  lcd.print(" \2"); 
  lcd.print(EEPROM.read(1)); 
  lcd.print(":");  // Набор текста
  lcd.print(EEPROM.read(2)); 
  lcd.print(" ");
  lcd.setCursor(0, 1);  // Устанавливаем курсор в позицию (0 столбец, 0 строка) 
  lcd.print("t");
  unsigned int temperat =(float)DHT11.temperature; 
  lcd.print(temperat);
  lcd.print(" \3");
  unsigned int vlOkr =(float)DHT11.humidity; 
  lcd.print(vlOkr);
  lcd.print(" \4"); 
  lcd.print(EEPROM.read(4)); 
  lcd.print(" \10"); 
  lcd.print(EEPROM.read(5)); 
  lcd.print(" ");
}

//---------------------ФУНКЦИЯ ВЫСТАВЛЕНИЕ ВРЕМЕНИ----------------------------------
void FunVistavVremen() {
  buttonA.but();
  if (buttonA.discon == HIGH) {
    //if (digitalRead(KNA) == HIGH) { lcd.clear();
    lcd.createChar(1, GlavnoeMenu[0]); 
    lcd.createChar(2, GlavnoeMenu[1]); 
    lcd.createChar(3, GlavnoeMenu[2]); 
    lcd.createChar(4, GlavnoeMenu[3]); 
    lcd.createChar(5, GlavnoeMenu[4]); 
    lcd.createChar(6, GlavnoeMenu[5]); 
    lcd.createChar(7, GlavnoeMenu[6]); 
    lcd.createChar(8, GlavnoeMenu[7]);
    lcd.setCursor(0, 0); lcd.print("Me\1\2: B-\3o\4\5\6"); lcd.setCursor(0, 1);
    lcd.print("A-B\7x D-C\6e\10"); int ex=0;
    //delay(2000);
    while (true) { 
      buttonB.but();
      buttonC.but(); 
      buttonA.but();
      //выход при нажатии на кнопку D 
      if (buttonB.discon) {
        lcd.clear();
        lcd.createChar(1, MenuPoliv[0]); 
        lcd.createChar(2, MenuPoliv[1]); 
        lcd.createChar(3, MenuPoliv[2]); 
        lcd.createChar(4, MenuPoliv[3]); 
        lcd.createChar(5, MenuPoliv[4]); 
        lcd.createChar(6, MenuPoliv[5]); 
        lcd.createChar(7, MenuPoliv[6]); 
        lcd.createChar(8, MenuPoliv[7]);
        lcd.setCursor(0, 0); 
        lcd.print("Ha\1a\2\3 \4o\5\6\7 \7"); 
        lcd.setCursor(0, 1);
        lcd.print(" \1 m Ha ce\10D");
        FunVspomVistavVremen(24, 1, 0, 1);
        FunVspomVistavVremen(60, 2, 4, 1);
        FunVspomVistavVremen(100, 3, 10, 1);
    }
    //выход при нажатии на кнопку D 
    if (buttonC.discon) {
      lcd.clear();
      lcd.createChar(1, MenuSvet[0]); 
      lcd.createChar(2, MenuSvet[1]); 
      lcd.createChar(3, MenuSvet[2]); 
      lcd.createChar(4, MenuSvet[3]); 
      lcd.createChar(5, MenuSvet[4]); 
      lcd.createChar(6, MenuSvet[5]);
      lcd.setCursor(0, 0); 
      lcd.print("C\1e\2 B\3\4 \6ac"); 
      lcd.setCursor(0, 1);
      lcd.print(" B\5\3\4 \6ac D");
      FunVspomVistavVremen(24, 4, 9, 0);
      FunVspomVistavVremen(24, 5, 9, 1);
    }
    //выход при нажатии на кнопку D 
    if (buttonA.discon) {
      break;
    }
    //таймер для выхода если ничего не происходит 
    ex++;
    if (ex>35000) {
      break;
    }
  }
}
}

//---Вспомогательная функция для ФУНКЦИЯ ВЫСТАВЛЕНИЕ ВРЕМЕНИ----------------------------------
void FunVspomVistavVremen(byte _time, byte _ROM, byte _strok, byte _stol) // XXX Макс количество ед. Времени || Ячейка ПЗУ || Строка || Столбец|| Текст после числа
{
  unsigned int s = 0;
  byte prVrem = EEPROM.read(_ROM); 
  lcd.setCursor(_strok, _stol);  // Установка курсора 
  lcd.print(EEPROM.read(_ROM));  // Набор текста
  while (true) {
    buttonB.but(); 
    buttonC.but(); 
    buttonA.but();
    byte i = prVrem; //необхадимо для ограничния записи времени если для часов то 24, если для минут то 60
    s++;
    if (buttonB.discon) {
      prVrem++;
    }
    if (buttonC.discon) {
      prVrem--;
    }
    if (prVrem == _time) //ограничния записи времени если для часов то 24, если для минут то 60 
      prVrem=0;
      else
      if (prVrem == 255) 
        prVrem=_time-1;
    if ((s/Miganie)%2 == 0) {  //если были изменения то выводим актуальную информацию на экран lcd.setCursor(_strok,_stol);    // Установка курсора
      lcd.print(prVrem);  // Набор текста
    }
    else
      if ((s/Miganie)%2 == 1) {
        lcd.setCursor(_strok,_stol);  // Установка курсора lcd.print(" ");  // Набор текста
      }
    if (buttonA.discon) {
      EEPROM.write(_ROM, prVrem); // записываем в ячейку 1 старший байт 
      lcd.setCursor(_strok,_stol);  // Установка курсора
      lcd.print(prVrem);  // Набор текста break;
    }
  }
}
