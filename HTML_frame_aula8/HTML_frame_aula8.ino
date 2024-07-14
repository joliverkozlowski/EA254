/*
 * Fonte https://esp32io.com/tutorials/esp32-controls-led-via-web
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
//See https://www.arduino.cc/reference/en/libraries/espasyncwebserver/
#include <LittleFS.h>

#define LED_1_PIN 25   // ESP32 pin IO25 connected to LED 1
#define LED_2_PIN 26   // ESP32 pin IO26 connected to LED 2
#define LED_ON_BOARD  2

// Replace with your network credentials
const char* ssid     = "Roger";
const char* password = "Roger050505";

AsyncWebServer server(80);

int LED_1_state = HIGH;
int LED_2_state = HIGH;

String ledState, ledState_Inverse;

// Function to replace the placeholders
String processor(const String& var){
  Serial.println(var);
  if(var == "LED_1_STATE"){
    if(LED_1_state == LOW)
    { ledState = "off"; } else{ ledState = "on"; }
    return ledState;
  }
  if(var == "LED_1_STATE_INVERSE"){
    if(LED_1_state == LOW)
    { ledState_Inverse = "on"; } else{ ledState_Inverse = "off"; }
    return ledState_Inverse;
  }
  if(var == "LED_2_STATE"){
    if(LED_2_state == LOW)
    { ledState = "off"; } else{ ledState = "on"; }
    return ledState;
  }
  if(var == "LED_2_STATE_INVERSE"){
    if(LED_2_state == LOW)
    { ledState_Inverse = "on"; } else{ ledState_Inverse = "off"; }
    return ledState_Inverse;
  }
  return String();
}

void setup() {
  Serial.begin(115200);
  delay(5000);

  // Device configuration
  pinMode(LED_1_PIN, OUTPUT);
  digitalWrite(LED_1_PIN, LED_1_state);
  pinMode(LED_2_PIN, OUTPUT);
  digitalWrite(LED_2_PIN, LED_2_state);
  pinMode(LED_ON_BOARD, OUTPUT);
  digitalWrite(LED_ON_BOARD, HIGH);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the ESP32's IP address
  Serial.print("ESP32 Web Server's IP address: ");
  Serial.println(WiFi.localIP());

  if(!LittleFS.begin()) {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  // home page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("GET /index.html");
    request->send(LittleFS, "/index.html", "text/html");
  });
  server.on("/frame_menu.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("GET /frame_menu.html");
    request->send(LittleFS, "/frame_menu.html", "text/html");
  });
  server.on("/led1.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("GET /led1.html");
    request->send(LittleFS, "/led1.html", String(), false, processor);
  });
  server.on("/led2.html", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("GET /led2.html");
    request->send(LittleFS, "/led2.html", String(), false, processor);
  });

  // Route to control LED 1
  server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("GET /led1/on");
    LED_1_state = HIGH;
    digitalWrite(LED_1_PIN, LED_1_state);
    request->send(LittleFS, "/led1.html", String(), false, processor);
  });
  server.on("/led1/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("GET /led1/off");
    LED_1_state = LOW;
    digitalWrite(LED_1_PIN, LED_1_state);
    request->send(LittleFS, "/led1.html", String(), false, processor);
  });

  // Route to control LED 2
  server.on("/led2/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("GET /led2/on");
    LED_2_state = HIGH;
    digitalWrite(LED_2_PIN, LED_2_state);
    request->send(LittleFS, "/led2.html", String(), false, processor);
  });
  server.on("/led2/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("GET /led2/off");
    LED_2_state = LOW;
    digitalWrite(LED_2_PIN, LED_2_state);
    request->send(LittleFS, "/led2.html", String(), false, processor);
  });

  // Serving image files
  server.on("/led_on.gif", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("GET /led_on.gif");
    request->send(LittleFS, "/led_on.gif", "image/gif");
  });
  server.on("/led_off.gif", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("GET /led_off.gif");
    request->send(LittleFS, "/led_off.gif", "image/gif");
  });

  server.on("/printIp", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.print("Received request from client with IP: ");
    Serial.println(request->client()->remoteIP());
    request->send(200, "text/plain", "ok!");
  });

  // Start the server
  server.begin();
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void loop() {
  // Your code 
  digitalWrite(LED_ON_BOARD,HIGH);
  delay(500);
  digitalWrite(LED_ON_BOARD,LOW);
  delay(500);
}
