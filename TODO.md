# TODO – UI for 2.4" TFT (feature/ui-tft)

### ✅ Completed
- [x] Wire ILI9341 pins (CS, DC, RST) to ESP32 and test init  
- [x] Implement `TFTDisplay.begin()` and `showPage()`  
- [x] Integrate `display.showPage()` in a dedicated FreeRTOS task  
- [x] Cycle pages (plants 1–4 / 5–8) via timeout  

### 🔜 Next Steps
- [ ] Add physical button or touch input to manually switch pages  
- [ ] Optimize redraw logic to update only changed elements  
- [ ] Measure render time & ensure no FreeRTOS deadlines are missed  
- [ ] Add error handling if display init or writes fail  
- [ ] Document UI module usage in `feature/docs-base` or new docs branch  
- [ ] Prepare for release: bump version, finalize CHANGELOG and README  
