#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"



FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() 
{
  Serial.begin(115200);
  
  // getting WiFi connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to Wi-Fi!");
  
  // Firebase Setup
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL; 
  
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase SignUp OK");
  } else {
    Serial.println(config.signer.signupError.message.c_str());
  }

  // config.token_status_callback = tokenStatusCallback; // Commented out to prevent errors if you haven't defined it

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
  Serial.println("----*Setup Complete*----");
  Serial.println("Type DATA in the serial monitor, press enter:");
}

void loop() 
{
  // FIXED: readdy() changed to ready()
  if(Firebase.ready() && Serial.available() > 0)
  {
    String inputData = Serial.readStringUntil('\n');
    inputData.trim();
    
    if(inputData.length() > 0)
    {
      Serial.print("Sending to Firebase: ");
      Serial.println(inputData);

      if(Firebase.RTDB.setString(&fbdo, "/serialData/message", inputData))
      {
        Serial.println("Data sent successfully!!");
        Serial.println("Path: " + fbdo.dataPath());
        Serial.println("Type: " + fbdo.dataType());
      }
      else
      {
        Serial.print("Failed to send data. Reason: ");
        Serial.println(fbdo.errorReason());
      }
      Serial.println("----------------------------------------");
    }
  }
}