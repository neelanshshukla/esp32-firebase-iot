# ESP32 Firebase IoT Integration

A proof-of-concept IoT project demonstrating how to securely connect an ESP32 microcontroller to Google Firebase to send real-time data to the cloud.

# Features
- Connects to a local Wi-Fi network.
- Authenticates securely with Google Firebase using the `Firebase_ESP_Client` library.
- Reads input from the Serial Monitor and pushes it to the Firebase Realtime Database.
- Uses HTTPS (SSL/TLS) for secure communication.
- **Secure Credentials:** Uses a `secrets.h` file (ignored by Git) to prevent leaking API keys and Wi-Fi passwords.

# Architecture
1. The ESP32 connects to a Wi-Fi network.
2. It authenticates anonymously with Firebase using the provided API Key.
3. When the user types a message in the Serial Monitor, the ESP32 packages it and sends an HTTP POST request to Firebase.
4. The data appears instantly in the Firebase Realtime Database console.

# Hardware & Software Requirements
- **Hardware:** ESP32 Development Board (Standard 30-pin or similar)
- **Software:** Arduino IDE
- **Libraries:**
  - `Firebase ESP Client` (by Mobizt)
  - `ArduinoJson` (v6.21.5 - *v7 is not supported by the Firebase library yet*)
  - `ESP_SSLClient` (by Mobizt)

#  Setup Instructions
1. Clone this repository.
2. In the root directory, duplicate the `secrets.h.example` file and rename the duplicate to `secrets.h`.
3. Open `secrets.h` and fill in your own credentials:
   ```cpp
   #define WIFI_SSID "YOUR_WIFI_NAME"
   #define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
   #define API_KEY "YOUR_FIREBASE_API_KEY"
   #define DATABASE_URL "YOUR_FIREBASE_DATABASE_URL"