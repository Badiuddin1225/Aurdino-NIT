#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_SSD1306.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SCREEN_ADDRESS 0x3C

void setup() {
Serial.begin(115200);
while (!Serial);

if (!bmp.begin()) {
Serial.println("Could not find a valid BMP180 sensor, check wiring!"); 
while (1);
}

if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
Serial.println(F("SSD1306 allocation failed"));
for (;;);
}

display.display();
delay(2000);
display.clearDisplay();
}

void loop() {
sensors_event_t event;
bmp.getEvent(&event);

display.clearDisplay();

if (event.pressure) {
float pressure = event.pressure;
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0); 
display.print("Pressure: ");
display.print(pressure);
display.println(" hPa");

float sealevelPressure = 1013.25;
float altitude = bmp.pressureToAltitude (sealevelPressure, event.pressure);
display.print("Altitude: ");
display.print(altitude);
display.println("m");

display.display(); // Show the display buffer on the screen

Serial.print("Pressure: ");
Serial.print(pressure);
Serial.println(" hPa");
Serial.print("Altitude: ");
Serial.print(altitude);
Serial.println(" m");
}
 else {

display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
display.setCursor(0, 0);
display.println("Sensor error");
display.display();
}
delay(2000);
}