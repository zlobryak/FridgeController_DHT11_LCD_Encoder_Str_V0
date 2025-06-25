// This code was partially generated using an AI language model Qwen3-235B-A22B
// Review and adjust as needed.

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <LiquidCrystal_I2C.h>

class DisplayManager {
public:
  DisplayManager(LiquidCrystal_I2C &lcd);

  void begin();
  void update(float currentTemp, float targetTemp, bool manualMode, bool relayState);

  void updateTargetTemp(float targetTemp, int position, int row);

  void updateTargetText(String text, int position, int row);
    
  int getTargetTempPosition();
  int getTargetTempRow();

  int getCurrentTempPosition();
  int getCurrentTempRow();

  
private:
  LiquidCrystal_I2C &lcd;

  int cleaner = 5;

  int currentTempPosition = 6;
  int currentTempRow = 0;

  int targetTempPosition = 15;
  int targetTempRow = 0;  

  int modeOnOffPosition = 7;
  int modeOnOffROW = 1;
};

#endif