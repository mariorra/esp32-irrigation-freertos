#include "PlantController.h"


// Goal is to reduce the ammount of coding puting generic definition as the expected behaviour is the same 
void PlantController::irrigationTask(void* param) {
  PlantConfig* cfg = (PlantConfig*)param; //Access the number stored at the memory address pointed to by param, treating it as a pointer to an integer. Using casting method. 
  int channel = cfg->channel;
  uint8_t relayPin = cfg->relayPin;
  Adafruit_ADS1115* adc = cfg->adc;
  SemaphoreHandle_t* mutex = cfg->mutex;

  delete cfg; // not needed anymore as we pass the value to the plantNumber identifier, free heap memory. 
  param = nullptr; // Defensive: avoid dangling pointer (not strictly needed here)

  while (true) {
    int moisture = 0;

    // Lock I2C access with mutex before reading from ADC
    if (xSemaphoreTake(*mutex, portMAX_DELAY)) {
      moisture = adc->readADC_SingleEnded(channel);
      xSemaphoreGive(*mutex);
      {
      Serial.printf("[Plant %d] ⚠ Failed to acquire I2C mutex! ⚠ \n", channel + 1);
      moisture = -1; // Optional: mark as invalid reading
      }
    }


    Serial.printf("[Plant %d] Moisture: %d\n", channel + 1, moisture);

    if (moisture > cfg->moistureThreshold) {
      Serial.printf("[Plant %d] --> Dry soil, activating pump\n", channel + 1);
      digitalWrite(relayPin, LOW);  // Relay ON
      vTaskDelay(pdMS_TO_TICKS( cfg->wateringDuration));
      digitalWrite(relayPin, HIGH); // Relay OFF
    } else {
      Serial.printf("[Plant %d] --> Moist soil, no watering\n", channel + 1);
    }

    vTaskDelay(pdMS_TO_TICKS( cfg->checkInterval));
  }
}

void PlantController::startTask(PlantConfig* config, int taskIndex) {
  xTaskCreatePinnedToCore(
    irrigationTask,
    ("PumpTask" + String(taskIndex)).c_str(),
    2048,
    config,
    1,
    nullptr,
    1
  );
}