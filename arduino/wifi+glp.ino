#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

// WiFi and WebSocket configurations
const char *ssid = "gui";
const char *password = "abcd5678";
const char *host = "192.168.219.64"; // IP address or domain name
const uint16_t port = 3000;

WebSocketsClient webSocket;

// Sensor and LED configurations
const int pinoLedVermelho = D12; // Digital pin used by the red LED
const int pinoLedVerde = D13;    // Digital pin used by the green LED
const int pinoSensor = D3;       // Digital pin used by the sensor
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
    webSocket.sendTXT("hello from ESP8266");
    break;
  case WStype_TEXT:
    Serial.printf("Received: %s\n", payload);
    break;
  }
}

void setup()
{
  // Initialize serial communication
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
  pinMode(pinoSensor, INPUT);         // Set pin as input
  pinMode(pinoLedVermelho, OUTPUT);   // Set pin as output for red LED
  pinMode(pinoLedVerde, OUTPUT);      // Set pin as output for green LED
  digitalWrite(pinoLedVermelho, LOW); // Red LED initially off
  digitalWrite(pinoLedVerde, HIGH);   // Green LED initially on (complement of red LED)
}

void loop()
{
  // WebSocket client loop
  webSocket.loop();

  // Read sensor value
  int sensorValue = digitalRead(pinoSensor);
  Serial.println(sensorValue);

  // Control LEDs based on sensor value
  if (sensorValue == LOW)
  { // If sensor reads LOW, turn on the red LED and off the green LED
    digitalWrite(pinoLedVermelho, HIGH);
    digitalWrite(pinoLedVerde, LOW);
  }
  else
  { // Otherwise, turn off the red LED and on the green LED
    digitalWrite(pinoLedVermelho, LOW);
    digitalWrite(pinoLedVerde, HIGH);
  }

  // Send sensor value over WebSocket
  String message = "Sensor value: " + String(sensorValue);
  webSocket.sendTXT(message);

  // Delay for a short period
  delay(dt);
}
