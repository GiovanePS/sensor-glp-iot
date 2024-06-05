/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "gui"
#define STAPSK "abcd5678"
#endif

// Wifi
const char *ssid = STASSID;
const char *password = STAPSK;

const char *host = "djxmmx.net";
const uint16_t port = 80;

// GLP
const int pinoLed = D12;   // PINO DIGITAL UTILIZADO PELO LED
const int pinoSensor = D3; // PINO DIGITAL UTILIZADO PELO SENSOR
int dt = 100;

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

    Serial.print("Sensor State:");
    Serial.println(digitalRead(pinoSensor));

    if (digitalRead(pinoSensor) == LOW)
    {                                // SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
        digitalWrite(pinoLed, HIGH); // ACENDE O LED
    }
    else
    {                               // SENÃO, FAZ
        digitalWrite(pinoLed, LOW); // APAGA O LED
    }
    // delay(dt);
}
