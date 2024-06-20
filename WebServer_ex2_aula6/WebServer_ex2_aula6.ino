/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-controls-led-via-web
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define LED_PIN 26  // ESP32 pin GPIO26 connected to LED
#define LED_ON_BOARD  2

const char* ssid     = "LMI_2";
const char* password = "ea254@ea254";

AsyncWebServer server(80);

int LED_state = LOW;

// Geração do código HTML com o status atual do led e links para alterar tal status
String getHTML() {
  String html = "<!DOCTYPE HTML>\n";
  html += "<html>\n";
  html += "<head><title>Led control using ESP32</title></head>\n";
  html += "<body>\n";
  html += "<p>LED state: <span style='color: red;'>";
  if (LED_state == LOW)
    html += "OFF";
  else
    html += "ON";
  html += "</span></p>\n";
  html += "<p><a href='/led1/on'>Turn ON</a><\p>\n";
  html += "<p><a href='/led1/off'>Turn OFF</a><\p>\n";
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

  // home page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("ESP32 Web Server: New request received:");
    Serial.println("GET /");
    request->send(200, "text/html", getHTML());
  });

  // Route to control the LED
  server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("ESP32 Web Server: New request received:");
    Serial.println("GET /led1/on");
    LED_state = HIGH;
    digitalWrite(LED_PIN, LED_state);
    request->send(200, "text/html", getHTML());
  });
  server.on("/led1/off", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("ESP32 Web Server: New request received:");
    Serial.println("GET /led1/off");
    LED_state = LOW;
    digitalWrite(LED_PIN, LED_state);
    request->send(200, "text/html", getHTML());
  });

  // Start the server
  server.begin();
}

void loop() {
  // Your code 
  digitalWrite(LED_ON_BOARD,HIGH);
  delay(500);
  digitalWrite(LED_ON_BOARD,LOW);
  delay(500);
}
