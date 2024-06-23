#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

// WiFi and WebSocket configurations
const char *ssid = "gui";
const char *password = "abcd5678";
const char *host = "192.168.80.64";
const uint16_t port = 3000;

WebSocketsClient webSocket;

// Sensor and LED configurations
const int redPin = D12;
const int greenPin = D13;
const int glpPin = D3;

int dt = 100;

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_DISCONNECTED:
    Serial.println("Disconnected!");
    break;
  case WStype_CONNECTED:
    Serial.println("Connected to server");
    break;
  case WStype_TEXT:
    Serial.printf("Received: %s\n", payload);
    break;
  }
}

void setup()
{
  Serial.begin(115200);

  // Initialize WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize WebSocket
  webSocket.begin(host, port, "/ws");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);

  // Initialize sensor and LEDs
  pinMode(glpPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
}

void loop()
{
  webSocket.loop();
  int sensorValue = digitalRead(glpPin);
  Serial.println(sensorValue);

  if (sensorValue == LOW)
  {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
  else
  {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }

  webSocket.sendTXT(String(sensorValue));
  delay(dt);
}
