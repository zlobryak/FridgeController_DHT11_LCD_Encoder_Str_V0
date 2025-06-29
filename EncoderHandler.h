#ifndef ENCODERHANDLER_H
#define ENCODERHANDLER_H

#include <Encoder.h>

class EncoderHandler {
  public:
    EncoderHandler(int pinA, int pinB, int pinSW);
    void update();
    int getDirection(); // -1, 0, +1
    bool isButtonPressed();     // Короткое нажатие
    bool isButtonLongPressed(); // Долгое нажатие (> 500 мс)

  private:
    Encoder encoder;
    long lastPos;
    int _pinSW;

    unsigned long buttonPressedMillis = 0;
    bool wasButtonLongPressed = false;
};

#endif