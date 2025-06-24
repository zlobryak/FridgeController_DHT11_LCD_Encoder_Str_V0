// This code was partially generated using an AI language model Qwen3-235B-A22B
// Review and adjust as needed.

#include "DisplayManager.h"
#include <Arduino.h>

DisplayManager::DisplayManager(LiquidCrystal_I2C &lcd) : lcd(lcd) {}
int DisplayManager::getTargetTempPosition() { return targetTempPosition; }
int DisplayManager::getTargetTempRow() { return targetTempRow; }

int DisplayManager::getCurrentTempPosition() { return currentTempPosition; }
int DisplayManager::getCurrentTempRow() { return currentTempRow; }

void DisplayManager::begin() {
  lcd.init();
  lcd.backlight();
  lcd.print("Thermostat v1.0");
  delay(1500);
  lcd.clear();
  Serial.println("LCD started");
}

void DisplayManager::update(float currentTemp, float targetTemp, bool manualMode, bool relayState) {
  Serial.println("LCD fully updated");
  lcd.clear();

  // Строка 0: текущая и целевая температура
  lcd.setCursor(0, 0);
  lcd.print("T:");
  updateTargetTemp(currentTemp, currentTempPosition, currentTempRow);
  lcd.print(" S:");

  updateTargetTemp(targetTemp, targetTempPosition, targetTempRow);

  // Строка 1: режим и состояние нагревателя
  lcd.setCursor(0, 1);
  lcd.print(manualMode ? "Manual " : "Auto ");
  lcd.print(relayState ? "ON " : "OFF");
}

void DisplayManager::updateTargetTemp(float targetTemp, int position, int row) {
  Serial.print("updateTargetTemp called: ");
  Serial.print(position);
  Serial.print(" ");
  Serial.print(row);
  Serial.print(" ");
  String buffer = String(targetTemp, 1); // один знак после запятой
  Serial.println("buffer: " + buffer);

  // Вычисляем позицию так, чтобы текст начинался с правого края
  int startPos = position - buffer.length() + 1;
  if (startPos < 0) startPos = 0;

  for (int i = 0; i > cleaner; i++){
    lcd.setCursor(position + i, row);
    lcd.print(" ");
  }

  lcd.setCursor(startPos, row);
  lcd.print(buffer);
}