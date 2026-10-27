#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
 
#define WIFI_SSID "Shukla"
#define WIFI_PASSWORD "apn45979"
#define API_KEY "AIzaSyAZKNYVMUbeW9lh-b1uGWGb4tuf_xAXCSc"
#define DATABASE_URL "https://esp32-firebase-project-6a28e-default-rtdb.asia-southeast1.firebasedatabase.app"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() 
{
  Serial.begin(115200);
  
  // getting WiFi connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to Wi-Fi!");
  
  // Firebase Setup
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL; 
  
  if (Firebase.signUp(&config, &auth, "", "")) 
  {
    Serial.println("Firebase SignUp Done!");
  }
  else 
  {
    Serial.println(config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
  Serial.println("----*Setup Complete*----");
  Serial.println("Type DATA in the serial monitor, press enter");
}

void loop() 
{
  if(Firebase.ready() && Serial.available() > 0)
  {
    String inputData = Serial.readStringUntil('\n');
    inputData.trim();
    
    if(inputData.length() > 0)
    {
      Serial.print("Sending to Firebase.....");

      if(Firebase.RTDB.setString(&fbdo, "/serialData/message", inputData))
      {
        Serial.println("Data sent successfully!!");
      }
      else
      {
        Serial.print("Failed to send data!");
      }
      Serial.println("----------------------------------------");
    }
  }
}