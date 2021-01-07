//add the wifi and firebase libraries
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

//define internet connections to the router
#define w_SSID "wifi_name"
#define w_PASSWORD "wifi_password"

//define firebase credentials
#define FIREBASE_HOST "https://example.firebaseio.com/"
#define FIREBASE_AUTH "firebase realtime database sectret key"

//gpio pin 5 
#define relay 5

//Define FirebaseESP8266 data object
FirebaseData fbdo;

FirebaseJson json;

//message read from the rtdb
String msg;

void printResult(FirebaseData &data);

void setup() {
  //init serial and gpio	
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  
  //init wifi connection
  WiFi.begin(w_SSID, w_PASSWORD);
  Serial.print("Connecting to WiFi Router");
  while (WiFi.status() != WL_CONNECTED)  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected to WiFi with the IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  //init firebase connection
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  //read message from rtdb and make decision based on the data received
  if (Firebase.getString(fbdo, "/message/")) {
    msg = fbdo.stringData();
    Serial.println(msg);
    if (msg.equals("on")) {
      lightOn();
      delay(1000);
    }
    if (msg.equals("off")) {
      lightOff();
      delay(1000);
    }
  }
}

//set gpio pin high
void lightOn() {
  digitalWrite(relay, HIGH);
  delay(400);
}

//set gpio pin low
void lightOff() {
  digitalWrite(relay, LOW);
  delay(400);
}
