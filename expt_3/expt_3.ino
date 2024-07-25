#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define SCREEN_WIDTH 128

#define SCREEN_HEIGHT 64

#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SCREEN_ADDRESS 0x3C

void setup() {
Serial.begin(9600);
Serial.println(F("DHT test!"));
dht.begin();

if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { 
 Serial.println(F("SSD1386 allocation failed")); 
 for (;;); // infinite Loop to stop execution
}

display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
}
void loop() 
{
  delay(2000);

float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);

if (isnan(h) || isnan(t) || isnan(f)) {
  Serial.println(F("Failed to read from DHT Sensor!")); 
  return;
}

display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);

display.print(F("Temp: "));
display.print(t);
display.print(F("C"));
display.setCursor(0, 20);

display.print(F("Temp: "));
display.print(f);
display.print(F(" F"));

display.display();
Serial.print(F("Temp: "));
Serial.print(t);
Serial.print(F(" C , "));

Serial.print(F("Temp: "));
Serial.println(f);

display.print(F("Humidity: "));
display.print(h);
display.print(F("%"));
display.setCursor(0, 10);
}
