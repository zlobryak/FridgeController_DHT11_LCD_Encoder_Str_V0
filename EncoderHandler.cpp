#include "EncoderHandler.h"
#include <Arduino.h>

EncoderHandler::EncoderHandler(int pinCLK, int pinDT, int pinSW)
  : encoder(pinCLK, pinDT) {
  pinMode(pinSW, INPUT_PULLUP);
  _pinSW = pinSW;
  lastPos = encoder.read() / 4;
}

void EncoderHandler::update() {
  long newPos = encoder.read() / 4;
  if (newPos != lastPos) {
    lastPos = newPos;
  }
}

int EncoderHandler::getDirection() {
  long newPos = encoder.read() / 4;
  if (newPos > lastPos) {
    lastPos = newPos;
    return 1;
  } else if (newPos < lastPos) {
    lastPos = newPos;
    return -1;
  }
  return 0;
}

bool EncoderHandler::isButtonPressed() {
  static bool lastState = HIGH;
  bool currentState = digitalRead(_pinSW);

  if (currentState == LOW && lastState == HIGH) {
    // Кнопка только нажата
    buttonPressedMillis = millis();
    wasButtonLongPressed = false;
  }

  if (currentState == HIGH && lastState == LOW) {
    // Кнопка отпущена
    if (!wasButtonLongPressed && (millis() - buttonPressedMillis) < 300) {
      lastState = HIGH;
      return true; // Короткое нажатие
    }
  }

  if (currentState == LOW && (millis() - buttonPressedMillis) > 500) {
    wasButtonLongPressed = true;
  }

  lastState = currentState;
  return false;
}

bool EncoderHandler::isButtonLongPressed() {
  bool currentState = digitalRead(_pinSW);
  if (currentState == LOW && (millis() - buttonPressedMillis) > 500 && !wasButtonLongPressed) {
    wasButtonLongPressed = true;
    return true;
  }
  return false;
}