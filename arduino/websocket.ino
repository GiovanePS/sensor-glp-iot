#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

const char *ssid = "gui";
const char *password = "abcd5678";
const char *host = "192.168.219.64"; // IP address or domain name
const uint16_t port = 3000;

WebSocketsClient webSocket;

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
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  webSocket.begin(host, port, "/");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000); // Reconnect every 5s if connection is lost
}

void loop()
{
  webSocket.loop();
}
