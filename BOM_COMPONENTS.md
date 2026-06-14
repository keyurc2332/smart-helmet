# Smart Helmet - Bill of Materials (BOM)

**Project**: Smart Helmet for Accident Detection and Emergency Alert System  
**Version**: 1.0  
**Last Updated**: June 2025

---

## 📦 Complete Components List

### Core Microcontroller

| Part | Model | Qty | Purpose | Approx. Cost |
|------|-------|-----|---------|--------------|
| Microcontroller | Arduino Nano v3.0 | 1 | Central processing unit | ₹600-800 |
| WiFi Module | ESP8266 (NodeMCU) | 1 | WiFi connectivity | ₹400-500 |

### Sensors

| Part | Model | Qty | Specifications | Purpose | Cost |
|------|-------|-----|---|---------|------|
| Motion Sensor | MPU6050 6-DOF | 1 | Accelerometer + Gyroscope, I2C | Fall/Impact detection | ₹400-500 |
| GPS Module | NEO-6M (u-blox) | 1 | Accuracy: ±5-10m, 3.3-5V | Location tracking | ₹800-1000 |
| GSM Module | SIM800L | 1 | Quad-band, UART interface | SMS alerts (backup) | ₹500-600 |

### Power Management

| Part | Model | Qty | Specifications | Purpose | Cost |
|------|-------|-----|---|---------|------|
| Li-Po Battery | 3.7V, 2000mAh | 1 | Rechargeable lithium | Power source | ₹400-500 |
| Power Module | TP4056 + 5V Boost | 1 | Charging + voltage regulation | Battery management | ₹200-300 |
| USB Cable | Micro USB | 1 | For charging & programming | Charging | ₹100-150 |

### Connectivity & Shields

| Part | Model | Qty | Purpose | Cost |
|------|-------|-----|---------|------|
| Logic Level Converter | 3.3V↔5V | 1 | Interface different voltage levels | ₹100-150 |
| USB FTDI Programmer | FT232RL | 1 | Serial communication (optional) | ₹200-300 |

### Passive Components

| Part | Specification | Qty | Purpose | Cost |
|------|---|-----|---------|------|
| Resistors | 10kΩ, 1kΩ, 470Ω | 20 | Pull-ups, current limiting | ₹50-100 |
| Capacitors | 10µF, 100nF | 15 | Filtering, decoupling | ₹100-150 |
| LED Indicator | Red, Green | 2 | Status indication | ₹50-100 |
| Push Button | 6mm | 2 | Reset, manual controls | ₹30-50 |
| Buzzer | 5V Active | 1 | Local alert sound | ₹50-100 |

### Connectivity & Interface

| Part | Specification | Qty | Purpose | Cost |
|------|---|-----|---------|------|
| Jumper Wires | M-M, M-F | 50 | Circuit connections | ₹50-100 |
| PCB Board | 10x10 cm Perforated | 1 | Component mounting | ₹100-150 |
| Header Pins | 40-pin strips | 2 | Module connections | ₹50-100 |
| Soldering Iron | 25W | 1 | Soldering components | ₹300-500 |
| Solder | Lead-free, 60-40 | 1 | Solder material | ₹100-150 |

### Mounting & Housing

| Part | Specification | Qty | Purpose | Cost |
|------|---|-----|---------|------|
| Helmet (Test/Demo) | Standard bike helmet | 1 | Integration platform | ₹500-2000 |
| 3D Printed Case | Custom enclosure | 1 | Component protection | ₹300-500 |
| Mounting Bracket | Adjustable aluminum | 1 | Sensor positioning | ₹200-300 |
| Velcro Strips | Heavy-duty | 1 | Non-permanent mounting | ₹50-100 |
| Cable Ties | Nylon, 10cm | 20 | Wire management | ₹30-50 |

### Miscellaneous

| Part | Specification | Qty | Purpose | Cost |
|------|---|-----|---------|------|
| Antenna (GPS) | SMA connector | 1 | Improved GPS signal | ₹100-200 |
| Antenna (GSM) | Built-in | 1 | Cellular connectivity | Included |
| Heat Shrink Tubing | Multi-size | 10 | Wire insulation | ₹50-100 |
| Breadboard | 830 points (optional) | 1 | Prototyping | ₹100-200 |

---

## 💰 Cost Summary

### Basic Kit (Essential Components)
| Category | Cost |
|----------|------|
| Microcontroller & WiFi | ₹1000-1300 |
| Sensors (MPU6050, GPS, GSM) | ₹1700-2100 |
| Power Management & Battery | ₹600-800 |
| Passive Components & Wiring | ₹400-600 |
| **Total (Approx.)** | **₹3700-4800** |

### Complete Kit (With Housing & Extras)
| Category | Cost |
|----------|------|
| Basic Kit | ₹3700-4800 |
| Housing & Mounting | ₹500-800 |
| Tools (Soldering Iron, Solder) | ₹400-650 |
| **Total (Approx.)** | **₹4600-6250** |

---

## 🛒 Where to Buy

### India
- **Arduino Components**: 
  - Amazon.in
  - GeeksforGeeks Electronics
  - Robocraze.com
  - ElectronicsComp.com

- **Sensors & Modules**:
  - DinoDirect.in
  - BangGood.com
  - AliExpress.com
  - LocalArduino dealers

### International
- Arduino.cc (Official)
- Adafruit.com
- SparkFun.com
- Amazon.com
- eBay.com

---

## 📋 Assembly Checklist

- [ ] Arduino Nano
- [ ] ESP8266 WiFi Module
- [ ] MPU6050 Sensor
- [ ] NEO-6M GPS Module
- [ ] SIM800L GSM Module
- [ ] 3.7V Li-Po Battery
- [ ] TP4056 Charging Module
- [ ] Power Boost Module (5V)
- [ ] Logic Level Converter (3.3V ↔ 5V)
- [ ] Resistors (10kΩ, 1kΩ, 470Ω)
- [ ] Capacitors (10µF, 100nF)
- [ ] LEDs (Red, Green)
- [ ] Push Buttons (2)
- [ ] Buzzer (5V)
- [ ] Jumper Wires (Male-Male, Male-Female)
- [ ] Perforated PCB Board
- [ ] Header Pins (40-pin)
- [ ] SIM Card (for GSM Module)
- [ ] Micro USB Cable
- [ ] Soldering Iron + Solder
- [ ] Helmet for Testing
- [ ] 3D Printed Housing (Optional)
- [ ] Mounting Brackets & Velcro

---

## 🔌 Pin Configuration Summary

### Arduino Nano Connections

```
Arduino Nano Pin Map
====================

I2C Bus (for MPU6050):
  - Pin A4 (SDA) → MPU6050 SDA
  - Pin A5 (SCL) → MPU6050 SCL
  - GND → MPU6050 GND
  - 5V → MPU6050 VCC

UART Serial (for ESP8266):
  - Pin 0 (RX) → ESP8266 TX
  - Pin 1 (TX) → ESP8266 RX
  - GND → ESP8266 GND
  - 3.3V → ESP8266 VCC (via Level Converter)

Software Serial (for GPS/GSM):
  - Pin 2 (RX) → GPS/GSM TX
  - Pin 3 (TX) → GPS/GSM RX
  - GND → GPS/GSM GND
  - 5V → GPS/GSM VCC

Indicators:
  - Pin 13 (LED) → Built-in LED
  - Pin 12 (Buzzer) → 5V Buzzer
  - Pin 11 (Button) → Reset Button

Power:
  - 5V → VCC (from Power Module)
  - GND → GND (Common)
```

---

## ⚙️ Soldering Tips

1. **Temperature**: 350-400°C (660-750°F)
2. **Duration**: 2-3 seconds per joint
3. **Quality Check**: Shiny, smooth solder joint (cone shape)
4. **Avoid**:
   - Cold solder joints (dull, grainy appearance)
   - Excessive heat (component damage)
   - Too much solder (shorts)

---

## 🔧 Troubleshooting Common Issues

### Component Won't Power On
- Check battery connection polarity
- Test with multimeter (should show 3.7V)
- Verify power module output

### WiFi Module Not Connecting
- Ensure correct baud rate (115200)
- Check WiFi credentials in code
- Test antenna connection

### GPS Not Getting Signal
- Ensure antenna is pointing upward
- Move outdoors (away from buildings)
- Wait 1-2 minutes for cold start
- Try with external antenna

### Sensor Not Responding
- Check I2C pullup resistors (10kΩ)
- Verify device address (0x68 for MPU6050)
- Test with I2C scanner code

---

## 📚 Reference Datasheets

- [Arduino Nano Pinout](https://store.arduino.cc/arduino-nano-every)
- [ESP8266 Documentation](https://github.com/esp8266/Arduino)
- [MPU6050 Datasheet](https://invensense.tdk.com/products/motion-tracking/6-axis/mpu-6050/)
- [NEO-6M GPS Datasheet](https://www.u-blox.com/sites/default/files/NEO-6_DataSheet_%28GPS.G6-HW-09005%29.pdf)
- [SIM800L Manual](https://www.elecrow.com/download/SIM800L_Hardware%20Design_V1.08.pdf)

---

## 💡 Money-Saving Tips

1. **Buy in Bulk**: Resistors and capacitors are cheaper in bulk
2. **Use Alternate Modules**: Consider ESP32 instead of Arduino+ESP8266 combo
3. **DIY Housing**: 3D print your own case instead of buying
4. **Used Components**: Check local electronics shops for used/refurbished parts
5. **Online Shopping**: Compare prices across multiple platforms
6. **Student Discounts**: Arduino and SparkFun offer student discounts

---

**Last Updated**: June 2025  
**Maintainer**: Keyur Chauhan  
**Version**: 1.0
