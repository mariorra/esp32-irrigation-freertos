# ✅ TODO – Irrigation-FreeRTOS System

---

## 🚧 Current Feature Branch: `feature/ui-tft`

### 📺 UI for 2.4" TFT Display

- [x] Wire ILI9341 pins (CS, DC, RST) to ESP32 and test init  
- [x] Implement `TFTDisplay.begin()` and `showPage()`  
- [x] Integrate `display.showPage()` in a dedicated FreeRTOS task  
- [x] Cycle pages (plants 1–4 / 5–8) via timeout  
- [ ] Measure render time & ensure FreeRTOS responsiveness  

---

## 🧩 Next Feature Branch: `feature/plantcontroller-modular`

### 🧱 Modular Refactor – `PlantController`

- [ ] Create `PlantController.h/.cpp` to encapsulate irrigation logic  
- [ ] Move logic from `irrigationTask()` inside the class  
- [ ] Make a static `startTask(PlantConfig*)` method to launch per-plant task  
- [ ] Refactor `main.cpp` to use `PlantController` class  
- [ ] Ensure memory is properly freed and tasks are stable  

---

## 💡 Future Ideas

### 🌐 Connectivity

- [ ] Integrate Wi-Fi and send data via MQTT  
- [ ] Enable OTA updates  
- [ ] Add local manual override (button or serial input)  

---

