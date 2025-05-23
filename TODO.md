echo "# âœ… TODO â€“ Irrigation-FreeRTOS with ADS1115

## í¿¢ Current Status (checkpoint: feature/ads1115-4plants)
- [x] Created \`PlantConfig\` struct for modular plant setup
- [x] Used dynamic memory (new/delete) for per-task configuration
- [x] Reading 4 moisture sensors via ADS1115 (address 0x48)
- [x] One FreeRTOS task per plant
- [x] Commit tracked on \`feature/ads1115-4plants\`

---

## í¿¡ Next Steps

### í´§ [HIGH] Scale to 8 plants using 2 ADS1115 chips
- [ ] Wire second ADS1115 with address 0x49
- [ ] Create a second \`Adafruit_ADS1115\` instance (\`ads2\`)
- [ ] Update \`PlantConfig\` to specify which ADC to use
- [ ] Assign each plant to \`ads1\` (channels 0â€“3) or \`ads2\` (channels 0â€“3)

### í´ [HIGH] Add FreeRTOS mutex for shared I2C bus
- [ ] Create a global \`SemaphoreHandle_t i2cMutex\`
- [ ] Wrap \`readADC_SingleEnded()\` with \`xSemaphoreTake/Give\`
- [ ] Ensure atomic access to the I2C bus across tasks

### í·¼ [MEDIUM] Optional cleanup
- [ ] Move \`relayPins[]\` and ADC init to their own module
- [ ] Replace hardcoded values (e.g., thresholds) with defines or config file

---

## í·  Future Ideas

### í·ª [LOW] Add manual override via button or serial input
- [ ] Trigger pump manually for a given plant

### í³¦ [LOW] Modularize into PlantController.{h,cpp}
- [ ] Encapsulate task logic into a C++ class
- [ ] Manage lifecycle of tasks cleanly

### â˜ï¸ [OPTIONAL] Integrate Wi-Fi and remote status
- [ ] Send plant moisture values via MQTT or HTTP
- [ ] OTA firmware updates

---

> í·­ Tip: Before continuing, always remember to check your current Git branch (\`git branch\`) before committing." > TODO.md
