#pragma once
#include "PlantConfig.h"
#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

class PlantController {
public:
  static void startTask(PlantConfig* config, int taskIndex);

private:
  static void irrigationTask(void* param);
};
