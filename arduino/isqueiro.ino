const int pinoLedVermelho = D12; // pino do LED vermelho
const int pinoLedVerde = D13;    // pino do LED verde
const int pinoSensor = D3;       // pino do sensor
int dt = 100;

void setup()
{
  pinMode(pinoSensor, INPUT);
  pinMode(pinoLedVermelho, OUTPUT);
  pinMode(pinoLedVerde, OUTPUT);
  digitalWrite(pinoLedVermelho, LOW);
  digitalWrite(pinoLedVerde, HIGH);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(digitalRead(pinoSensor)); 
  if (digitalRead(pinoSensor) == LOW)
  {                                      // verifica se a leitura do pino do sensor é LOW
    digitalWrite(pinoLedVermelho, HIGH); // acende o LED vermelho
    digitalWrite(pinoLedVerde, LOW);     // apaga o LED verde
  }
  else
  {                                     // se a leitura do pino do sensor não for LOW
    digitalWrite(pinoLedVermelho, LOW); // apaga o LED vermelho
    digitalWrite(pinoLedVerde, HIGH);   // acende o LED verde
  }
  delay(dt); // espera por 'dt' milissegundos
}
