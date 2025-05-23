#include "TFTDisplay.h"
#include <Arduino.h>
#include <Adafruit_GFX.h>

TFTDisplay::TFTDisplay(Adafruit_ILI9341& tft) : _tft(tft) {}

void TFTDisplay::begin() {
    _tft.begin();                      // Initialize the ILI9341 controller
    _tft.setRotation(1);               // Landscape orientation
    _tft.fillScreen(ILI9341_BLACK);    // Clear the screen to black
}

void TFTDisplay::showPage(int pageIndex, const int16_t readings[], int count) {
    _tft.fillScreen(ILI9341_BLACK);    // Clear previous page

    const int baseX = 20;              // X offset for first bar
    const int spacing = 80;            // Spacing between bars

    for (int i = 0; i < count; i++) {
        int16_t raw = readings[i];     // Raw ADC value for this bar
        String label = "P" + String(pageIndex * count + i + 1);
        drawBar(baseX + i * spacing, raw, label);
    }

    // Navigation arrows
    _tft.setTextSize(2);
    _tft.setTextColor(ILI9341_WHITE);
    _tft.setCursor(5, 225);
    _tft.print("<");  // Previous page arrow
    _tft.setCursor(300, 225);
    _tft.print(">");  // Next page arrow
}

void TFTDisplay::drawBar(int x, int16_t raw, const String& label) {
    int bh = map(raw, RAW_MIN, RAW_MAX, 0, BAR_MAX_H);
    bh = constrain(bh, 0, BAR_MAX_H);

    int yTop = BAR_Y_BOTTOM - bh;

    // Draw bar outline
    _tft.drawRect(x, BAR_Y_BOTTOM - BAR_MAX_H, BAR_WIDTH, BAR_MAX_H, ILI9341_WHITE);
    
    // Fill bar interior
    _tft.fillRect(x + 1, yTop, BAR_WIDTH - 2, bh, ILI9341_CYAN);

    // Draw indicator circle at top of fill
    _tft.fillCircle(x + BAR_WIDTH/2, yTop, 8, ILI9341_WHITE);
    _tft.drawCircle(x + BAR_WIDTH/2, yTop, 8, ILI9341_BLACK);

    // Percentage text
    int pct = map(raw, RAW_MIN, RAW_MAX, 0, 100);
    _tft.setTextSize(1);
    _tft.setTextColor(ILI9341_WHITE);
    _tft.setCursor(x + BAR_WIDTH/2 - 10, yTop - 12);
    _tft.print(pct);
    _tft.print("%");

    // Label below bar
    _tft.setCursor(x + BAR_WIDTH/2 - 6, BAR_Y_BOTTOM + 5);
    _tft.print(label);
}