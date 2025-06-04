# 📄 Changelog

All notable changes to this project will be documented in this file.

---


### Added – feature/plantcontroller-modular

- New `PlantController` module to encapsulate irrigation task logic

### Changed
- Task creation now handled via modular class


## [Unreleased] – feature/ads1115-8plants-mutex

### Added
- Support for 2 ADS1115 chips (addresses 0x48 and 0x49)
- `PlantConfig` extended to store ADC and channel
- FreeRTOS semaphore to protect I2C access (mutex)
- Modular scaling to support 8 plants
- **UI Module**: `TFTDisplay` class for 2.4" ILI9341 TFT
- FreeRTOS `displayTask` to cycle between plant pages
- PlatformIO dependencies added for Adafruit ILI9341 & GFX libraries
- Documentation updates in README, CHANGELOG, TODO for UI integration

### Changed
- `main.cpp`: integrated `displayTask`, structured init sequence
- Improved README with badges, wiring tables, and usage instructions
- Updated TODO.md with UI-specific tasks and roadmap

---

## [feature/ads1115-4plants]
- Initial system with one ADS1115 (0x48)
- Modular `PlantConfig` with pointer to ADS
- 4 tasks, one per plant
- Dynamic memory and task assignment using FreeRTOS
