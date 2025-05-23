cat > CHANGELOG.md << 'EOF'
# 📄 Changelog

All notable changes to this project will be documented in this file.

---

## [Unreleased] – feature/ads1115-8plants-mutex

### Added
- Support for 2 ADS1115 chips (addresses 0x48 and 0x49)
- `PlantConfig` extended to store ADC and channel
- FreeRTOS semaphore to protect I2C access (mutex)
- Modular scaling to support 8 plants

### Changed
- Task logic adapted to use structured config
- Main loop now initializes two ADCs and dispatches 8 tasks

---

## [feature/ads1115-4plants]
- Initial system with one ADS1115 (0x48)
- Modular `PlantConfig` with pointer to ADS
- 4 tasks, one per plant
- Dynamic memory and task assignment using FreeRTOS
EOF
