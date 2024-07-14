/*
  Fonte: https://RandomNerdTutorials.com/esp32-date-time-ntp-client-server-arduino/
*/

#include <WiFi.h>
#include "time.h"

const char* ssid     = "Roger";
const char* password = "Roger050505";

const char* ntpServer = "pool.ntp.org";
//const char* ntpServer = "181.213.132.2";
//const char* ntpServer = "200.160.7.196";
const long  gmtOffset_sec = -3*3600;
const int   daylightOffset_sec = 0; //3600;

struct tm timeinfo;
String Local_IP;

void setup(){
  Serial.begin(115200);
  delay(5000); // Aguardar alguns segundos antes de enviar texto para a janela do Serial Monitor

  // Connect to Wi-Fi
  Serial.print("Trying to connect to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected to ");
  Serial.println(ssid);
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
  Local_IP = WiFi.localIP().toString();
  IPAddress primaryDNS(192, 168, 0, 1);
  
  // Init and get the time
  while (!getLocalTime(&timeinfo)){
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    delay(500);
    Serial.print("x");
  }
  printLocalTime();

  // Disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop(){
  delay(5000);
  printLocalTime();
}

void printLocalTime(){
  String Local_IP_Date_Time;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  char Local_Date_Time[50]; //50 chars should be enough
  // https://www.ibm.com/docs/en/i/7.3?topic=functions-strftime-convert-datetime-string
  strftime(Local_Date_Time, sizeof(Local_Date_Time), ", %d/%m/%Y, %H:%M:%S", &timeinfo);
  Local_IP_Date_Time = Local_IP;
  Local_IP_Date_Time += Local_Date_Time;
  Serial.println(Local_IP_Date_Time);
}