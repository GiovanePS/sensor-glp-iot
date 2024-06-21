#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

// WiFi and WebSocket configurations
const char *ssid = "gui";
const char *password = "abcd5678";

const char *host = "192.168.219.64"; // IP address or domain name
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
  webSocket.begin(host, port, "/");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000); // Reconnect every 5s if connection is lost

  // Initialize sensor and LEDs
  pinMode(glpPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  // Turn off the red LED and on the green LED
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
}

void loop()
{
  // WebSocket client loop
  webSocket.loop();

  // Read sensor value
  int sensorValue = digitalRead(glpPin);
  Serial.println(sensorValue);

  // Control LEDs based on sensor value
  if (sensorValue == LOW)
  { // If sensor reads LOW, turn on the red LED and off the green LED
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }
  else
  { // Otherwise, turn off the red LED and on the green LED
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }

  // Send sensor value over WebSocket
  String message = String(sensorValue);
  webSocket.sendTXT(message);

  // Delay for a short period
  delay(dt);
}
