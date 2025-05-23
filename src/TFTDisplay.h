#pragma once

#include <Arduino.h>
#include <Adafruit_ILI9341.h>

class TFTDisplay {
public:
    // Constructor: pass reference to Adafruit_ILI9341 instance
    TFTDisplay(Adafruit_ILI9341& tft);

    // Initialize the display hardware and clear screen
    void begin();

    /**
     * Render a page of bars.
     * @param pageIndex 0-based page number for label offset
     * @param readings  array of raw ADC values
     * @param count     number of readings (bars) to display
     */
    void showPage(int pageIndex, const int16_t readings[], int count);

private:
    Adafruit_ILI9341& _tft;

    // Draw a single bar with outline, fill, indicator, and label
    void drawBar(int x, int16_t raw, const String& label);

    // Bar dimensions and ADC mapping constants
    static constexpr int BAR_WIDTH      = 50;
    static constexpr int BAR_MAX_H      = 120;
    static constexpr int BAR_Y_BOTTOM  = 200;
    static constexpr int RAW_MIN        = 0;
    static constexpr int RAW_MAX        = 32767;
};
