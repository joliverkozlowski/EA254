const int Servomotor_Pin = 13;  // Pino 13 corresponds to GPIO13
const int ledChannel = 0;
const int resolution = 10;
const int Nsteps = pow(2,resolution); // duty cycle de 0 a Nsteps-1

// Setting PWM properties
const int T = 20;          // Periodo do sinal de PWM (em ms)
const int Tmin = 0;        // Tmin do pulso (em ms)
const int Tmax = 3;        // Tmax do pulso (em ms)
const int Tdelay = 20;     // tempo em cada posição (em ms)
const int DC_passo = 1;    // passo do duty cycle
const int freq = 1000/T;   // frequência do sinal de PWM (em Hz)

void setup(){
  Serial.begin(115200);
  // configure PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  // attach the channel to the GPIOs to be controlled
  ledcAttachPin(Servomotor_Pin, ledChannel);
}

void loop(){

  // Increase angle of the servomotor
  Serial.println("--> Loop 1");
  for(int dutyCycle = Nsteps*Tmin/T; dutyCycle <= Nsteps*Tmax/T; dutyCycle=dutyCycle+10*DC_passo){
    Serial.printf(" %u",dutyCycle);
    if (dutyCycle == 100*int(dutyCycle/100)) Serial.println("");
    ledcWrite(ledChannel, dutyCycle);
    delay(10*Tdelay);
  }

  // Decrease angle of the servomotor
  Serial.println("");
  Serial.println("--> Loop 2");
  for(int dutyCycle = Nsteps*Tmax/T; dutyCycle >= Nsteps*Tmin/T; dutyCycle=dutyCycle-DC_passo){
    Serial.printf(" %u",dutyCycle);
    if (dutyCycle == 40*int(dutyCycle/40)) Serial.println("");
    ledcWrite(ledChannel, dutyCycle);   
    delay(Tdelay);
  }
}
