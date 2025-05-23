#include <Arduino.h>

// Analog input for soil moisture sensor (ADC1)
const int sensorPin = 34; // GPIO34: safe analog input
// Digital output for pump relay
const int relayPin = 2;   // GPIO2: safe output for relay

// Moisture threshold (higher = drier)
const int moistureThreshold = 2000;
// Pump activation time in milliseconds
const int wateringDuration = 5000;
// Delay between sensor checks
const int checkInterval = 10000;

// FreeRTOS task for managing one plant
void irrigationTask(void* param) {
  while (true) {
    int value = analogRead(sensorPin);
    Serial.printf("[Plant] Moisture: %d\n", value);

    if (value > moistureThreshold) {
      Serial.println("[Plant] --> Dry soil, activating pump");
      digitalWrite(relayPin, LOW);  // Relay on
      vTaskDelay(pdMS_TO_TICKS(wateringDuration));
      digitalWrite(relayPin, HIGH); // Relay off
    } else {
      Serial.println("[Plant] --> Moist soil, no watering");
    }

    vTaskDelay(pdMS_TO_TICKS(checkInterval));
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Relay off by default

  xTaskCreatePinnedToCore(
    irrigationTask,    // Task function
    "PlantTask",       // Name
    2048,              // Stack size
    nullptr,           // No parameters needed
    1,                 // Priority
    nullptr,           // No handle needed
    1                  // Run on core 1
  );
}

void loop() {
  // Nothing here: everything runs on the task
}
