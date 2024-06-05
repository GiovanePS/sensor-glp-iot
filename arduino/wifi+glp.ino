/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#ifndef STASSID
#define STASSID "gui"
#define STAPSK "abcd5678"
#endif

// Wifi
const char *ssid = STASSID;
const char *password = STAPSK;

const char *host = " 192.168.219.64";
const uint16_t port = 3000;

// GLP
const int pinoLed = D12;   // PINO DIGITAL UTILIZADO PELO LED
const int pinoSensor = D3; // PINO DIGITAL UTILIZADO PELO SENSOR
int dt = 1000;

void setup()
{
  // Wifi
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // GLP
  pinMode(pinoSensor, INPUT); // DEFINE O PINO COMO ENTRADA
  pinMode(pinoLed, OUTPUT);   // DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoLed, LOW); // LED INICIA DESLIGADO
}

void loop()
{
  // Server Connection
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  if (!client.connect(host, port))
  {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }

  // This will send the request to the server
  client.println("hello from ESP8266");

  // read back one line from server
  Serial.println("receiving from remote server");
  String line = client.readStringUntil('\r');
  Serial.println(line);

  Serial.println("closing connection");
  client.stop();

  Serial.print("Sensor State:");
  Serial.println(digitalRead(pinoSensor));

  if (digitalRead(pinoSensor) == LOW) // SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
  {
    digitalWrite(pinoLed, HIGH); // ACENDE O LED
  }
  else // SENÃO, FAZ
  {
    digitalWrite(pinoLed, LOW); // APAGA O LED
  }
  delay(dt);
}
