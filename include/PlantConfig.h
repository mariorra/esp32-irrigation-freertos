#pragma once

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>
#include "freertos/semphr.h"  // For SemaphoreHandle_t

struct PlantConfig {
    uint8_t channel;                  // ADC channel (0–3)
    Adafruit_ADS1115* adc;           // Pointer to ADC instance
    uint8_t relayPin;                // GPIO pin for the pump
    SemaphoreHandle_t* mutex;        // Shared I2C mutex

    int moistureThreshold;           // Threshold above which watering starts
    int wateringDuration;            // Duration to keep pump ON (ms)
    int checkInterval;               // Delay between moisture checks (ms)
};
