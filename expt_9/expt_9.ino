#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3EDh_OwYO"
#define BLYNK_TEMPLATE_NAME "led"
#define BLYNK_AUTH_TOKEN "7_ND-FK4zcLo7sX9LzcdcKsAk2gdOVlp"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[]= "1234";
char pass[] = "12345678900";
char auth[] = "7_ND-FK4zcLo7sX9LzcdcKsAk2gdOVlp";
#define RELAY_PIN 13

void setup() 
{
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, pass);
  Serial.print(".");
  while (WiFi.status() != WL_CONNECTED) { 
  delay(500);
  Serial.println(".");
}

Serial.println(); 
Serial.println("Connected to WiFi");
Serial.println(WiFi.localIP());
Blynk.config(auth);
if (Blynk.connect()) {
  Serial.println("Connected to Blynk server");
} else {

Serial.println("Failed to connect to Blynk server");
}
}
BLYNK_WRITE(VO) {

int pinValue = param.asInt(); 
if(pinValue == 0) {
Serial.println("LED is OFF");

} else { 

Serial.println("LED is ON");
}
}
void loop() {
Blynk.run();
}