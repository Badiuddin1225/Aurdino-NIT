#define BLYNK_TEMPLATE_ID "TMPL3jN1q9uno"
#define BLYNK_TEMPLATE_NAME "Sahil"
#define BLYNK_AUTH_TOKEN "UWlN3UflLxrvXHzgVDRuGBi23jE5CJHo"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = "UWlN3UflLxrvXHzgVDRuGBi23jE5CJHo";

char ssid[] = "1234"; 
char pass[] = "12345678900";

#define DHTPIN 27 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
void sendSensorData()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

if (isnan(h) || isnan(t)) { 
  Serial.println("Failed to read from DHT sensor!");
  return;
}

Serial.print("Temperature: ");
Serial.print(t);
Serial.print("°C, Humidity: ");
Serial.print(h);
Serial.println("%");

Blynk.virtualWrite(V1, t); // V1 for temperature
Blynk.virtualWrite(V2, h); // V2 for humidity
Serial.println("Displayed data in Blynk app.");

}
void setup(){
  Serial.begin(115200);
  Serial.println("Connecting to WiFi...");
  Blynk.begin(auth, ssid, pass);

  while (WiFi.status() != WL_CONNECTED) { 
  delay(1000);
  Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  dht.begin();
  timer.setInterval(5000L, sendSensorData);
}
void loop()

{
Blynk.run();
timer.run();
}