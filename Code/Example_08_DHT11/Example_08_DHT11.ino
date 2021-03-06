#include <SimpleDHT.h>
int pinDHT11 = 2;
SimpleDHT11 dht11;
void setup() {
  Serial.begin(9600);
}
void loop() {
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  delay(1000);
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    Serial.println("Read DHT11 failed");
    return;
  }
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" %");
  delay(1000);
}
