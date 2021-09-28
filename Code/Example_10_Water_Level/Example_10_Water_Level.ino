int adc_id = 0;        // вход A0
int HistoryValue = 0;  // предыдущее значение АЦП
char printBuffer[128]; // буфер вывода
void setup() {
  Serial.begin(9600);
}
void loop() {
    int value = analogRead(adc_id); // читаем АЦП
    if(((HistoryValue>=value) && ((HistoryValue - value) > 10)) || 
       ((HistoryValue<value) && ((value - HistoryValue) > 10))) {
      sprintf(printBuffer,"ADC%d level is %d\n",adc_id, value);
      Serial.print(printBuffer);
      HistoryValue = value;
    }
}
