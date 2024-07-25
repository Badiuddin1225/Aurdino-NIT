#include "DHT.h"
#define DHTPIN 27
#define DHTTYPE 11
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
dht.begin();
}
void loop()
{
  delay(2000);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)){
    Serial.println("failed to read from DHT sensor!");
    return;
   }
Serial.print("humidity: ");
Serial.print(humidity);
Serial.print(" %\t");
Serial.print("temperature: ");
Serial.print(temperature);
Serial.println(" *c");
}
