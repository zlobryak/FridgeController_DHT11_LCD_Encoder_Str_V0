// This code was partially generated using an AI language model Qwen3-235B-A22B
// Review and adjust as needed.

#include "DisplayManager.h"
#include "CoolingController.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Encoder.h>


// === Настройки пинов ===
#define DHTPIN 2
#define DHTTYPE DHT_TYPE_DHT11
#define RELAY_PIN 3
#define ENCODER_CLK 6
#define ENCODER_DT 5
#define ENCODER_SW 4

// === Объекты ===
DHT dht(DHTPIN, 11); // можно просто указать тип датчика числом (11 или 22)
Encoder myEncoder(ENCODER_DT, ENCODER_CLK); //Обьект энкодера из библиотки

LiquidCrystal_I2C lcd(0x27, 16, 2);
DisplayManager display(lcd);
CoolingController thermostat(RELAY_PIN);

long lastEncoderPos = 0;

unsigned long checkInterval = 5000;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  display.begin();
  display.update(dht.readTemperature(), thermostat.getTargetTemp(), thermostat.isManualMode(), thermostat.isCoolingOn());
  pinMode(ENCODER_SW, INPUT_PULLUP);
  Serial.println("Setup success");
}

void loop() {
  unsigned long currentMillis = millis();

  // --- Обработка нажатия на энкодер ---
  if (digitalRead(ENCODER_SW) == LOW) {
    delay(50); // Антидребезг
    bool newMode = !thermostat.isManualMode();
    thermostat.setManualMode(newMode);
    if (newMode) {
      thermostat.setRelayState(!thermostat.isCoolingOn());
    }
    display.update(dht.readTemperature(), thermostat.getTargetTemp(), thermostat.isManualMode(), thermostat.isCoolingOn());
    while (digitalRead(ENCODER_SW) == LOW) delay(10);
  }

  // --- Изменение целевой температуры энкодером ---
  long newPosition = myEncoder.read() / 4;
  //Serial.print("Encoder position: ");
  //Serial.println(newPosition);
  if (newPosition != lastEncoderPos) {
    if (newPosition > lastEncoderPos) {
      thermostat.setTargetTemp(thermostat.getTargetTemp() - 0.1f);
    } else {
      thermostat.setTargetTemp(thermostat.getTargetTemp() + 0.1f);
    }
    lastEncoderPos = newPosition;
    display.updateTargetTemp(thermostat.getTargetTemp(), display.getTargetTempPosition(), display.getTargetTempRow());
  }

  // --- Автоматическое обновление температуры ---
  if (currentMillis - previousMillis >= checkInterval) {
    previousMillis = currentMillis;
    
    float currentTemp = dht.readTemperature();
    thermostat.setLastTemp(currentTemp);
    if (!isnan(currentTemp)) {
      thermostat.update(currentTemp);
     // display.update(dht.readTemperature(), thermostat.getTargetTemp(), thermostat.isManualMode(), thermostat.isCoolingOn());
     if (thermostat.getLastTemp() != currentTemp){
      display.updateTargetTemp(currentTemp, display.getCurrentTempPosition(), display.getCurrentTempRow());
      while (digitalRead(ENCODER_SW) == LOW) delay(10);
     }
    }
  }
}

//TODO  Добавить гистерезис


//      Все перерисовки делать через точечную перерисовку
//      Вынести энкодер в отдельный класс
//      Перерисовка режимов рабты и значения "ON" "OFF"
//
//      Некорректная обработка ручного переключения. done (но отображение не вызывается при автоматическом переключении)
//      Для чего нужно добавить ручную прорисовук режима и On Of, а затем вызывать этим методы в автоматическом обновлении