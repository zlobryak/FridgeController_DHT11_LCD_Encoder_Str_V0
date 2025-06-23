// CoolingController.cpp
#include "CoolingController.h"
#include <Arduino.h> 

CoolingController::CoolingController(int pin) : relayPin(pin) {
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, HIGH); // Реле выключено
}

void CoolingController::setTargetTemp(float temp) {
    targetTemp = temp;
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
        if (currentTemp > targetTemp) {  // ← ВАЖНО: поменяли сравнение
            setRelayState(true);         // Включаем охлаждение
        } else {
            setRelayState(false);        // Выключаем охлаждение
        }
    }
}