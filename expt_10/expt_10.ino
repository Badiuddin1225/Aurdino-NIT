#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>

const int csPin = 5;
const int resetPin = 14;
const int irqPin = 2;

#define DHTPIN 27
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define SCREEN_ADDRESS 0x3C

void setup() 
{ 
Serial.begin(9600);

while (!Serial); 
dht.begin();

if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
  Serial.println(F("SSD1306 allocation failed"));
  for (;;);
}

 display.display();
 delay(2000);
 display.clearDisplay();
 Wire.begin();

Serial.println("LoRa Transmitter");
LoRa.setPins (csPin, resetPin, irqPin);
if (!LoRa.begin(866E6)) {
Serial.println("Starting LoRa failed!");
while (1);
}
}


void loop() {
float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);

if (isnan(h) || isnan(t) || isnan(f)) {
Serial.println(F("Failed to read from DHT sensor!"));
return;
}

display.clearDisplay();
display.setTextSize(1);
display.setTextColor (SSD1306_WHITE);
display.setCursor(0, 0);

display.print(F("Temp: "));
display.print(t);
display.print(F("C"));
display.setCursor(0, 20);

display.print(F("Temp: "));
display.print(f);
display.print(F(" F"));
display.setCursor(0, 40);

display.print(F("Hum: "));
display.print(h);

display.print(F("%"));

display.display();
Serial.print (F("Hum: "));
Serial.print(h);
Serial.print(F("%, "));

Serial.print(F("Temp: "));
Serial.println(f);

String packet = "Humidity: " + String(h) + "% || " + "Temperature: "+
String() + "C | "+ String(f)+ "F";
LoRa.beginPacket();
LoRa.print(packet);
LoRa.endPacket();

Serial.print("Sent packet: ");
Serial.println(packet);
delay(2000);
}

