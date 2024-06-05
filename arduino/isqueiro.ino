const int pinoLed = D12; //PINO DIGITAL UTILIZADO PELO LED
const int pinoSensor = D3; //PINO DIGITAL UTILIZADO PELO SENSOR
int dt = 100;

void setup(){
  pinMode(pinoSensor, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoLed, LOW); //LED INICIA DESLIGADO
  Serial.begin(9600);
}
 
void loop(){
  Serial.println(digitalRead(pinoSensor));
  if(digitalRead(pinoSensor) == LOW){ //SE A LEITURA DO PINO FOR IGUAL A LOW, FAZ
      digitalWrite(pinoLed, HIGH); //ACENDE O LED
  }else{ //SENÃO, FAZ
    digitalWrite(pinoLed, LOW); //APAGA O LED
  }
  delay(dt); 
}