#include "DisplayManager.h"
#include "CoolingController.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <DHT.h>
#include <Encoder.h>


// === Настройки пинов ===
#define DHTPIN 2
#define DHT11
#define RELAY_PIN 3
#define ENCODER_CLK 6
#define ENCODER_DT 5
#define ENCODER_SW 4

// === Объекты ===
DHT dht(DHTPIN, 11); // можно просто указать тип датчика числом
Encoder myEncoder(ENCODER_DT, ENCODER_CLK);

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

  // --- Изменение температуры энкодером ---
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
    if (!isnan(currentTemp)) {
      thermostat.update(currentTemp);
      display.update(dht.readTemperature(), thermostat.getTargetTemp(), thermostat.isManualMode(), thermostat.isCoolingOn());
      while (digitalRead(ENCODER_SW) == LOW) delay(10);
    }
  }
}

//TODO  Добавить гистерезис
//      Добавить реле
//      Вынести энкодер в отдельный класс