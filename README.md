cat > README.md << 'EOF'
# Irrigation System with ESP32, FreeRTOS and ADS1115

## 📦 Description

This project implements an automated irrigation system using an ESP32, two ADS1115 analog-to-digital converters, capacitive soil moisture sensors, and relay-controlled water pumps.

It uses FreeRTOS to assign one task per plant. Each task reads its sensor and controls the corresponding pump independently.

## ⚙ Features

- Support for **8 individual plants**  
- Two ADS1115 over I2C (`0x48`, `0x49`)  
- FreeRTOS-based parallel task architecture  
- **Mutex-protected I2C access** to avoid conflicts  
- Modular `PlantConfig` struct passed to each task  

## 🔧 Wiring (for ADS1)
- SDA: GPIO 21
- SCL: GPIO 22
- ADDR: GND → 0x48

EOF


# 🌿 ESP32 Irrigation System – 8 Plants with ADS1115 & FreeRTOS

## 📦 Overview

This project implements an automated irrigation system using an ESP32, two ADS1115 analog-to-digital converters, capacitive soil moisture sensors, and relay-controlled water pumps.

It uses FreeRTOS to assign one task per plant. Each task reads its sensor and controls the corresponding pump independently.

## 🧠 Key Features

- Support for **8 individual plants**  
- Two ADS1115 over I2C (`0x48`, `0x49`)  
- FreeRTOS-based parallel task architecture  
- **Mutex-protected I2C access** to avoid conflicts  
- Modular `PlantConfig` struct passed to each task  

## 📐 Architecture

main
├─ feature/docs-base
├─ dev
│ ├─ feature/freertos-base
│ ├─ feature/ads1115-4plants
│ └─ feature/ads1115-8plants-mutex
└─ docs/update-ads8-mutex


## 🔌 Wiring Overview

### ADS1115 #1 (0x48)
- SDA → GPIO 21  
- SCL → GPIO 22  
- Channels 0–3 → Plants 1–4  

### ADS1115 #2 (0x49)
- SDA → GPIO 21  
- SCL → GPIO 22  
- Channels 0–3 → Plants 5–8  

### Relays
- Plant 1 → GPIO 2
- Plant 2 → GPIO 4
- Plant 3 → GPIO 5
- Plant 4 → GPIO 15
- Plant 5 → GPIO 16
- Plant 6 → GPIO 17
- Plant 7 → GPIO 18
- Plant 8 → GPIO 19


## 🔐 Concurrency and Mutex Usage

Access to the shared I2C bus is **protected with a FreeRTOS mutex**, ensuring safe concurrent readings from the ADS1115 devices.

Each task:

1. Takes the mutex before I2C read  
2. Reads from its assigned ADS1115 + channel  
3. Releases the mutex  
4. Controls its relay based on moisture  

## 📁 Project Structure

- `main.cpp` – Initialization and FreeRTOS task creation  
- `PlantConfig` – Struct containing per-plant configuration  
- `irrigationTask()` – Logic for reading, mutex use, and pump control  

## 📋 Next Steps

- Add error logging, retries or fallback logic  
- Expose moisture levels via serial/MQTT  
- Modularize task creation into `PlantController.cpp`  
