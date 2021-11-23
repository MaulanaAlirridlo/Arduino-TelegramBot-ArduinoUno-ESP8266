#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
String data;
char c;

int sensor = A0;
int val;

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  delay(10);
}

void loop() {
  delay(7000);
  val = analogRead(sensor);
  val = map(val, 1023, 0, 0, 100);
  mySerial.print(val);
  Serial.println(val);   
}
