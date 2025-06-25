// This code was partially generated using an AI language model Qwen3-235B-A22B
// Review and adjust as needed.
// EncoderHandler.cpp
#include <Encoder.h>
#include "EncoderHandler.h"
#include <Arduino.h>

EncoderHandler::EncoderHandler(int pinDT, int pinCLK, int pinSW)
    : encoder(pinDT, pinCLK), swPin(pinSW) {
    pinMode(swPin, INPUT_PULLUP);
    lastPosition = encoder.read();

    Serial.print("Encoder started at: ");
    Serial.print("DT: ");
    Serial.print(pinDT);
    Serial.print("CLK: ");
    Serial.print(pinCLK);
    Serial.print("SW: ");
    Serial.println(pinSW);
}

bool EncoderHandler::isButtonPressed() {
    currentPosition = encoder.read();

    // Обработка кнопки
    if (digitalRead(swPin) == LOW) {
        delay(50); // Антидребезг
        buttonPressed = true;
        while (digitalRead(swPin) == LOW) delay(10); // Ждём отпускания
    } else {
        buttonPressed = false;
    }
    return buttonPressed;
    Serial.print("Encoder update called, button:  ");
    Serial.println(buttonPressed ? "Pressed" : "Not Pressed");
}

int EncoderHandler::getDirection() {
    Serial.print("Encoder getDirrection called, directon: ");
    if (currentPosition > lastPosition) {
        lastPosition = currentPosition;
        Serial.println("1");
        return 1; // Поворот вправо
    } else if (currentPosition < lastPosition) {
        lastPosition = currentPosition;
        Serial.println("-1");
        return -1; // Поворот влево
    }
    Serial.println("0");
    return 0; // Нет изменения
    
}

