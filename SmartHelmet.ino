#include <wire.h>
#include <MPU6050.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>  // For secure connection
#include <ArduinoJson.h>       // For JSON handling in Pushbullet requests

// WiFi and Pushbullet credentials
const char* ssid = "AndroidAPA9D5";          // Your WiFi SSID
const char* password = "labdhi23";           // Your WiFi Password
const char* apiKey = "o.K263B7Sma88rg4j6PuKmGoNqup0YxkAw"; // Pushbullet API Key

MPU6050 mpu;  // Create MPU6050 object

// Pushbullet API URL
const char* pushbullet_url = "https://api.pushbullet.com/v2/pushes";

// Device identifier (empty to send to all devices)
String deviceIdentifier = "";

// WiFi Client for Pushbullet connection
WiFiClientSecure wifiClient;

void setup() {
  Serial.begin(115200);

  // Initialize I2C communication and MPU6050 sensor
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  } else {
    Serial.println("MPU6050 connected successfully");
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi.");
}

void loop() {
  int16_t ax, ay, az;

  // Read accelerometer data
  mpu.getAcceleration(&ax, &ay, &az);

  // Convert raw values to acceleration in 'g'
  float accel_x = ax / 16384.0;
  float accel_y = ay / 16384.0;
  float accel_z = az / 16384.0;

  // Calculate acceleration magnitude
  float accel_magnitude = sqrt(accel_x * accel_x + accel_y * accel_y + accel_z * accel_z + accel_x);

  // Print the calculated magnitude to the Serial Monitor
  Serial.print("Acceleration Magnitude: ");
  Serial.println(accel_magnitude);

  // Fall detection threshold set to 1.5g (you can adjust this)
  if (accel_magnitude > 1.5) {
    Serial.println("Fall detected");
    sendFallAlert();  // Send Pushbullet notification when fall is detected
    delay(60000);     // Prevent spamming alerts (wait 1 minute)
  }

  delay(500);  // Delay for 500ms between readings
}

void sendFallAlert() {
  if (WiFi.status() == WL_CONNECTED) {
    // Prepare the Pushbullet notification JSON
    DynamicJsonDocument doc(1024);
    doc["type"] = "note";
    doc["title"] = "Fall Detection Alert";
    doc["body"] = "Fall detected! Immediate assistance may be needed.";
    doc["device_iden"] = deviceIdentifier;

    // Send Pushbullet notification
    String jsonData;
    serializeJson(doc, jsonData);

    // Begin secure HTTPS connection
    wifiClient.setInsecure();  // Bypass SSL certificate verification (for testing purposes)

    // Open connection
    if (wifiClient.connect("api.pushbullet.com", 443)) {
      wifiClient.println("POST /v2/pushes HTTP/1.1");
      wifiClient.println("Host: api.pushbullet.com");
      wifiClient.println("Content-Type: application/json");
      wifiClient.println("Content-Length: ");
      wifiClient.println(jsonData.length());
      wifiClient.println("Authorization: Bearer " + String(apiKey));
      wifiClient.println();
      wifiClient.print(jsonData);

      Serial.println("Push notification sent!");
    } else {
      Serial.println("Failed to connect to Pushbullet.");
    }
  } else {
    Serial.println("WiFi not connected.");
  }
}
