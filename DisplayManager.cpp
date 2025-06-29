// This code was partially generated using an AI language model Qwen3-235B-A22B
// Review and adjust as needed.

#include "DisplayManager.h"
#include "CoolingController.h"
#include <Arduino.h>

DisplayManager::DisplayManager(LiquidCrystal_I2C &lcd) : lcd(lcd) {}
int DisplayManager::getTargetTempPosition() { return targetTempPosition; }
int DisplayManager::getTargetTempRow() { return targetTempRow; }

int DisplayManager::getCurrentTempPosition() { return currentTempPosition; }
int DisplayManager::getCurrentTempRow() { return currentTempRow; }

int DisplayManager::getTempCleaner() { return tempCleaner; } //Один геттер для обеих температур

int DisplayManager::getOnOffPosition() { return modeOnOffPosition; }
int DisplayManager::getOnOffRow() { return modeOnOffRow; }
int DisplayManager::getOnOffCleaner() { return onOffCleaner; }

int DisplayManager::getModePosition() { return modePosition; }
int DisplayManager::getModeRow() { return modeRow; }
int DisplayManager::getModeCleaner() { return modeCleaner; }

String DisplayManager::getCurrentTempSignature() { return currentTempSignature; }
int DisplayManager::getCurrentTempSignaturePosition() { return currentTempSignaturePosition; }
int DisplayManager::getCurrentTempSignatureRow() { return currentTempSignatureRow; }
int DisplayManager::getCurrentTempSignatureCleaner() { return currentTempSignatureCleaner; }
String DisplayManager::getTargetTempSignature() { return targetTempSignature; }
int DisplayManager::getTargetTempSignaturePosition() { return targetTempSignaturePosition; }
int DisplayManager::getTargetTempSignatureRow() { return targetTempSignatureRow; }
int DisplayManager::getTargetTempSignatureCleaner() { return targetTempSignatureCleaner; }


void DisplayManager::begin() {
  lcd.init();
  lcd.backlight();
  lcd.print("Loading");
  delay(500);
  lcd.clear();
  Serial.println("LCD started");
}

void DisplayManager::update(CoolingController thermostat) {
  Serial.println("LCD fully updated");
  lcd.clear();
  updateTargetTemp(thermostat.getLastTemp(), currentTempPosition, currentTempRow, tempCleaner); // Выводит на экран текущую температуру

  updateTargetText(targetTempSignature, currentTempSignaturePosition, currentTempSignatureRow, currentTempSignatureCleaner); // Подпись текущей температуры
  updateTargetText(currentTempSignature, targetTempSignaturePosition, targetTempSignatureRow, targetTempSignatureCleaner); // Подпись заданной температуры

  updateTargetTemp(thermostat.getTargetTemp(), targetTempPosition, targetTempRow, tempCleaner); //Выводит на экран заданную температуру

  updateTargetText(thermostat.isManualMode() ? "Auto" : "Manual", modePosition, modeRow, modeCleaner);

  updateTargetText(thermostat.isCoolingOn() ? "On" : "Off", modeOnOffPosition, modeOnOffRow, onOffCleaner);
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