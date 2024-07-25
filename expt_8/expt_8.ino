#include <Wire.h>

int relayPin = 13;
bool LED = false;
void setup() {
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);
}

void loop() {

  LED = !LED;
  digitalWrite(relayPin, LED? HIGH: LOW);
  Serial.print("LED Status:");
  Serial.println(LED? "ON": "OFF");
  delay(4000);
}