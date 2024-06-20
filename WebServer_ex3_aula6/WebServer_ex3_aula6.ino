/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-web-server
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define LED_ON_BOARD  2

const char* ssid     = "LMI_2";
const char* password = "ea254@ea254";

AsyncWebServer server(80);

float getTemperature() {
  // YOUR SENSOR IMPLEMENTATION HERE
  // simulate the temperature value
  float temp_x100 = random(0, 10000);  // a ramdom value from 0 to 10000
  return temp_x100 / 100;              // return the simulated temperature value from 0 to 100 in float
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_ON_BOARD, OUTPUT);
  digitalWrite(LED_ON_BOARD, HIGH);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Trying to connect to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the ESP32's IP address
  Serial.print("ESP32 Web Server's IP address: ");
  Serial.println(WiFi.localIP());

  // Define a route to serve the HTML page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
  Serial.println("ESP32 Web Server: New request received:");  // for debugging
  Serial.println("GET /");                                    // for debugging

    // get temperature from sensor
    float temperature = getTemperature();
    // Format the temperature with two decimal places
    String temperatureStr = String(temperature, 2);

    String html = "<!DOCTYPE HTML>";
    html += "<html>\n";
    html += "<head><title>ESP32 Web Server</title></head>\n";
    html += "<body>\n";
    html += "<p>Temperature: <span style=\"color: red;\">";
    html += temperature;
    html += "&deg;C</span>";
    html += "</p>\n";
    html += "<body>\n</html>";

    request->send(200, "text/html", html);
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

