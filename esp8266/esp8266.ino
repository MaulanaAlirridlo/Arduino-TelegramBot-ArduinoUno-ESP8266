#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

String data;
char c;
 
void setup() {
 
  Serial.begin(115200);
  WiFi.begin("Net", "11111111");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
  Serial.println("Connected");
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    while(Serial.available()>0){
    delay(10);
      c = Serial.read();
      data += c;
    }
    if (data.length()>0) {
      HTTPClient http;
  
      http.begin("http://192.168.43.152:8000/");
      http.addHeader("Content-Type", "text/plain");
      int httpCode = http.POST(data);              //Send the request
      String payload = http.getString();           //Get the response payload
      delay(10);
      data = "";

      http.end();  //Close connection
    }
  }
  delay(100);
 
}
