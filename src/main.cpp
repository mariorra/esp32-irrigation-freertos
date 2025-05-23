#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

// Configuration structure passed to each task
  struct PlantConfig {
    uint8_t channel;                 // ADS1115 analog input channel (0-3)
    Adafruit_ADS1115* adc;           // Pointer to the ADC instance
    uint8_t relayPin;                // GPIO pin for controlling the pump relay
  };

// Moisture threshold (higher = drier)
  const int moistureThreshold = 2000;
// Pump active time in milliseconds
  const int wateringDuration = 5000;
// Delay between sensor checks
  const int checkInterval = 20000;

// ADS1115 instance
  Adafruit_ADS1115 ads;  

// FreeRTOS task to manage each plant, defined a unique task for all the plants
// Goal is to reduce the ammount of coding puting generic definition as the expected behaviour is the same 
void irrigationTask(void* param) {
  PlantConfig* cfg = (PlantConfig*)param; //Access the number stored at the memory address pointed to by param, treating it as a pointer to an integer. Using casting method. 
  
  int channel = cfg->channel;
  uint8_t relayPin = cfg->relayPin;
  Adafruit_ADS1115* adc = cfg->adc;

  delete cfg; // not needed anymore as we pass the value to the plantNumber identifier, free heap memory. 
  param = nullptr; // Defensive: avoid dangling pointer (not strictly needed here)

  while (true) {
    int moisture = adc->readADC_SingleEnded(channel);
    Serial.printf("[Plant %d] Moisture: %d\n", channel + 1, moisture);

    if (moisture > moistureThreshold) {
      Serial.printf("[Plant %d] --> Dry soil, activating pump\n", channel + 1);
      digitalWrite(relayPin, LOW);  // Relay ON
      vTaskDelay(pdMS_TO_TICKS(wateringDuration));
      digitalWrite(relayPin, HIGH); // Relay OFF
    } else {
      Serial.printf("[Plant %d] --> Moist soil, no watering\n", channel + 1);
    }

    vTaskDelay(pdMS_TO_TICKS(checkInterval));
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("SETUP: first print ");
  const char *pcTaskError = "Error creating task! ";

  Wire.begin(21, 22);// SDA = GPIO 21, SCL = GPIO 22
  Serial.println("SETUP: I2C created");

  if (!ads.begin(0x48)) {  // I2C address of the ADS1115
    Serial.println("Failed to initialize ADS1115. Check wiring!");
    while (1);
  }

  Serial.println("ADS1115 initialized.");
//Relay definition
  const uint8_t relayPins[4] = {2, 4, 5, 15};

  for (int i = 0; i < 4; i++) {
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
