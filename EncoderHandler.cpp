// This code was partially generated using an AI language model Qwen3-235B-A22B
// Review and adjust as needed.
// EncoderHandler.cpp

#include "EncoderHandler.h"
#include <Arduino.h>

EncoderHandler::EncoderHandler(int pinDT, int pinCLK, int pinSW)
    : encoder(pinDT, pinCLK), swPin(pinSW) {
    pinMode(swPin, INPUT_PULLUP);
    lastPosition = encoder.read();
}

void EncoderHandler::update() {
    currentPosition = encoder.read();

    // Обработка кнопки
    if (digitalRead(swPin) == LOW) {
        delay(50); // Антидребезг
        buttonPressed = true;
        while (digitalRead(swPin) == LOW) delay(10); // Ждём отпускания
    } else {
        buttonPressed = false;
    }
}

int EncoderHandler::getDirection() {
    if (currentPosition > lastPosition) {
        lastPosition = currentPosition;
        return 1; // Поворот вправо
    } else if (currentPosition < lastPosition) {
        lastPosition = currentPosition;
        return -1; // Поворот влево
    }
    return 0; // Нет изменения
}

bool EncoderHandler::isButtonPressed() {
    return buttonPressed;
}