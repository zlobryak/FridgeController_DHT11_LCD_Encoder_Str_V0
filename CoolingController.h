// CoolingController.h
// This code was partially generated using an AI language model Qwen3-235B-A22B
// Review and adjust as needed.
#pragma once

class CoolingController {
public:
    CoolingController(int relayPin);

    void setTargetTemp(float currentTemp);
    float getTargetTemp();

    float getLastTemp();
    void setLastTemp(float currentTemp);

    void setManualMode(bool mode);
    void setRelayState(bool state);
    void update(float currentTemp);

    bool isManualMode();
    bool isCoolingOn();

    float getHysteresis();
    void setHysteresis(float hysteresis);
    

private:
    int relayPin;
    float targetTemp = 4.0;
    float lastTemp = 0.0;
    bool manualMode = false;
    bool relayState = false;

    float hysteresis = 0.5;
    bool isAdjustingHysteresis = false;

    private:
    static constexpr float MIN_TARGET_TEMP = -15.0f;
    static constexpr float MAX_TARGET_TEMP = 15.0f;
};