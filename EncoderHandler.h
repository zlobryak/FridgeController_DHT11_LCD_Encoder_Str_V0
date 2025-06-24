// This code was partially generated using an AI language model Qwen3-235B-A22B
// Review and adjust as needed.
//EncoderHandler.h
#pragma once
#include <Encoder.h>

class EncoderHandler{
  public:
    EncoderHandler(int pinDT, int pinCLK, int pinSW)

    void update(); // Обновляем состояние энкодера

    // Получаем направление поворота: +1 (вправо), -1 (влево), 0 (нет изменений)
    int getDirection();

    // Проверяем нажатие кнопки
    bool isButtonPressed();

  private:
      Encoder encoder;
    int swPin;

    long lastPosition = 0;
    long currentPosition = 0;
    bool buttonPressed = false;

}