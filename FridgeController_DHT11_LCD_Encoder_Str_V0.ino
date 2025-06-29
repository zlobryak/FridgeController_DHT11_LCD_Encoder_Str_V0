// This code was partially generated using an AI language model Qwen3-235B-A22B
// Review and adjust as needed.

#include "DisplayManager.h"
#include "CoolingController.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Encoder.h>
#include <OneWire.h>
#include <DallasTemperature.h>


// === Настройки пинов ===
#define ONE_WIRE_BUS 7         // Пин подключения DS18B20

#define RELAY_PIN 3 //Реле
//Пины энкодера
#define ENCODER_CLK 6 
#define ENCODER_DT 5
#define ENCODER_SW 4

// === Объекты ===
OneWire oneWire(ONE_WIRE_BUS);               // Подключение к шине OneWire
DallasTemperature sensors(&oneWire);         // Датчики температуры
DeviceAddress sensorAddress;                 // Адрес датчика (если несколько)


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
    sensors.setResolution(sensorAddress, 12); // Максимальная точность
  }
  sensors.requestTemperatures(); //Опрос датчика
  thermostat.update(sensors.getTempCByIndex(0)); // Запись значений датчиков в термостат
   
  display.begin(); //Инициалицаация дисплея
  display.update(thermostat); // Отрисовка экрана

  
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
    sensors.requestTemperatures();
  //  display.updateTargetTemp(thermostat.getTargetTemp(), display.getTargetTempPosition(), display.getTargetTempRow(), display.getTempCleaner());
  // display.updateTargetTemp(sensors.getTempCByIndex(0), display.getCurrentTempPosition(), display.getCurrentTempRow(), display.getTempCleaner());
    display.updateTargetText(thermostat.isCoolingOn() ? "On" : "Off",display.getOnOffPosition(),display.getOnOffRow(), display.getOnOffCleaner());
    display.updateTargetText(thermostat.isManualMode() ? "Manual" : "Auto",display.getModePosition(),display.getModeRow(), display.getModeCleaner());
   // display.update(dht.readTemperature(), thermostat.getTargetTemp(), thermostat.isManualMode(), thermostat.isCoolingOn());
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
    display.updateTargetTemp(thermostat.getTargetTemp(), display.getTargetTempPosition(), display.getTargetTempRow(), display.getTempCleaner());
  }

  // --- Автоматическое обновление температуры ---
  if (currentMillis - previousMillis >= checkInterval) {
    previousMillis = currentMillis;
    
    sensors.requestTemperatures();
    float currentTemp = sensors.getTempCByIndex(0);
    Serial.print("Measurment: ");
    Serial.println(currentTemp);
    if (!isnan(currentTemp)) {      
    
     if (thermostat.getLastTemp() != currentTemp){
      thermostat.update(currentTemp);
      display.updateTargetTemp(currentTemp, display.getCurrentTempPosition() ,display.getCurrentTempRow(), display.getTempCleaner());
                while (digitalRead(ENCODER_SW) == LOW) delay(10);
     }
      display.updateTargetText(thermostat.isCoolingOn() ? "On" : "Off", display.getOnOffPosition(), display.getOnOffRow(), display.getOnOffCleaner());

    }
  }

}

//TODO  Добавить гистерезис done 


//      Все перерисовки делать через точечную перерисовку Done
//      Вынести энкодер в отдельный класс
//      Перерисовка режимов рабты и значения "ON" "OFF"
//
//      Некорректная обработка ручного переключения. done (но отображение не вызывается при автоматическом переключении)
//      Для чего нужно добавить ручную прорисовук режима и On Of, а затем вызывать этим методы в автоматическом обновлении