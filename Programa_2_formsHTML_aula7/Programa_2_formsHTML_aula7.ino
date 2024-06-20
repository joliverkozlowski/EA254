/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-controls-led-via-web
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
//See https://www.arduino.cc/reference/en/libraries/espasyncwebserver/
#include <LittleFS.h>

#define LED_PIN 26  // ESP32 pin GPIO26 connected to LED
#define LED_ON_BOARD  2

// Replace with your network credentials
const char* ssid     = "LMI_2";
const char* password = "ea254@ea254";

AsyncWebServer server(80);

int LED_state = LOW;

const char* PARAM_INPUT_1 = "input1";
String inputMessage = "mensagem inicial";

// Geração do código HTML com o status atual do led e links para alterar tal status
String getHTML() {
  String html = "<!DOCTYPE HTML>\n";
  html += "<html>\n";
  html += "<head><title>Led control using ESP32</title></head>\n";
  html += "<body>\n";
  html += "<p><b>State:</b> Led <span style='color: red;'>";
  if (LED_state == LOW) {
    html += "OFF <img src=\"/led_off.gif\"></span></p>\n";
    html += "<p><b>Action:</b> To turn the LED ON <a href='/led1/on'>click here</a>\n";
    html += "or on the following image\n";
    html +="<form action=\"/led1/on\"><input type=\"image\" src=\"/led_on.gif\" alt=\"Submit\"></form></p>\n";
  }
  else {
    html += "ON <img src=\"/led_on.gif\"></span></p>\n";
    html += "<p><b>Action:</b> To turn the LED OFF <a href='/led1/off'>click here</a>\n";
    html += "or on the following image\n";
    html += "<form action=\"/led1/off\"><input type=\"image\" src=\"/led_off.gif\" alt=\"Submit\"></form></p>\n";
  }
  html +="<p><form action=\"/get_text_box\"> Text box: <input type=\"text\" name=\"input1\" value=\" ";
  html += inputMessage;
  html +="\"> <input type=\"submit\" value=\"CLICK\"></form></p>";
  html += "</body>\n";
  html += "</html>";
  return html;
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
    request->send(200, "text/html", getHTML());
  });

  // Route to control the LED
  server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("GET /led1/on");
    LED_state = HIGH;
    digitalWrite(LED_PIN, LED_state);
    request->send(200, "text/html", getHTML());
  });
  server.on("/led1/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("GET /led1/off");
    LED_state = LOW;
    digitalWrite(LED_PIN, LED_state);
    request->send(200, "text/html", getHTML());
  });
  // Serving image files
  server.on("/italogo.gif", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("GET /italogo.gif");
    request->send(LittleFS, "/italogo.gif", "image/gif");
  });
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
