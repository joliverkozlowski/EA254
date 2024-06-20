
#define LED_BUILTIN 2
#define LED1 17
const int LED2 = 27;
int PinState = 0;
bool change = 0;
// Setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;



// the setup function runs once when you power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED1,OUTPUT);
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  // attach the channel to the GPIOs to be controlled
  ledcAttachPin(LED2, ledChannel);
  Serial.begin (115200);

  xTaskCreatePinnedToCore (
    loop1,     // Function to implement the task
    "loop1",   // Name of the task
    1000,      // Stack size in words
    NULL,      // Task input parameter
    0,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run (0 or 1)
  );

  xTaskCreatePinnedToCore (
    loop2,     // Function to implement the task
    "loop2",   // Name of the task
    1000,      // Stack size in words
    NULL,      // Task input parameter
    0,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run (0 or 1)
  );

  xTaskCreatePinnedToCore (
    loop3,     // Function to implement the task
    "loop3",   // Name of the task
    1000,      // Stack size in words
    NULL,      // Task input parameter
    0,         // Priority of the task
    NULL,      // Task handle.
    1          // Core where the task should run (0 or 1)
  );

  xTaskCreatePinnedToCore (
    loop4,     // Function to implement the task
    "loop4",   // Name of the task
    1000,      // Stack size in words
    NULL,      // Task input parameter
    0,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run (0 or 1)
  );


}

// the loop function runs over and over again forever
void loop() {
}

// the loop2 function also runs forever but as a parallel task
void loop1 (void* pvParameters) {
  while (1) {
  //Serial.print ("loop1(): 'Led da placa piscando' running in core ");
  //Serial.println (xPortGetCoreID());
  digitalWrite (LED_BUILTIN, HIGH);  // turn the LED_BUILTIN on
   vTaskDelay(1000);  // wait for a second
  digitalWrite (LED_BUILTIN, LOW); // turn the LED_BUILTIN off
   vTaskDelay(1000);  // wait for a second
  }
}

void loop2 (void* pvParameters) {
  while (1) {
  //Serial.print ("loop1(): 'Leitura da porta IO do LED1' running in core ");
  //Serial.println (xPortGetCoreID());
  PinState = digitalRead(LED1);
  if ( change != PinState){
    change = PinState;
    Serial.print("Valor lido = "); Serial.println(PinState);
  }
   vTaskDelay(1000);
  }
}

void loop3 (void* pvParameters) {
  while (1) {
    //Serial.print ("--> loop3() running in core ");
    //Serial.println (xPortGetCoreID());
    digitalWrite(LED1,HIGH); // turn the LED on
     vTaskDelay(500);
    digitalWrite(LED1,LOW);  // turn the LED off
     vTaskDelay(500);
  }
}

void loop4 (void* pvParameters) {
  while (1) {
 // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++)
  {
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
     vTaskDelay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--)
  {
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);   
     vTaskDelay(15);
  }
  }
}