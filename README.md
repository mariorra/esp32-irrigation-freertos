# 🌿 ESP32 Irrigation System – 8 Plants with ADS1115 & FreeRTOS

[![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32-blue)](https://platformio.org/)  [![FreeRTOS](https://img.shields.io/badge/FreeRTOS-ESP32-orange)](https://www.freertos.org/)  [![License](https://img.shields.io/badge/License-MIT-green)](LICENSE)

## 📦 Project Overview

Automate plant irrigation with precision! This project leverages an ESP32, dual ADS1115 ADCs, capacitive moisture sensors, and relay-driven pumps. Each of the 8 plants is managed by its own FreeRTOS task, ensuring independent, concurrent control.

## 🎯 Key Features

- **8 independent plant channels** with customizable thresholds
- Dual ADS1115 modules (I2C addresses `0x48` & `0x49`) for up to 8 analog inputs
- FreeRTOS-based multitasking for responsive, parallel execution
- Mutex-protected I2C bus to avoid collisions
- Modular code structure with `PlantConfig` and UI layers
- Optional TFT display UI for real-time monitoring

## 🚀 Quick Start

### Prerequisites

- ESP32 development board
- 8 capacitive moisture sensors
- 8 relay modules (active low)
- 2 × ADS1115 breakout boards
- 2.4" ILI9341 TFT (optional)
- PlatformIO + VSCode or Arduino IDE

### Installation

1. Clone the repo:
   ```bash
   git clone https://github.com/youruser/irrigation-freertos.git
   cd irrigation-freertos
   ```
2. Open in PlatformIO and install dependencies.
3. Configure `platformio.ini`:
   ```ini
   [env:esp32]
   platform = espressif32
   board = esp32dev
   framework = arduino

   lib_deps =
     adafruit/Adafruit ADS1X15@^1.1.0
     adafruit/Adafruit ILI9341@^1.5.8    ; optional TFT UI
     adafruit/Adafruit GFX Library@^1.10.10  ; optional TFT UI
   ```
4. Wire your hardware (see Wiring section).
5. Build & upload:
   ```bash
   pio run --target upload
   ```

## 🔌 Hardware Wiring

### ADS1115 Modules

| Module     | ADDR Pin | I2C Address | SDA Pin | SCL Pin |
|------------|----------|-------------|---------|---------|
| ADS1115 #1 | GND      | 0x48        | 21      | 22      |
| ADS1115 #2 | VCC      | 0x49        | 21      | 22      |

### Relay Pins

| Plant | Relay GPIO |
|-------|------------|
| 1     | 2          |
| 2     | 4          |
| 3     | 5          |
| 4     | 15         |
| 5     | 16         |
| 6     | 17         |
| 7     | 18         |
| 8     | 19         |

### TFT Display (Optional)

```
TFT_CS  → GPIO 15
TFT_DC  → GPIO 2
TFT_RST → GPIO 4
MOSI    → GPIO 23
MISO    → GPIO 19
SCK     → GPIO 18
```  

## 📁 Project Structure

```
├── src/
│   ├── main.cpp              ; entry & task startup
│   ├── PlantConfig.h/.cpp    ; core irrigation logic
│   ├── PlantController.h/.cpp; task factory and logic
│   ├── TFTDisplay.h/.cpp     ; optional UI module
│   └── ...
├── include/                  ; global headers
├── platformio.ini
├── README.md
├── CHANGELOG.md
└── TODO.md
```

## 🔐 Concurrency & Task Flow

Each plant spawns a task with its own `PlantConfig`, containing:
- ADC pointer & channel
- Relay pin
- I2C mutex
- Threshold & timing values

**Task loop:**
1. `xSemaphoreTake()` to lock I2C
2. Read ADC channel
3. `xSemaphoreGive()` to release I2C
4. Compare value to threshold → activate pump if needed
5. Delay until next check

## 🖥UI Monitoring (2.4" TFT)

Optional real-time dashboard:
- Bars showing moisture % per plant
- White-border bars, top indicator circles & percentage labels
- Page navigation for plants 1–4 and 5–8
- Handled by TFTDisplay class in its own FreeRTOS task

## 📋 Next Steps

- [x] Calibrate thresholds per plant
- [ ] Implement NVS storage for settings
- [ ] Add MQTT telemetry
- [ ] Integrate error logging & watchdog reset
- [ ] Release v0.2.0-beta

---

