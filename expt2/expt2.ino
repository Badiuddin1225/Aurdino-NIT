#include<Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085); // Corrected initialization syntax

void setup() {
  Serial.begin(115200);
  Serial.println("BMP180 Sensor Test");
  
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1); // Infinite loop to halt execution if sensor not found
  }
}

void loop() {
  sensors_event_t event;
  bmp.getEvent(&event);

  if (event.pressure) {
    Serial.print("Pressure: ");
    Serial.print(event.pressure);
    Serial.println(" hPa");

    // Calculate altitude based on sea level pressure (adjust this value according to your location)
    float seaLevelPressure = 1013.25; // Adjust according to your local sea level pressure
    Serial.print("Altitude: ");
    Serial.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure));
    Serial.println(" meters");

    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  } else {
    Serial.println("Sensor error");
  }

  delay(2000); // Delay in milliseconds (lowercase 'delay' function)
}

