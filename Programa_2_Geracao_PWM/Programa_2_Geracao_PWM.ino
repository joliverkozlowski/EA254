// The number of the LED pin
const int ledPin1 = 17;  // 17 corresponds to GPIO17
const int ledPin2 = 27;  // 27 corresponds to GPIO27

// Setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  // attach the channel to the GPIOs to be controlled
  ledcAttachPin(ledPin1, ledChannel);
  ledcAttachPin(ledPin2, ledChannel);
}

void loop(){
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
  {
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
  {
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);   
    delay(15);
  }
}
