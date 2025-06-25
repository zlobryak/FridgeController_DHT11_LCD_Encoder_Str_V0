// This code was partially generated using an AI language model Qwen3-235B-A22B
// Review and adjust as needed.

#include "DisplayManager.h"
#include <Arduino.h>

DisplayManager::DisplayManager(LiquidCrystal_I2C &lcd) : lcd(lcd) {}
int DisplayManager::getTargetTempPosition() { return targetTempPosition; }
int DisplayManager::getTargetTempRow() { return targetTempRow; }

int DisplayManager::getCurrentTempPosition() { return currentTempPosition; }
int DisplayManager::getCurrentTempRow() { return currentTempRow; }
int DisplayManager::getOnOffPosition() { return modeOnOffPosition; }
int DisplayManager::getOnOffRow() { return modeOnOffRow; }
int DisplayManager::getModePosition() { return modePosition; }
int DisplayManager::getModeRow() { return modeRow; }
int DisplayManager::getTempCleaner() { return tempCleaner; }
int DisplayManager::getModeCleaner() { return modeCleaner; }
int DisplayManager::getOnOffCleaner() { return onOffCleaner; }

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
  updateTargetTemp(currentTemp, currentTempPosition, currentTempRow, tempCleaner);
  lcd.print(" S:");

  updateTargetTemp(targetTemp, targetTempPosition, targetTempRow, tempCleaner);

  // Строка 1: режим и состояние нагревателя
  lcd.setCursor(0, 1);
  lcd.print(manualMode ? "Manual " : "Auto ");
  lcd.print(relayState ? "ON " : "OFF");
}

void DisplayManager::updateTargetTemp(float targetTemp, int position, int row, int tempCleaner) {
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

  for (int i = 0; i > tempCleaner; i++){
    lcd.setCursor(position + i, row);
    lcd.print(" ");
  }

  lcd.setCursor(startPos, row);
  lcd.print(buffer);
}

void DisplayManager::updateTargetText(String text, int position, int row, int textCleaner){
  Serial.print("updateTargetText called: ");
  Serial.print(position);
  Serial.print(" ");
  Serial.print(row);
  Serial.print(" ");
  Serial.print(text);
  Serial.print(" ");
  Serial.println(textCleaner);


  // Вычисляем позицию так, чтобы текст начинался с правого края
  int startPos = position - text.length() + 1;
  if (startPos < 0) startPos = 0;

  for (int i = textCleaner; i > 0; i--){
    lcd.setCursor(position - i, row);
    lcd.print(" ");
  }

  lcd.setCursor(startPos, row);
  lcd.print(text);
}