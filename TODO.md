cat > TODO.md << 'EOF'
# TODO – UI for 2.4" TFT (feature/ui-tft)

- [ ] Wire ILI9341 pins (CS, DC, RST) to ESP32 and test init
- [ ] Implement TFTDisplay.begin() and showPage()
- [ ] Integrate display.showPage() in a dedicated FreeRTOS task
- [ ] Cycle pages (plants 1–4 / 5–8) via button or timeout
- [ ] Measure render time & ensure FreeRTOS responsiveness
EOF
