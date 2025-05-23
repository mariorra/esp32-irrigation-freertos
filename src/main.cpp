#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

// Configuration structure passed to each task
  struct PlantConfig {
    uint8_t channel;                 // ADS1115 analog input channel (0-3)
    Adafruit_ADS1115* adc;           // Pointer to the ADC instance
    uint8_t relayPin;                // GPIO pin for controlling the pump relay
    SemaphoreHandle_t* mutex;          // Pointer to shared I2C mutex
  };

// Moisture threshold (higher = drier)
  const int moistureThreshold = 2000;
// Pump active time in milliseconds
  const int wateringDuration = 5000;
// Delay between sensor checks
  const int checkInterval = 20000;

// ADS1115 instance (0x48 and 0x49)
  Adafruit_ADS1115 ads1;  
  Adafruit_ADS1115 ads2;

// FreeRTOS mutex to protect access to the I2C bus (shared between tasks)
  SemaphoreHandle_t i2cMutex;

// FreeRTOS task to manage each plant, defined a unique task for all the plants
// Goal is to reduce the ammount of coding puting generic definition as the expected behaviour is the same 
void irrigationTask(void* param) {
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
      Serial.printf("[Plant %d] ⚠ Failed to acquire I2C mutex! ⚠\n", channel + 1);
      moisture = -1; // Optional: mark as invalid reading
      }
    }


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
  //const char *pcTaskError = "Error creating task! ";

  // Create the I2C mutex for synchronized access between tasks
  i2cMutex = xSemaphoreCreateMutex();

  Wire.begin(21, 22);// SDA = GPIO 21, SCL = GPIO 22
  Serial.println("SETUP: I2C created");

   if (!ads1.begin(0x48)) {
    Serial.println("❌ Failed to initialize ADS1115 #1 at address 0x48");
    while (true);
  }

  // Initialize second ADS1115 (address 0x49)
  if (!ads2.begin(0x49)) {
    Serial.println("❌ Failed to initialize ADS1115 #2 at address 0x49");
    while (true);
  }

  Serial.println("ADS1115 #1 & #2 initialized.");
  //Relay definition
  const uint8_t relayPins[8] = {2, 4, 5, 15, 16, 17, 18, 19};

  for (int i = 0; i < 8; i++) {
    // Assign each plant to either ads1 or ads2 based on index
    Adafruit_ADS1115* selectedADC = (i < 4) ? &ads1 : &ads2;
    uint8_t channel = i % 4;

    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); // Relay OFF by default

    // Allocate configuration for this task
    PlantConfig* cfg = new PlantConfig{channel, selectedADC, relayPins[i], &i2cMutex};

    xTaskCreatePinnedToCore(
      irrigationTask,                        // Task function
      ("PumpTask" + String(i)).c_str(),      // Task name
      2048,                                  // Stack size
      cfg,                                 // Parameter
      1,                                     // Priority
      nullptr,                               // No handle needed
      1                                      // Core 1
    );
  }
}

void loop() {
  // Not used – all logic handled by FreeRTOS tasks
}
