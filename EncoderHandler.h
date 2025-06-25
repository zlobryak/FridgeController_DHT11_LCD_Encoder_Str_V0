// This code was partially generated using an AI language model Qwen3-235B-A22B
// Review and adjust as needed.
//EncoderHandler.h
#pragma once
#include <Encoder.h>
#include <Arduino.h>

class EncoderHandler {
  public:
    EncoderHandler(int pinDT, int pinCLK, int pinSW);
    // Возвращаем состояние кнопки
    bool isButtonPressed();

    // Получаем направление поворота: +1 (вправо), -1 (влево), 0 (нет изменений)
    int getDirection();
    // Возвращаем положение энкодера
    long GetCurrentPosition();
    long SetcurrentPosition();


  private:
    Encoder encoder;
    int swPin;

    long lastPosition = 0;
    long currentPosition = 0;
    bool buttonPressed = false;

};