#include <Arduino.h>

// Analog pins (ADC1) for moisture sensors
const int sensorPins[4] = {34, 35, 32, 33};
// Digital pins for pump relays
const int relayPins[4] = {2, 4, 5, 15};

// Moisture threshold (higher = drier)
const int moistureThreshold = 2000;
// Pump active time in milliseconds
const int wateringDuration = 5000;
// Delay between sensor checks
const int checkInterval = 10000;

// FreeRTOS task to manage each plant
void irrigationTask(void* param) {
  int plantNumber = *((int*)param);
  int sensorPin = sensorPins[plantNumber];
  int relayPin = relayPins[plantNumber];

  while (true) {
    int moisture = analogRead(sensorPin);
    Serial.printf("[Plant %d] Moisture: %d\n", plantNumber + 1, moisture);

    if (moisture > moistureThreshold) {
      Serial.printf("[Plant %d] --> Dry soil, activating pump\n", plantNumber + 1);
      digitalWrite(relayPin, LOW);  // Relay ON
      vTaskDelay(pdMS_TO_TICKS(wateringDuration));
      digitalWrite(relayPin, HIGH); // Relay OFF
    } else {
      Serial.printf("[Plant %d] --> Moist soil, no watering\n", plantNumber + 1);
    }

    vTaskDelay(pdMS_TO_TICKS(checkInterval));
  }
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 4; i++) {
    pinMode(sensorPins[i], INPUT);
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); // Relay OFF by default

    // Allocate unique plantNumber for this task
    int* param = new int(i);
    xTaskCreatePinnedToCore(
      irrigationTask,                        // Task function
      ("PumpTask" + String(i)).c_str(),      // Task name
      2048,                                  // Stack size
      param,                                 // Parameter
      1,                                     // Priority
      nullptr,                               // No handle needed
      1                                      // Core 1
    );
  }
}

void loop() {
  // Not used – all logic handled by FreeRTOS tasks
}
