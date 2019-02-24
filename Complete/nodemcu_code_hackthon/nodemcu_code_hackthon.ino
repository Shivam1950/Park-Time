

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "parking-manager-58b3f.firebaseio.com"
#define FIREBASE_AUTH "xfQ8R78Q8hqV7tEQJjZSk7WwFsTDgvtHKDRTm5hd" 
#define WIFI_SSID "shivamredmi"
#define WIFI_PASSWORD "8 8 8 8 "


int sensorValue;
float voltage;
int led;

void setup() {
  
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


void loop() {

  sensorValue = analogRead(A0);
  voltage = sensorValue * (5.0 / 1023.0); 

  if(voltage < 3.20){
  
  Firebase.setInt("parking-manager-58b3f/land_1", 0);
  led = 0;
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }}
  else{
    Firebase.setInt("parking-manager-58b3f/land_1", 1);
    led = 1;
  if (Firebase.failed()) {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());  
      return;
  }
  }

  if(led == 1){
    digitalWrite(4, HIGH);
  }
  else{
    digitalWrite(4, LOW);
  }
  delay(100);
}
