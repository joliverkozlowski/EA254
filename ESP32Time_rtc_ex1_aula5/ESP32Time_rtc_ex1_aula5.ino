#include <ESP32Time.h>

ESP32Time rtc;

void setup() {
  Serial.begin(115200);
  //rtc.setTime(30, 24, 15, 17, 1, 2021);  // 17th Jan 2021 15:24:30
  //rtc.setTime(1609459200);  // 1st Jan 2021 00:00:00, ver UNIX TIME STAMP em https://www.unixtimestamp.com/
  //rtc.offset = 7200; // change offset value
}

void loop() {
//  Serial.println(rtc.getTime());          //  (String) 15:24:38
//  Serial.println(rtc.getDate());          //  (String) Sun, Jan 17 2021
//  Serial.println(rtc.getDate(true));      //  (String) Sunday, January 17 2021
//  Serial.println(rtc.getDateTime());      //  (String) Sun, Jan 17 2021 15:24:38
//  Serial.println(rtc.getDateTime(true));  //  (String) Sunday, January 17 2021 15:24:38
//  Serial.println(rtc.getTimeDate());      //  (String) 15:24:38 Sun, Jan 17 2021
//  Serial.println(rtc.getTimeDate(true));  //  (String) 15:24:38 Sunday, January 17 2021
//
//  Serial.println(rtc.getMicros());        //  (long)    723546
//  Serial.println(rtc.getMillis());        //  (long)    723
//  Serial.println(rtc.getEpoch());         //  (long)    1609459200
//  Serial.println(rtc.getSecond());        //  (int)     38    (0-59)
//  Serial.println(rtc.getMinute());        //  (int)     24    (0-59)
//  Serial.println(rtc.getHour());          //  (int)     3     (1-12)
//  Serial.println(rtc.getHour(true));      //  (int)     15    (0-23)
//  Serial.println(rtc.getAmPm());          //  (String)  pm
//  Serial.println(rtc.getAmPm(true));      //  (String)  PM
//  Serial.println(rtc.getDay());           //  (int)     17    (1-31)
//  Serial.println(rtc.getDayofWeek());     //  (int)     0     (0-6)
//  Serial.println(rtc.getDayofYear());     //  (int)     16    (0-365)
//  Serial.println(rtc.getMonth());         //  (int)     0     (0-11)
//  Serial.println(rtc.getYear());          //  (int)     2021
//  Serial.println(rtc.getLocalEpoch());    //  (long)    1609459200 epoch without offset
 int i;
  
  Serial.println("--> Step 1:");
  for (i = 1; i <= 10; i++) {
    Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));   // (String) returns time with specified format
    delay(1000);
  }

  Serial.println("--> Step 2:");
  rtc.setTime(20, 10, 14, 5, 6, 2024);  // 05/06/2024 (DD/MM/YYYY), 14:10:20 HH:MM:SS
  for (i = 1; i <= 10; i++) {
    Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));   // (String) returns time with specified format
    delay(1000);
  }

  Serial.println("--> Step 3:");
  rtc.offset = -10800; // change offset value
  rtc.setTime(20, 10, 14, 5, 6, 2024);  // 05/06/2024 (DD/MM/YYYY), 14:10:20 HH:MM:SS
  for (i = 1; i <= 10; i++) {
    Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S"));   // (String) returns time with specified format
    delay(1000);
  }

  exit(0);
}