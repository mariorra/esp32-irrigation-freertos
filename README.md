cat > README.md << 'EOF'
# Irrigation System with ESP32, FreeRTOS and ADS1115

## 📦 Description

This system controls up to 8 plants using capacitive moisture sensors, relay-controlled pumps, and two ADS1115 analog-to-digital converters over I2C.

## ⚙ Features

- FreeRTOS task per plant
- Scalable via `PlantConfig` struct
- I2C access protected with a mutex
- Modular and maintainable architecture

## 🔧 Wiring (for ADS1)
- SDA: GPIO 21
- SCL: GPIO 22
- ADDR: GND → 0x48

EOF
