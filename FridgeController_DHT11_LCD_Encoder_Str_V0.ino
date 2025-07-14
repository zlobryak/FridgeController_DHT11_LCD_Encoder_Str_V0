// This code was partially generated using an AI language model Qwen3-235B-A22B
// Review and adjust as needed.

#include "DisplayManager.h"
#include "CoolingController.h"
#include "EncoderHandler.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Encoder.h>
#include <OneWire.h>
#include <DallasTemperature.h>


// === Настройки пинов ===
#define ONE_WIRE_BUS 8         // Пин подключения DS18B20

#define RELAY_PIN 3 //Реле
//Пины энкодера
#define ENCODER_CLK 6 
#define ENCODER_DT 5
#define ENCODER_SW 4

// === Объекты ===
OneWire oneWire(ONE_WIRE_BUS);               // Подключение к шине OneWire
DallasTemperature sensors(&oneWire);         // Датчики температуры
DeviceAddress sensorAddress;                 // Адрес датчика (если несколько)

EncoderHandler encoder(ENCODER_CLK, ENCODER_DT, ENCODER_SW); // Объект энкодера из нового класса
Encoder myEncoder(ENCODER_DT, ENCODER_CLK); //Обьект энкодера из библиотки

LiquidCrystal_I2C lcd(0x27, 16, 2); //Создаем экран
DisplayManager display(lcd); //создаем объект класса DisplayManager
CoolingController thermostat(RELAY_PIN); //Объект термостата

long lastEncoderPos = 0;

unsigned long checkInterval = 5000;
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);  
      // Инициализация датчика температуры
  sensors.begin();
  if (!sensors.getAddress(sensorAddress, 0)) {
    Serial.println("DS18B20 error");
  } else {
    Serial.println("DS18B20 online");
    sensors.setResolution(sensorAddress, 12); // Максимальная точность
  }
  sensors.requestTemperatures(); //Опрос датчика
  thermostat.update(sensors.getTempCByIndex(0)); // Запись значений датчиков в термостат
   
  display.begin(); //Инициалицаация дисплея
  display.update(thermostat); // Отрисовка экрана

  encoder.update();

  pinMode(ONE_WIRE_BUS, INPUT_PULLUP);
  pinMode(ENCODER_SW, INPUT_PULLUP);
  Serial.println("Setup success");
}

void loop() {
  unsigned long currentMillis = millis(); 

  // --- Автоматическое обновление температуры ---
  if (currentMillis - previousMillis >= checkInterval) {
    previousMillis = currentMillis;  
    sensors.requestTemperatures();
    float currentTemp = sensors.getTempCByIndex(0);
    
    Serial.print("Measurment: ");
    Serial.println(currentTemp);
    if (!isnan(currentTemp) && !thermostat.isManualMode()) {      
    
     if (thermostat.getLastTemp() != currentTemp){
      thermostat.update(currentTemp);
      display.updateTargetTemp(currentTemp, display.getCurrentTempPosition() ,display.getCurrentTempRow(), display.getTempCleaner());
                while (digitalRead(ENCODER_SW) == LOW) delay(10);
     }
      display.updateTargetText(thermostat.isCoolingOn() ? "On" : "Off", display.getOnOffPosition(), display.getOnOffRow(), display.getOnOffCleaner());

    }
  }

  // --- Обработка нажатия на энкодер ---
  if (encoder.isButtonPressed()) {
    //меняем режим работы на противоположный
    bool newMode = !thermostat.isManualMode();
    thermostat.setManualMode(newMode);

  // При переходе в ручной режим, по умолчанию выключим реле.
    if (thermostat.isManualMode()) {
      thermostat.setRelayState(false);
    }
  // Обновим информацию по состоянию и режиму на экране
    display.updateTargetText(thermostat.isCoolingOn() ? "On" : "Off", display.getOnOffPosition(), display.getOnOffRow(), display.getOnOffCleaner());
    display.updateTargetText(thermostat.isManualMode() ? "Manual" : "Auto", display.getModePosition(), display.getModeRow(), display.getModeCleaner());
  }

  if (encoder.isButtonLongPressed) {
    isAdjustingHysteresis = !isAdjustingHysteresis;

    if (isAdjustingHysteresis) {
    display.updateTargetText(thermostat.isCoolingOn() ? "On" : "Off", display.getOnOffPosition(), display.getOnOffRow(), display.getOnOffCleaner());
    } else {
      thermostat.setHysteresis(thermostat.getHysteresis()); // Сохранить/применить
      display.update(thermostat); // Вернуть обычный экран
    }
  }


    // --- Поворот энкодера: изменение целевой температуры или состояния реле ---
  int dir = encoder.getDirection();
  if (dir != 0) {
    if (thermostat.isManualMode()) {
    // В ручном режиме: поворот энкодера меняет состояние реле
    if (dir > 0) {
      thermostat.setRelayState(true); // Повернули вправо — включаем
    } else {
      thermostat.setRelayState(false); // Повернули влево — выключаем
    }
      display.updateTargetText(thermostat.isCoolingOn() ? "On" : "Off", display.getOnOffPosition(), display.getOnOffRow(), display.getOnOffCleaner());
    } else {
      // В автоматическом режиме: меняем целевую температуру
      float step = 0.1f;
      float newTargetTemp = thermostat.getTargetTemp() - dir * step;
      thermostat.setTargetTemp(newTargetTemp);
      display.updateTargetTemp(thermostat.getTargetTemp(), display.getTargetTempPosition(), display.getTargetTempRow(), display.getTempCleaner());
    }
  }

}
// TODO
// Дописать метод изменения гистерезица поворотом энкодера, после перехода в этот режим догим нажатием на кнопку