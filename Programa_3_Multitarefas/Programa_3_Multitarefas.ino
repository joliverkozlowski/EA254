
#define LED_BUILTIN 2
#define LED 17

// the setup function runs once when you power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED,OUTPUT);

  Serial.begin (115200);

  xTaskCreatePinnedToCore (
    loop2,     // Function to implement the task
    "loop2",   // Name of the task
    1000,      // Stack size in words
    NULL,      // Task input parameter
    0,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run (0 or 1)
  );
}

// the loop function runs over and over again forever
void loop() {
  Serial.print ("loop() running in core ");
  Serial.println (xPortGetCoreID());
  digitalWrite (LED_BUILTIN, HIGH);  // turn the LED_BUILTIN on
  delay (1000);  // wait for a second
  digitalWrite (LED_BUILTIN, LOW); // turn the LED_BUILTIN off
  delay (1000);  // wait for a second
}

// the loop2 function also runs forever but as a parallel task
void loop2 (void* pvParameters) {
  while (1) {
    Serial.print ("--> loop2() running in core ");
    Serial.println (xPortGetCoreID());
    digitalWrite(LED,HIGH); // turn the LED on
    delay (500);
    digitalWrite(LED,LOW);  // turn the LED off
    delay (500);
  }
}