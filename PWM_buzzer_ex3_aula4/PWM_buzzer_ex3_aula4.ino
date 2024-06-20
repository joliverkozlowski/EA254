#define PWM_PIN 26

int freq = 2000;
int channel = 0;
int resolution = 8;
  
void setup() {  
  Serial.begin(115200);
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(PWM_PIN, channel);
}
  
void loop() {

  delay(2000);
  Serial.printf("\n\n========> Starting loop:\n");

  ledcWriteTone(channel, 2500);
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle = dutyCycle + 20) {
    Serial.printf("DutyCycle = %d\n", dutyCycle);
    ledcWrite(channel, dutyCycle);
    delay(1000);
  }
  
  ledcWrite(channel, 127); // Dutycycle = 127 em 255
  for (int freq = 250; freq < 8000; freq = freq + 250) {
    Serial.printf("Freq = %d\n", freq);
    ledcWriteTone(channel, freq);
    delay(1000);
  } 
}