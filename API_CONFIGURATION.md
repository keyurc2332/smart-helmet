# 🔧 Pushbullet API Configuration Guide

**Smart Helmet Project - Emergency Alert System Setup**

---

## 📱 What is Pushbullet?

Pushbullet is a cloud-based service that allows you to:
- Send instant notifications across devices (phones, tablets, computers)
- Push real-time alerts and messages
- Integrate with IoT devices and applications
- Create custom notification channels

For this Smart Helmet project, we use Pushbullet to send **fall detection alerts** to emergency contacts.

---

## ✅ Step-by-Step Setup Guide

### Step 1: Create a Pushbullet Account

1. Visit **[Pushbullet.com](https://www.pushbullet.com)**
2. Click **"Sign Up"** in the top-right corner
3. Enter your email and create a password
4. Verify your email by clicking the confirmation link
5. ✅ Account created!

---

### Step 2: Get Your API Key

1. Log in to Pushbullet
2. Go to **Settings** → **Account** → **API Key**
3. You'll see a long string starting with `o.`
4. **Click the copy button** to copy your API key
5. This is your `apiKey` for the Arduino code

**Example API Key Format:**
```
o.K263B7Sma88rg4j6PuKmGoNqup0YxkAw
```

---

### Step 3: Install Pushbullet App on Your Phone

#### For Android:
1. Open **Google Play Store**
2. Search for **"Pushbullet"**
3. Download and install the official Pushbullet app
4. Log in with your Pushbullet account

#### For iPhone:
1. Open **App Store**
2. Search for **"Pushbullet"**
3. Download and install
4. Log in with your Pushbullet account

---

### Step 4: Configure Arduino Code

Open `SmartHelmet.ino` and update these lines:

```cpp
// Line 6-7: WiFi Configuration
const char* ssid = "YOUR_WiFi_SSID";           // Change to your WiFi name
const char* password = "YOUR_WiFi_PASSWORD";   // Change to your WiFi password

// Line 8: Pushbullet API Key
const char* apiKey = "o.K263B7Sma88rg4j6PuKmGoNqup0YxkAw";  // Replace with your API key
```

**Example:**
```cpp
const char* ssid = "AndroidAPA9D5";
const char* password = "labdhi23";
const char* apiKey = "o.YOUR_ACTUAL_API_KEY_HERE";
```

---

### Step 5: Upload Code to Arduino

1. Connect Arduino via USB
2. Open Arduino IDE
3. Select correct board: **Tools → Board → ESP8266**
4. Select port: **Tools → Port → COM#**
5. Click **Upload** (Ctrl + U)
6. Wait for upload to complete
7. Open **Serial Monitor** (Ctrl + Shift + M)

---

### Step 6: Test the System

#### Method 1: Simulate a Fall
```
1. Open Serial Monitor (115200 baud)
2. Shake the helmet/device vigorously
3. Look for "Fall detected" in serial output
4. Check your phone for Pushbullet notification
```

#### Method 2: Trigger Manually (Code Modification)
Uncomment this in `SmartHelmet.ino` for testing:
```cpp
// In loop() function, replace the threshold check with:
if (true) {  // Always send alert for testing
    Serial.println("Test: Fall detected");
    sendFallAlert();
    delay(60000);
}
```

---

## 🔔 Understanding Alert Notifications

### Alert Structure

When a fall is detected, the system sends:

```json
{
  "type": "note",
  "title": "Fall Detection Alert",
  "body": "Fall detected! Immediate assistance may be needed.",
  "device_iden": "your_device_id"
}
```

### What You'll See on Your Phone

```
╔══════════════════════════════════╗
║  Pushbullet                      ║
╠══════════════════════════════════╣
║ 🔴 Fall Detection Alert          ║
║ Fall detected! Immediate         ║
║ assistance may be needed.        ║
║                                  ║
║ [Dismiss]  [More Info]           ║
╚══════════════════════════════════╝
```

---

## 🌐 API Endpoint Reference

### Pushbullet API Endpoints

**Base URL:**
```
https://api.pushbullet.com/v1
```

**Send Note Endpoint:**
```
POST https://api.pushbullet.com/v2/pushes
```

### Request Headers Required

```
POST /v2/pushes HTTP/1.1
Host: api.pushbullet.com
Content-Type: application/json
Content-Length: [length of body]
Authorization: Bearer [YOUR_API_KEY]
```

### Response Example

**Success (201 Created):**
```json
{
  "iden": "ujpah72o0",
  "guid": "12345678",
  "type": "note",
  "title": "Fall Detection Alert",
  "body": "Fall detected! Immediate assistance may be needed.",
  "created": 1234567890,
  "modified": 1234567890,
  "dismissed": false,
  "direction": "self",
  "sender_iden": "ujpah72o0",
  "sender_email": "your.email@gmail.com",
  "sender_email_normalized": "youremail@gmail.com",
  "sender_name": "Arduino Device",
  "receiver_iden": "ujpah72o0",
  "receiver_email": "your.email@gmail.com",
  "receiver_email_normalized": "youremail@gmail.com"
}
```

**Error (401 Unauthorized):**
```json
{
  "error": {
    "code": 401,
    "message": "Invalid access token"
  }
}
```

---

## 🔐 Security Best Practices

⚠️ **IMPORTANT**: Protect your API key!

### Do's ✅
- [ ] Store API key in secure location
- [ ] Use HTTPS (our code does)
- [ ] Rotate API key periodically
- [ ] Never share key in public repositories
- [ ] Use `.gitignore` to exclude secret files

### Don'ts ❌
- [ ] Don't commit API key to GitHub
- [ ] Don't share in forums or chat
- [ ] Don't use same key across multiple projects
- [ ] Don't hardcode credentials in production

### Hide Your API Key

Option 1: Use `.env` file
```
# .env file (add to .gitignore)
PUSHBULLET_API_KEY=o.your_key_here
WIFI_SSID=your_ssid
WIFI_PASSWORD=your_password
```

Option 2: Store in EEPROM
```cpp
// Store API key in Arduino's permanent memory
EEPROM.begin(512);
// Write key
// Read key
```

---

## 🐛 Troubleshooting

### Problem: Notifications Not Received

**Symptom**: Serial shows "Push notification sent!" but phone doesn't get alert

**Solutions**:
1. ✅ Verify Pushbullet app is installed
2. ✅ Check you're logged in to Pushbullet app
3. ✅ Ensure phone WiFi is ON and connected
4. ✅ Check notification permissions in phone settings
5. ✅ Look in Pushbullet app's "Archive" section
6. ✅ Verify API key is correct (copy-paste, no spaces)

---

### Problem: "WiFi not connected" Error

**Symptom**: Serial shows "WiFi not connected" message

**Solutions**:
```cpp
// Check these in code:
1. WiFi SSID is correct (case-sensitive)
2. WiFi password is correct
3. WiFi is 2.4GHz (not 5GHz)
4. ESP8266 antenna is connected
5. Try hiding/unhiding WiFi SSID
6. Restart WiFi router
```

Test code:
```cpp
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED && timeout < 20) {
    delay(500);
    Serial.print(".");
    timeout++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi Connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ WiFi Failed!");
  }
}
```

---

### Problem: "Failed to connect to api.pushbullet.com"

**Symptom**: WiFi connected but Pushbullet API fails

**Solutions**:
1. Check internet connectivity
2. Verify firewall isn't blocking port 443
3. Confirm API endpoint (https://api.pushbullet.com)
4. Try different time to rule out API downtime
5. Check Pushbullet status: [status.pushbullet.com](https://status.pushbullet.com)

---

### Problem: "Invalid access token" Error

**Symptom**: API returns 401 Unauthorized

**Solutions**:
1. Copy API key again from Pushbullet settings
2. Check for spaces or extra characters
3. API key might have been revoked - regenerate it
4. Ensure correct authorization format:
   ```cpp
   "Authorization: Bearer " + String(apiKey)
   ```

---

## 📊 Monitoring Your Alerts

### View Alert History

1. Open Pushbullet app
2. Go to **"Inbox"** tab
3. Scroll to see all received alerts
4. Click alert for details and timestamp

### Create Custom Channels (Optional)

1. In Pushbullet app, tap **"+"** button
2. Select **"Create channel"**
3. Name it (e.g., "Smart Helmet Alerts")
4. Configure privacy settings
5. Share with others who need alerts

---

## 🚀 Advanced: Send to Multiple Contacts

To alert multiple emergency contacts:

```cpp
void sendFallAlert() {
  if (WiFi.status() == WL_CONNECTED) {
    // Array of API keys for multiple users
    const char* emergencyContacts[] = {
      "o.key_contact_1_here",
      "o.key_contact_2_here",
      "o.key_contact_3_here"
    };
    
    // Send to each contact
    for (int i = 0; i < 3; i++) {
      sendAlertToContact(emergencyContacts[i]);
      delay(1000);  // Space out requests
    }
  }
}

void sendAlertToContact(const char* contactKey) {
  // Similar code as sendFallAlert but uses contactKey instead of apiKey
  // ... [implementation]
}
```

---

## 💡 Pro Tips

1. **Test Regularly** - Simulate falls weekly to ensure system works
2. **Backup Power** - Keep your phone charged for receiving alerts
3. **Update Contacts** - Maintain current emergency contact information
4. **Review Alerts** - Check archive to verify system is working
5. **Share Project** - Let emergency contacts know to expect alerts
6. **Document Everything** - Keep records of tests and alerts
7. **Low Battery Alert** - Consider adding battery level to notifications

---

## 📚 Additional Resources

- **Pushbullet Official Docs**: https://docs.pushbullet.com
- **Arduino WiFi Client**: https://reference.arduino.cc/reference/en/libraries/wifi/wificlientsecure/
- **JSON in Arduino**: https://arduinojson.org
- **ESP8266 WiFi Guide**: https://github.com/esp8266/Arduino

---

## 🔄 Resetting Your API Key

If you suspect your API key is compromised:

1. Log in to Pushbullet
2. Go to **Settings → Account → API Key**
3. Click **"Revoke"** next to current key
4. Click **"Create Access Token"**
5. Copy the new API key
6. Update Arduino code with new key
7. Re-upload to device

---

## ✨ Next Steps

After successful setup:

1. ✅ Test system thoroughly in different conditions
2. ✅ Document your API key securely
3. ✅ Inform emergency contacts about the system
4. ✅ Consider adding SMS backup (SIM800 module)
5. ✅ Plan for data logging and analytics
6. ✅ Explore Pushbullet advanced features

---

## 📞 Support

- **Pushbullet Help**: https://help.pushbullet.com
- **Arduino Forums**: https://forum.arduino.cc
- **GitHub Issues**: Report problems on project repository
- **Community**: Join Arduino IoT communities

---

**Last Updated**: June 2025  
**Compatible With**: Arduino IDE 1.8+, Pushbullet API v2  
**Tested On**: ESP8266, Arduino Nano + WiFi Shield
