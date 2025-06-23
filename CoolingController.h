// CoolingController.h
#pragma once

class CoolingController {
public:
    CoolingController(int relayPin);

    void setTargetTemp(float temp);
    float getTargetTemp();
    void setManualMode(bool mode);
    void setRelayState(bool state);
    void update(float currentTemp);

    bool isManualMode();
    bool isCoolingOn();

private:
    int relayPin;
    float targetTemp = -15.0;
    bool manualMode = false;
    bool relayState = false;
};