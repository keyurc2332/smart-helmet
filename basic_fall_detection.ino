// Smart Helmet - Basic Fall Detection Example
// Simplified version for learning and testing
// 
// This example demonstrates the core functionality:
// 1. Read accelerometer data
// 2. Detect rapid acceleration (fall)
// 3. Send alert via WiFi

#include <Wire.h>
#include <MPU6050.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// ============ CONFIGURATION ============

// WiFi Settings
const char* WIFI_SSID = "YOUR_SSID";
const char* WIFI_PASSWORD = "YOUR_PASSWORD";

// Pushbullet Settings
const char* API_KEY = "o.YOUR_API_KEY";
const char* API_HOST = "api.pushbullet.com";
const int API_PORT = 443;

// Fall Detection Settings
const float FALL_THRESHOLD = 1.5;  // G-force threshold
const int ALERT_COOLDOWN = 60000;  // 1 minute (ms)

// ============ OBJECTS ============

MPU6050 accelerometer;
WiFiClientSecure wifiClient;

// ============ VARIABLES ============

unsigned long lastAlertTime = 0;
boolean wifiConnected = false;

// ============ SETUP ============

void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\n=== Smart Helmet System Starting ===\n");

  // Initialize I2C for sensors
  Wire.begin();
  Serial.println("[1/4] Initializing I2C...");
  
  // Initialize accelerometer (MPU6050)
  accelerometer.initialize();
  
  if (!accelerometer.testConnection()) {
    Serial.println("ERROR: MPU6050 not found!");
    while(1);  // Halt if sensor not found
  }
  Serial.println("[2/4] MPU6050 sensor OK ✓");

  // Connect to WiFi
  Serial.println("[3/4] Connecting to WiFi...");
  connectToWiFi();

  // Ready!
  Serial.println("[4/4] System ready for operation ✓");
  Serial.println("\n=== System Ready ===\n");
  Serial.println("Monitoring for falls...\n");
}

// ============ MAIN LOOP ============

void loop() {
  // Read accelerometer
  int16_t accelX, accelY, accelZ;
  accelerometer.getAcceleration(&accelX, &accelY, &accelZ);

  // Convert to G-forces (16384 = 1G)
  float gX = accelX / 16384.0;
  float gY = accelY / 16384.0;
  float gZ = accelZ / 16384.0;

  // Calculate total acceleration magnitude
  float magnitude = sqrt(gX*gX + gY*gY + gZ*gZ);

  // Print sensor data to Serial Monitor
  Serial.print("Accel: X=");
  Serial.print(gX, 2);
  Serial.print("G, Y=");
  Serial.print(gY, 2);
  Serial.print("G, Z=");
  Serial.print(gZ, 2);
  Serial.print("G | Magnitude=");
  Serial.print(magnitude, 2);
  Serial.print("G | Threshold=");
  Serial.println(FALL_THRESHOLD, 2);

  // Check for fall
  if (magnitude > FALL_THRESHOLD) {
    detectFall(gX, gY, gZ, magnitude);
  }

  // Small delay to avoid overwhelming serial output
  delay(500);
}

// ============ FALL DETECTION ============

void detectFall(float accelX, float accelY, float accelZ, float magnitude) {
  // Check if enough time has passed since last alert
  unsigned long currentTime = millis();
  
  if (currentTime - lastAlertTime < ALERT_COOLDOWN) {
    Serial.println("Alert cooldown active, skipping...");
    return;
  }

  // Log the detected fall
  Serial.println("\n╔════════════════════════════════════╗");
  Serial.println("║  🚨 FALL DETECTED!                 ║");
  Serial.println("╚════════════════════════════════════╝");
  Serial.print("Acceleration Magnitude: ");
  Serial.print(magnitude, 2);
  Serial.println(" G");
  Serial.print("Time: ");
  Serial.println(currentTime);

  // Send alert
  if (wifiConnected) {
    sendPushbulletAlert(magnitude);
    lastAlertTime = currentTime;
    Serial.println("Alert sent! Cooling down for 1 minute...\n");
  } else {
    Serial.println("ERROR: WiFi not connected, cannot send alert");
    Serial.println("Retrying WiFi connection...\n");
    connectToWiFi();
  }
}

// ============ WiFi CONNECTION ============

void connectToWiFi() {
  Serial.print("Connecting to: ");
  Serial.println(WIFI_SSID);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  int maxAttempts = 20;

  while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✓ WiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Signal Strength: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm\n");
    wifiConnected = true;
  } else {
    Serial.println("\n✗ WiFi Connection Failed!");
    Serial.println("Will retry when fall is detected.\n");
    wifiConnected = false;
  }
}

// ============ PUSHBULLET API ============

void sendPushbulletAlert(float magnitude) {
  Serial.println("Sending Pushbullet alert...");

  // Create JSON payload
  String jsonPayload = "{";
  jsonPayload += "\"type\":\"note\",";
  jsonPayload += "\"title\":\"🚨 Fall Detection Alert\",";
  jsonPayload += "\"body\":\"Fall detected with magnitude ";
  jsonPayload += magnitude;
  jsonPayload += "G. Immediate assistance may be needed.\"";
  jsonPayload += "}";

  // Connect to Pushbullet
  Serial.print("Connecting to ");
  Serial.println(API_HOST);
  
  if (!wifiClient.connect(API_HOST, API_PORT)) {
    Serial.println("Connection failed!");
    return;
  }

  Serial.println("Connected to Pushbullet API");

  // Send HTTP POST request
  Serial.println("Sending POST request...");
  
  wifiClient.print("POST /v2/pushes HTTP/1.1\r\n");
  wifiClient.print("Host: ");
  wifiClient.print(API_HOST);
  wifiClient.print("\r\n");
  wifiClient.print("Content-Type: application/json\r\n");
  wifiClient.print("Authorization: Bearer ");
  wifiClient.print(API_KEY);
  wifiClient.print("\r\n");
  wifiClient.print("Content-Length: ");
  wifiClient.print(jsonPayload.length());
  wifiClient.print("\r\n\r\n");
  wifiClient.print(jsonPayload);

  // Wait for response
  delay(1000);

  // Read response
  while (wifiClient.available()) {
    String line = wifiClient.readStringUntil('\n');
    Serial.println(line);
  }

  wifiClient.stop();
  Serial.println("✓ Alert sent successfully!\n");
}

// ============ HELPER FUNCTIONS ============

// Get WiFi signal strength in percentage
int getWiFiSignalStrength() {
  int rssi = WiFi.RSSI();
  // Convert RSSI to percentage (rough approximation)
  // -30 dBm = 100%, -90 dBm = 0%
  return constrain(map(rssi, -90, -30, 0, 100), 0, 100);
}

// Print system status
void printSystemStatus() {
  Serial.println("\n=== System Status ===");
  Serial.print("WiFi Connected: ");
  Serial.println(wifiConnected ? "Yes" : "No");
  
  if (wifiConnected) {
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Signal Strength: ");
    Serial.print(getWiFiSignalStrength());
    Serial.println("%");
  }
  
  Serial.print("Uptime (ms): ");
  Serial.println(millis());
  Serial.println();
}

// ============ CALIBRATION ============

// Run this to find the right threshold for your device
void calibrateThreshold() {
  Serial.println("\n=== CALIBRATION MODE ===");
  Serial.println("Keep device still for 5 seconds...");
  
  float maxMagnitude = 0;
  unsigned long endTime = millis() + 5000;

  while (millis() < endTime) {
    int16_t ax, ay, az;
    accelerometer.getAcceleration(&ax, &ay, &az);
    
    float gx = ax / 16384.0;
    float gy = ay / 16384.0;
    float gz = az / 16384.0;
    float magnitude = sqrt(gx*gx + gy*gy + gz*gz);
    
    if (magnitude > maxMagnitude) {
      maxMagnitude = magnitude;
    }
    
    delay(10);
  }

  Serial.print("Baseline (no movement): ");
  Serial.println(maxMagnitude, 2);
  Serial.println("Now perform a fall simulation...");
}

/*
 * ============ USAGE GUIDE ============
 * 
 * 1. Fill in your WiFi SSID and password
 * 2. Get API key from https://www.pushbullet.com/account
 * 3. Upload code to Arduino/ESP8266
 * 4. Open Serial Monitor (115200 baud)
 * 5. Shake device to simulate fall
 * 6. Check phone for Pushbullet notification
 * 
 * ============ TROUBLESHOOTING ============
 * 
 * No WiFi: Check SSID and password
 * No alert: Check API key and internet connection
 * No sensor data: Check I2C connections (SDA/SCL)
 * False alarms: Increase FALL_THRESHOLD value
 * Missed falls: Decrease FALL_THRESHOLD value
 * 
 * ============ SENSOR CALIBRATION ============
 * 
 * Baseline acceleration (stationary): ~0.95-1.05 G
 * Safe movement: 1.0-1.3 G
 * Fall: >1.5 G
 * 
 * Adjust FALL_THRESHOLD based on your testing
 */
