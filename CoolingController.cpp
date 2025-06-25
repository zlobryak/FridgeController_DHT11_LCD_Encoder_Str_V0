// CoolingController.cpp
// This code was partially generated using an AI language model Qwen3-235B-A22B
// Review and adjust as needed.
#include "CoolingController.h"
#include <Arduino.h> 

CoolingController::CoolingController(int pin) : relayPin(pin) {
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, HIGH); // Реле выключено
}

void CoolingController::setLastTemp(float currentTemp){
      lastTemp = currentTemp;
      Serial.print("LastTemp set: ");
      Serial.println(lastTemp);
    }

float CoolingController::getLastTemp() const{
  return lastTemp;
}

void CoolingController::setTargetTemp(float currentTemp) {
    if (currentTemp < MIN_TARGET_TEMP) {
        targetTemp = MIN_TARGET_TEMP;
    } else if (currentTemp > MAX_TARGET_TEMP) {
        targetTemp = MAX_TARGET_TEMP;
    } else {
        targetTemp = currentTemp;
    }
    Serial.print("TargetTemp set: ");
    Serial.println(currentTemp);
}

float CoolingController::getTargetTemp() {
    return targetTemp;
}

void CoolingController::setManualMode(bool mode) {
    manualMode = mode;
    Serial.print("Mode changed to: ");
    Serial.println(mode ? "Manual" : "Auto");
}

void CoolingController::setRelayState(bool state) {
    Serial.println(
      String("RelayState: ") +
      (state ? "On" : "Off")
    );
    relayState = state;
    digitalWrite(relayPin, relayState ? LOW : HIGH);
}

bool CoolingController::isManualMode() {
    return manualMode;
}
bool CoolingController::isCoolingOn() {
    return relayState;
}

void CoolingController::update(float currentTemp) {
    if (!manualMode) {
        if (currentTemp > targetTemp) {
            setRelayState(true);         // Включаем охлаждение
        } else {
            setRelayState(false);        // Выключаем охлаждение
        }
    }
    Serial.print("Controller update called. ");
    Serial.print("Mode: ");
    Serial.print(manualMode ? "Manual " : "Auto ");
    Serial.print("currentTemp: ");
    Serial.print(currentTemp);
    Serial.print(" ");
    Serial.print("targetTemp: ");
    Serial.println(targetTemp);

}