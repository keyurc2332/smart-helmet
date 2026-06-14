# ⚡ Smart Helmet - Quick Start Guide

**Get your Smart Helmet running in 5 minutes!**

---

## 🚀 Quick Setup (5 Minutes)

### 1️⃣ Get API Key (1 min)

```
1. Go to https://www.pushbullet.com
2. Sign up (or login)
3. Settings → Account → API Key
4. Copy the key (starts with "o.")
```

### 2️⃣ Update Code (1 min)

Edit `SmartHelmet.ino` lines 6-8:

```cpp
const char* ssid = "YOUR_WIFI";           // WiFi name
const char* password = "YOUR_PASSWORD";   // WiFi password
const char* apiKey = "o.YOUR_API_KEY";    // Pushbullet key
```

### 3️⃣ Upload to Arduino (1 min)

```
Tools → Board → Select your board
Tools → Port → Select COM port
Click Upload (Ctrl + U)
```

### 4️⃣ Install Phone App (1 min)

- Android: Google Play Store → Search "Pushbullet"
- iPhone: App Store → Search "Pushbullet"
- Login with your Pushbullet account

### 5️⃣ Test It! (1 min)

```
1. Open Serial Monitor (Ctrl + Shift + M)
2. Shake the device hard
3. Check your phone for alert!
```

---

## ✅ Verify Everything Works

| Check | What to Do |
|-------|-----------|
| **WiFi** | Serial should show "Connected to WiFi" |
| **API** | Serial should show "Push notification sent!" |
| **Phone** | Should receive notification within 5 seconds |
| **GPS** | Wait 1 minute outdoors, should show coordinates |

---

## 🎯 Adjust Sensitivity (Optional)

If getting false alarms or missing real falls:

```cpp
// Line 58 in SmartHelmet.ino
if (accel_magnitude > 1.5) {  // Change this number

// Recommendations:
// 1.2 = Very sensitive (experimental)
// 1.5 = Balanced (recommended) ← START HERE
// 2.0 = Less sensitive (stable)
// 2.5 = Very stable (may miss falls)
```

---

## 🔋 Installation on Helmet

1. **Waterproof the circuit**
   ```
   Option 1: Silicon sealant around components
   Option 2: Waterproof case/box
   Option 3: Clear epoxy coating
   ```

2. **Mount inside helmet**
   ```
   - Inside back of helmet
   - Or top of helmet
   - Use adhesive or brackets
   - Keep antenna exposed (if GPS/GSM)
   ```

3. **Secure battery**
   ```
   - Use velcro strips
   - Secure with zip ties
   - Keep away from heat sources
   ```

4. **Test fit**
   ```
   - Wear helmet for 10 minutes
   - Check for discomfort
   - Adjust if needed
   ```

---

## 🐛 Common Issues & Quick Fixes

| Problem | Fix |
|---------|-----|
| **No WiFi** | Check WiFi name/password in code |
| **No notification** | Verify API key is correct |
| **Phone not getting alert** | Check notification settings in phone |
| **GPS not working** | Wait 2 min outdoors, check antenna |
| **False alarms** | Increase threshold to 2.0 |
| **Missing real falls** | Decrease threshold to 1.2 |

---

## 📱 What You'll See on Phone

When a fall is detected:

```
🔔 Fall Detection Alert
   Fall detected! 
   Immediate assistance may be needed.
   
   [View]  [Clear]
```

---

## ✨ Features Unlocked

After setup:
- ✅ Automatic accident detection
- ✅ Instant alerts to phone
- ✅ GPS location sharing
- ✅ Real-time notifications
- ✅ Emergency contact alerts

---

## 📞 Need Help?

**Common Questions:**

**Q: How long does battery last?**  
A: 8-10 hours with continuous monitoring

**Q: Is it waterproof?**  
A: Not by default. Add silicone or epoxy coating.

**Q: Can I add multiple emergency contacts?**  
A: Yes! See advanced section in README.md

**Q: What if WiFi is not available?**  
A: SMS alerts via GSM module (optional)

---

## 🎓 Next Steps

1. **Test thoroughly**
   - Simulate falls in safe environment
   - Verify phone gets alerts
   - Check GPS accuracy

2. **Inform contacts**
   - Tell emergency contacts about system
   - Explain how alerts work
   - Share your Pushbullet details

3. **Wear confidently**
   - Helmet is now smart & safe!
   - Monitor battery regularly
   - Enjoy the peace of mind

---

## 📚 Full Documentation

For detailed info, see:
- **README.md** - Full project overview
- **INSTALLATION_GUIDE.md** - Detailed setup
- **API_CONFIGURATION.md** - Pushbullet setup
- **BOM_COMPONENTS.md** - Component details

---

**⏱️ Total Time: 5-10 minutes**  
**Difficulty: Easy**  
**Result: Working Smart Helmet! 🎉**

---

**Happy Riding! Stay Safe! 🏍️**
