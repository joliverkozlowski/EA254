#define LED 17
#define InputPin 26

int PinState = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  pinMode(InputPin,INPUT);
}

void loop()
{
  Serial.println("--> Hello World!");
  // Write HIGH
  digitalWrite(LED,HIGH);
  PinState = digitalRead(InputPin);
  Serial.print("Valor lido = "); Serial.println(PinState);
  delay(1000);
  // Write LOW
  digitalWrite(LED,LOW);
  PinState = digitalRead(InputPin);
  Serial.print("Valor lido = "); Serial.println(PinState);
  delay(1000);
}