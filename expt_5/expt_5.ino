#include<WiFi.h>
#include<DHT.h>

const char *ssid = "0900";
const char *password = "123456789";

WiFiServer server(80);

#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN , DHTTYPE);

float temperature = 0.0;
float humidity = 0.0;
unsigned long previousMillis = 0;   

const long interval = 5000;

void setup()

{
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while( WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");        
  }
  Serial.println();
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server,started");
  Serial.print("IP Address");
  Serial.println(WiFi.localIP());

  dht.begin();
}
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT Sensor!");
      return;
    }
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    while (!client.available()) {
      delay(1);
    }
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();

    String response ="HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/html\r\n";
    response += "\r\n";
    response += "<!DOCTYPE HTML>\r\n";
    response += "<html>\r\n";
    response += "<head><title>ESP32 web Server</title></head>\r\n";
    response += "<body><h1>Hello from ESP32!<h1>\r\n";
    response += "<p>Temperature: " + String(temperature) + "&#8451;</P>\r\n";
    response += "<p>Humidity: " + String(humidity) + " %</p>\r\n";
    response += "</body></html>\r\n";
    client.print(response);
    delay(1);
    client.stop();
    Serial.println("client disconnected.");
  }
}