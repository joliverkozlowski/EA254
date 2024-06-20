#define BUZZER 26
#define BUTTON 18

struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

Button button1 = {BUTTON, 0, false};

//variables to keep track of the timing of recent interrupts
unsigned long button_time = 0;  
unsigned long last_button_time = 0; 

void IRAM_ATTR isr() {
  button_time = millis();
  if (button_time - last_button_time > 250) {
    button1.numberKeyPresses++;
    button1.pressed = true;
    last_button_time = button_time;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(button1.PIN, INPUT_PULLUP);
  pinMode(BUZZER,OUTPUT);
  attachInterrupt(button1.PIN, isr, FALLING);
}

void loop() {
    if (button1.pressed) {
      Serial.printf("Button has been pressed %u times\n", button1.numberKeyPresses);
      button1.pressed = false;
      digitalWrite(BUZZER,HIGH);
      delay(1000);
      digitalWrite(BUZZER,LOW);
    }
}