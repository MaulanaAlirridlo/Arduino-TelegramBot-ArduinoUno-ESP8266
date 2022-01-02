#include <SoftwareSerial.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22
SoftwareSerial mySerial(3,4);
int sensor = A0;
int klembabTanah;
float klembabRuang, suhu, indexPanas;
String json;
int relay = 5;
int siram = 0;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  dht.begin();
  pinMode(relay,OUTPUT);
  digitalWrite(relay,HIGH);
  delay(10);
}

void loop() {
  klembabTanah = analogRead(sensor);
  klembabTanah = map(klembabTanah, 1023, 0, 0, 100);
  klembabRuang = dht.readHumidity();
  suhu = dht.readTemperature();
  indexPanas = dht.computeHeatIndex(suhu, klembabRuang, false);  
  if(klembabTanah < 40) {
    digitalWrite(relay,LOW);
    siram = 1;
    json = String("{\"kelembapan tanah\":")+klembabTanah+",\"suhu ruangan\":"+suhu+",\"kelembapan ruangan\":"+klembabRuang+",\"index panas\":"+indexPanas+",\"siram\":"+siram+"}";
    mySerial.print(json);
    Serial.println(json); 
    delay(81000);
    digitalWrite(relay,HIGH);
    siram = 0;
  }
  else if(suhu > 28.7 && klembabTanah < 46) {
    digitalWrite(relay,LOW);
    siram = 1;
    json = String("{\"kelembapan tanah\":")+klembabTanah+",\"suhu ruangan\":"+suhu+",\"kelembapan ruangan\":"+klembabRuang+",\"index panas\":"+indexPanas+",\"siram\":"+siram+"}";
    mySerial.print(json);
    Serial.println(json); 
    delay(26000);
    digitalWrite(relay,HIGH);
    siram = 0;
  }
  else {
    json = String("{\"kelembapan tanah\":")+klembabTanah+",\"suhu ruangan\":"+suhu+",\"kelembapan ruangan\":"+klembabRuang+",\"index panas\":"+indexPanas+",\"siram\":"+siram+"}";
    mySerial.print(json);
    Serial.println(json); 
  }
  delay(5000);
}
