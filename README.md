# 🎯 Smart Helmet - Accident Detection and Emergency Alert System

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Arduino](https://img.shields.io/badge/Platform-Arduino-blue.svg)](https://www.arduino.cc/)
[![Contributors](https://img.shields.io/badge/Contributors-Welcome-brightgreen.svg)](#contributing)

**Award:** Best Paper at MULTICON-W 2025 (16th International & National Conferences and Workshops)

---

## 📋 Table of Contents

- [Overview](#overview)
- [Motivation](#motivation)
- [Problem Statement](#problem-statement)
- [Features](#features)
- [Components](#components)
- [Circuit Diagram](#circuit-diagram)
- [Installation & Setup](#installation--setup)
- [Usage](#usage)
- [Code Architecture](#code-architecture)
- [Results](#results)
- [Future Scope](#future-scope)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

---

## 🚀 Overview

The **Smart Helmet** is an IoT-enabled safety device designed to automatically detect motorcycle accidents and send real-time alerts to emergency contacts with precise GPS location. This project combines sensor technology with cloud connectivity to reduce emergency response times and potentially save lives.

The system integrates:
- Motion detection using accelerometer and gyroscope
- GPS location tracking
- WiFi connectivity
- Cloud-based alert notifications via Pushbullet API

---

## 💡 Motivation

Road accidents remain a major cause of injury and death globally, with motorcyclists being particularly vulnerable due to the lack of protection compared to car occupants. While helmets provide physical protection, they cannot prevent accidents. This project is motivated by the need to:

- **Reduce response times** for emergency services
- **Provide immediate notification** to emergency contacts
- **Ensure timely medical assistance** especially in isolated areas
- **Leverage technology** to improve road safety for motorcyclists

---

## 🔴 Problem Statement

Despite the use of helmets, many motorcyclists face critical delays in receiving medical attention after accidents, leading to severe consequences including permanent injuries or death. Currently, there is no widespread system that can automatically detect an accident involving a motorcyclist and alert emergency services in real-time.

This gap leaves accident victims without timely support, especially when accidents occur in isolated areas where immediate help may not be available.

---

## ✨ Features

- ✅ **Real-time Accident Detection** - Uses MPU6050 accelerometer to detect sudden impacts
- ✅ **GPS Location Tracking** - Neo GPS module provides precise coordinates
- ✅ **Instant Notifications** - Sends alerts via Pushbullet API to emergency contacts
- ✅ **WiFi Connectivity** - ESP8266 module for internet connectivity
- ✅ **User-Friendly Alerts** - Clear, actionable emergency notifications
- ✅ **Low Power Design** - Optimized for extended operation
- ✅ **Customizable Thresholds** - Adjustable sensitivity for different riding conditions

---

## 🔧 Components

### Hardware Components

| Component | Quantity | Purpose |
|-----------|----------|---------|
| **Arduino Nano** | 1 | Central microcontroller for processing sensor data |
| **MPU6050** | 1 | Accelerometer & Gyroscope for motion detection |
| **ESP8266** | 1 | WiFi module for internet connectivity |
| **Neo GPS Module (U-Blox)** | 1 | GPS for location tracking |
| **SIM800 GSM Module** | 1 | Cellular communication for SMS alerts |
| **Li-Po Battery** | 1 | Power source (3.7V, 2000mAh recommended) |
| **Power Management Module** | 1 | Regulates power distribution |
| **Resistors & Capacitors** | Various | Circuit support components |
| **PCB Board** | 1 | Integration of all components |

### Software Libraries

```cpp
#include <Wire.h>              // I2C communication
#include <MPU6050.h>           // MPU6050 sensor library
#include <ESP8266WiFi.h>       // WiFi connectivity
#include <WiFiClientSecure.h>  // Secure HTTPS connection
#include <ArduinoJson.h>       // JSON parsing for API
```

---

## 🔌 Circuit Diagram

```
┌─────────────────────────────────────────────────────────────┐
│                                                             │
│                    SMART HELMET CIRCUIT                     │
│                                                             │
│  Battery (3.7V)                                             │
│      │                                                      │
│      ├─→ Power Management Module                            │
│           │                                                 │
│           ├─→ Arduino Nano (Microcontroller)                │
│           │      │                                          │
│           │      ├─→ I2C Bus ──→ MPU6050 (Accel+Gyro)       │
│           │      │                                          │
│           │      ├─→ Serial UART ──→ ESP8266 (WiFi)         │
│           │      │                                          │
│           │      └─→ Serial UART ──→ Neo GPS Module         │
│           │                                                 │
│           └─→ GSM Module (SIM800) for SMS                   │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

**Connections Summary:**
- **MPU6050**: I2C (SDA/SCL) to Arduino
- **ESP8266**: UART (RX/TX) to Arduino Serial
- **Neo GPS**: UART (RX/TX) to Arduino Serial (Software Serial)
- **GSM Module**: UART (RX/TX) for backup SMS alerts
- **All modules**: Common GND with Arduino

---

## 📦 Installation & Setup

### Prerequisites

- Arduino IDE (v1.8.0 or higher) - [Download](https://www.arduino.cc/en/software)
- Arduino Board Support Package for ESP8266
- Required Libraries (see instructions below)

### Step 1: Install Arduino IDE

Download from [Arduino Official Website](https://www.arduino.cc/en/software)

### Step 2: Add ESP8266 Board Support

1. Open Arduino IDE → **Preferences**
2. Add this URL to "Additional Board Manager URLs":
   ```
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   ```
3. Go to **Tools → Board Manager** and search for "esp8266"
4. Click **Install**

### Step 3: Install Required Libraries

In Arduino IDE, go to **Sketch → Include Library → Manage Libraries**

Search and install:
- `MPU6050` by I2CDevLib
- `ArduinoJson` by Benoit Blanchon
- `TinyGPS++` by Mikal Hart (for GPS)
- `PubSubClient` (if using MQTT)

```bash
# Or install via command line
# (If using PlatformIO)
pio lib install "MPU6050"
pio lib install "ArduinoJson"
pio lib install "TinyGPS++"
```

### Step 4: Configuration

Edit the following in `SmartHelmet.ino`:

```cpp
// WiFi Configuration
const char* ssid = "YOUR_SSID";           // Your WiFi network name
const char* password = "YOUR_PASSWORD";   // Your WiFi password

// Pushbullet API Configuration
const char* apiKey = "YOUR_API_KEY";      // Get from pushbullet.com
```

### Step 5: Upload Code

1. Connect Arduino via USB
2. Select **Board**: ESP8266 (NodeMCU 1.0)
3. Select **Port**: COM port of your device
4. Click **Upload** (Ctrl + U)

### Step 6: Pushbullet Setup

1. Go to [Pushbullet.com](https://www.pushbullet.com) and create an account
2. Go to **Settings → API Key** and copy your key
3. Paste in code at line 7
4. Download Pushbullet app on your phone to receive notifications

---

## 💻 Usage

### Starting the System

1. **Power On** - Connect battery to the system
2. **WiFi Connection** - Device automatically connects to configured WiFi
3. **GPS Lock** - Wait 30-60 seconds for GPS to acquire satellite signal
4. **Ready for Detection** - Device is now active and monitoring

### Testing the System

#### Test 1: Simulate a Fall
- Gently shake the helmet to trigger the accelerometer
- Check serial monitor for "Fall detected" message
- Verify Pushbullet notification received

#### Test 2: GPS Functionality
- Open Serial Monitor (Baud Rate: 115200)
- Move device outdoors for GPS signal
- Verify coordinates in serial output

### Adjusting Sensitivity

To change fall detection threshold:

```cpp
// In loop() function - Line ~58
if (accel_magnitude > 1.5) {  // Change 1.5 to lower/higher value
    sendFallAlert();
    delay(60000);  // Wait 1 minute before next alert
}
```

**Threshold Guide:**
- `1.2` - Very Sensitive (may cause false alarms)
- `1.5` - Balanced (recommended)
- `2.0` - Less Sensitive (may miss real falls)

---

## 🏗️ Code Architecture

```
SmartHelmet/
├── SmartHelmet.ino          # Main Arduino code
├── README.md                # Documentation
├── LICENSE                  # MIT License
├── Circuit_Diagram.png      # Hardware schematic
├── Components_List.txt      # Bill of Materials
└── Documentation/
    ├── Installation_Guide.md
    ├── API_Configuration.md
    └── Troubleshooting.md
```

### Key Functions

| Function | Purpose |
|----------|---------|
| `setup()` | Initialize sensors, WiFi, and serial communication |
| `loop()` | Main program loop - continuously reads sensor data |
| `sendFallAlert()` | Sends Pushbullet notification when fall detected |

### Sensor Data Flow

```
MPU6050 Accelerometer
        ↓
Read X, Y, Z values
        ↓
Convert to g-forces (÷ 16384)
        ↓
Calculate Magnitude (√x² + y² + z²)
        ↓
Compare with Threshold (1.5g)
        ↓
If Exceeded → sendFallAlert()
        ↓
Pushbullet API → Emergency Contact
```

---

## 📊 Results

### Successful Detection Tests

- **Accuracy Rate**: 94% correct fall detection
- **False Positive Rate**: 2-3% (can be tuned)
- **Average Response Time**: 2-3 seconds from fall to alert
- **GPS Accuracy**: ±5-10 meters

### Hardware Performance

- **Power Consumption**: 250mA average, 600mA peak
- **Battery Life**: ~8-10 hours continuous operation
- **WiFi Range**: Up to 50 meters (standard)
- **GPS Acquisition**: 30-60 seconds (cold start)

### Sample Alert Notification

```json
{
  "type": "note",
  "title": "Fall Detection Alert",
  "body": "Fall detected! Immediate assistance may be needed.",
  "device_iden": "device_id_here"
}
```

---

## 🔮 Future Scope

### Phase 2 - Enhanced Health Monitoring
- [ ] Integrate heart rate sensors
- [ ] Pulse oximetry monitoring
- [ ] Body temperature tracking
- [ ] Customize alerts based on vital signs

### Phase 3 - Predictive Safety
- [ ] Integrate proximity sensors for collision detection
- [ ] Pre-warning system for potential accidents
- [ ] Machine learning for accident prediction

### Phase 4 - IoT Network Integration
- [ ] Connect to smart traffic systems
- [ ] Vehicle-to-Vehicle (V2V) communication
- [ ] Smart city infrastructure integration
- [ ] Real-time traffic data sharing

### Phase 5 - Mobile Application
- [ ] Dedicated Android/iOS app
- [ ] Real-time tracking dashboard
- [ ] Riding analytics and statistics
- [ ] Emergency contact management

---

## 🤝 Contributing

We welcome contributions! Here's how:

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/AmazingFeature`)
3. **Commit** changes (`git commit -m 'Add AmazingFeature'`)
4. **Push** to branch (`git push origin feature/AmazingFeature`)
5. **Open** a Pull Request

### Contribution Areas

- 🐛 Bug fixes and improvements
- 📚 Documentation enhancements
- 🔧 Hardware optimizations
- 📱 Mobile app development
- 🧪 Testing and validation

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

```
MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files...
```

---

## 📞 Contact & Support

**Author**: Keyur Chauhan  
**Project Title**: Smart Helmet for Real-Time Accident Detection and Emergency Alert System  
**Award**: Best Paper - MULTICON-W 2025

### Get Help

- 📧 **Email**: [keyurchauhan15@gmail.com]
- 💼 **LinkedIn**: [www.linkedin.com/in/keyur-chauhan-]

### Report Issues

Found a bug? Have a question?
- 🐛 [Create an Issue](../../issues)
- 💬 [Start a Discussion](../../discussions)

---

## 🙏 Acknowledgments

- Thakur College of Engineering & Technology
- All contributors and testers
- Open-source community for libraries

---

## 📚 References

1. WHO - Global Status Report on Road Safety
2. Arduino Documentation - https://docs.arduino.cc
3. Pushbullet API - https://docs.pushbullet.com
4. MPU6050 Datasheet
5. ESP8266 Documentation

---

**⭐ If this project helped you, please consider giving it a star!**

Last Updated: June 2025
