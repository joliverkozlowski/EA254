#include "LittleFS.h"
 
void setup() {
  Serial.begin(115200);

  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
 
}

int i = 0; 
void loop() {

  delay(5000);  
  i++;
  Serial.printf("--> Loop %d:\n",i); 

  File file = LittleFS.open("/test_example.txt", "r");
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }
  
  Serial.println("File Content:");
  while(file.available()){
    Serial.write(file.read());
  }
  file.close();
  Serial.println("");
 
}