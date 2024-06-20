#define LED_BUILTIN 2
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode (LED_BUILTIN, OUTPUT);

  Serial.begin (115200);

  xTaskCreatePinnedToCore (
    loop2,     // Function to implement the task
    "loop2",   // Name of the task
    1000,      // Stack size in words
    NULL,      // Task input parameter
    5,         // Priority of the task
    NULL,      // Task handle.
    1          // Core where the task should run
  );
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite (LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay (1000);  // wait for a second
  digitalWrite (LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
  delay (1000);  // wait for a second
  Serial.print ("Task loop() running in core ");
  Serial.println (xPortGetCoreID());
}

// the loop2 function also runs forever but as a parallel task
void loop2 (void* pvParameters) {
  while (1) {
    Serial.print ("Hello, ");
    delay (500); // wait for half a second
    Serial.print ("task loop2() running in core ");
    Serial.println (xPortGetCoreID());
    delay (500); // wait for half a second
  }
}