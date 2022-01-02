#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

String data;
char c;
 
void setup() {
 
  Serial.begin(115200);
  WiFi.begin("Galaxy A52s 5G17E1", "izkz5374");
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
  Serial.println("Connected");
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) {
    while(Serial.available()>0){
    delay(10);
      c = Serial.read();
      data += c;
    }
    if (data.length()>0) {
      HTTPClient http;
  
      http.begin("http://47.254.240.15/");
      http.addHeader("Content-Type", "application/json");
      int httpCode = http.POST(data);
      delay(10);
      data = "";

      http.end();  //Close connection
      delay(1000);
    }
  } else {
    delay(1000);
    Serial.println("Reconnecting");
    WiFi.disconnect();
    WiFi.reconnect();
  }
  delay(100);
 
}
