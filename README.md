# 🧊 Fridge Thermostat Arduino Controller

Arduino-based thermostat controller for a fridge with temperature monitoring and relay control.

---

## 📄 Description

This project is an Arduino-powered thermostat controller designed to regulate the temperature of a fridge. It reads temperature data from a sensor (e.g., DS18B20), compares it to a setpoint, and controls a relay to turn the fridge compressor on or off accordingly.

---

## 🔧 Features

- Real-time temperature reading  
- Adjustable temperature setpoint  
- Relay control based on temperature  
- Display support (16 x 2, I2C)
- Debug via serial monitor  

---

## 🤖 AI Use Disclosure

> **Note:** Most of the code was initially generated using the Qwen AI chat model. Some parts were later rewritten or fine-tuned manually, also with assistance from AI tools.

If you're reusing or modifying this project, feel free to use the AI-generated parts but ensure proper attribution and testing.

---

## 📦 Hardware Requirements

- Arduino Uno (or compatible board)
- Temperature sensor (DS18B20 recommended)
- Relay module (5V or 12V depending on setup)
- Power supply for Arduino and components
- Optional: I2C LCD/OLED display
- Optional: Push buttons for setting temperature

---

## 📁 File Structure

- `FridgeController_DHT11_LCD_Encoder_Str_V0` – Main Arduino sketch
- `README.md` – This file


---

## 🛠️ Installation

1. Install Arduino IDE or your preferred environment.
2. Install necessary libraries:
   - DHT.h
   - OneWire
   - DallasTemperature
   - LiquidCrystal_I2C (if using LCD)
3. Upload the sketch to your Arduino.
4. Connect hardware as described in the wiring diagram.

---

## 📈 Example Output (Serial Monitor)
LCD started
LCD fully updated
updateTargetTemp called: 6 0 buffer: 25.0
updateTargetTemp called: 15 0 buffer: 4.0
Setup success
RelayState: On
