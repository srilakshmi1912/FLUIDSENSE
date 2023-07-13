
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define FIREBASE_HOST "fir-esp8266-b9605-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "G4gwq0HoEPcDXhpCfxBzxigPhLCsscWGTY5mddZ9"
#define WIFI_SSID "D-Link"
#define WIFI_PASSWORD "sh4712592179"  


int ldrPin = A0; // the analog input pin for the LDR
int buzzerPin = D1; 

FirebaseData firebaseData;     // Declare the Firebase Data object in the global scope
int val=0;      // Declare global variable to store value
void setup() {
  Serial.begin(115200);                                   
  Serial.println("Serial communication started\n\n");           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                    
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());//print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);// connect to firebase
  Firebase.reconnectWiFi(true);
  delay(10000);
  pinMode(buzzerPin, OUTPUT); 
}

void loop() 
{ 

 int ldrValue = analogRead(ldrPin); // Read the analog value from the LDR module
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  if (ldrValue < 900) {  // If laser light is detected by the LDR
    tone(buzzerPin, 600, 250); // 440 Hz tone for 500 milliseconds
    delay(250); // Wait for 500 milliseconds
    digitalWrite(buzzerPin, LOW); 
    delay(1000);   
    Firebase.pushInt(firebaseData, "/DripStatus", ldrValue); 
  }
  else {
    digitalWrite(buzzerPin, LOW);  // Turn off buzzer
    Firebase.pushInt(firebaseData, "/DripStatus", ldrValue);
  }
  delay(10000); // wait for 10 second before taking the next reading
}