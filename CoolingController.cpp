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
    }

float CoolingController::getLastTemp() const{
  return lastTemp;
}

void CoolingController::setTargetTemp(float temp) {
    if (temp < MIN_TARGET_TEMP) {
        targetTemp = MIN_TARGET_TEMP;
    } else if (temp > MAX_TARGET_TEMP) {
        targetTemp = MAX_TARGET_TEMP;
    } else {
        targetTemp = temp;
    }
}

float CoolingController::getTargetTemp() {
    return targetTemp;
}

void CoolingController::setManualMode(bool mode) {
    manualMode = mode;
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
}