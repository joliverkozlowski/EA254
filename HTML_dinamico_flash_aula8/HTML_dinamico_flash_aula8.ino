/*
 * Fonte: https://esp32io.com/tutorials/esp32-controls-led-via-web
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
//See https://www.arduino.cc/reference/en/libraries/espasyncwebserver/
#include <LittleFS.h>

#define LED_PIN 26  // ESP32 pin GPIO26 connected to LED
#define LED_ON_BOARD  2

// Replace with your network credentials
const char* ssid     = "Roger";
const char* password = "Roger050505";

AsyncWebServer server(80);

int LED_state = LOW;

const char* PARAM_INPUT_1 = "input1";
String inputMessage = "Texto";
String ledState, ledState_Inverse;
String IP_client;

// Function to replace the placeholders
String processor(const String& var){
  Serial.println(var);
  if(var == "LED_STATE"){
    if(LED_state == LOW)
    { ledState = "off"; } else{ ledState = "on"; }
    return ledState;
  }
  if(var == "LED_STATE_UPPERCASE"){
    if(LED_state == LOW)
    { ledState = "OFF"; } else{ ledState = "ON"; }
    return ledState;
  }
  if(var == "LED_STATE_INVERSE"){
    if(LED_state == LOW)
    { ledState_Inverse = "on"; } else{ ledState_Inverse = "off"; }
    return ledState_Inverse;
  }
  if(var == "LED_STATE_INVERSE_UPPERCASE"){
    if(LED_state == LOW)
    { ledState_Inverse = "ON"; } else{ ledState_Inverse = "OFF"; }
    return ledState_Inverse;
  }
  if(var == "MSG_TEXT"){
    return inputMessage;
  }
  return String();
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_ON_BOARD, OUTPUT);
  digitalWrite(LED_ON_BOARD, HIGH);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LED_state);

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
    Serial.println("GET /");
    request->send(LittleFS, "/index.html", String(), false, processor);
  });
  
  // Route to control the LED
  server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("GET /led1/on");
    LED_state = HIGH;
    digitalWrite(LED_PIN, LED_state);
    request->send(LittleFS, "/index.html", String(), false, processor);
  });
  server.on("/led1/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("GET /led1/off");
    LED_state = LOW;
    digitalWrite(LED_PIN, LED_state);
    request->send(LittleFS, "/index.html", String(), false, processor);
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
  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get_text_box", HTTP_GET, [] (AsyncWebServerRequest *request) {
    //String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
    else {
      inputMessage = "Text Box: No message sent";
      inputParam = "none";
    }
    inputMessage= "@" + inputMessage + "@"; 
    Serial.print("Texto na caixa de texto: "); Serial.println(inputMessage);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: \"" + inputMessage +
                                     "\"<br><a href=\"/\">Return to Home Page</a>");
  });
  server.on("/printIp", HTTP_GET, [](AsyncWebServerRequest *request){ 
    request->send(200, "text/plain", "ok");
    Serial.print("Received request from client with IP: ");
    Serial.println(request->client()->remoteIP());
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
