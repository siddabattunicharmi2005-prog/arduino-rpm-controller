# Arduino-Based DC Motor RPM Controller & Meter

A Tinkercad-simulated embedded systems project that demonstrates real-time speed control and monitoring of a DC motor using an Arduino Uno, an L293D motor driver, an I2C LCD screen, and a potentiometer.

---

## 📝 Project Description

This project is an embedded systems prototype designed to control and monitor the speed of a DC motor in real-time. The system utilizes an Arduino Uno to process analog inputs from a potentiometer, translate that data into a Pulse Width Modulation (PWM) signal, and drive the motor via an L293D push-pull four-channel driver chip.

### Key Engineering Design Choices:
* **Isolated Power Rails:** To prevent inductive voltage spikes and excessive current draw from damaging the microcontroller, the circuit splits power. The Arduino provides 5V for the logic circuitry, while an external 9V battery supplies dedicated high-current power to the motor.
* **I2C Protocol Communication:** Integrating an I2C backpack onto the 16x2 LCD reduces the required data pins from 6 down to just 2 (SDA and SCL), maximizing available pins on the Arduino Uno for other peripherals.
* **PWM Speed Control:** The duty cycle of the motor driver is dynamically adjusted via analog voltage values scaled from a 10kΩ potentiometer.

---

## 🛠️ Hardware Components

* **Microcontroller:** Arduino Uno R3
* **Display:** 16x2 Liquid Crystal Display (LCD) with I2C Backpack
* **Driver IC:** L293D Motor Driver
* **Actuator:** DC Motor with Tachometer/Encoder
* **Input Peripheral:** 10kΩ Potentiometer
* **Power Supply:** 9V Battery (External Motor Power)
* **Prototyping:** Breadboard and Jumper Wires

---

## 🔌 Circuit Architecture

### 1. I2C LCD Connections
* **GND** ➡️ Common GND Rail
* **VCC** ➡️ 5V Power Rail
* **SDA** ➡️ Arduino Analog Pin **A4**
* **SCL** ➡️ Arduino Analog Pin **A5**

### 2. Potentiometer Connections
* **Left Leg** ➡️ Common GND Rail
* **Middle Leg (Wiper)** ➡️ Arduino Analog Pin **A0**
* **Right Leg** ➡️ 5V Power Rail

### 3. L293D Motor Driver Pin Mapping
* **Pin 1 (Enable 1,2):** Arduino Digital Pin (PWM Capable)
* **Pin 2 (Input 1):** Arduino Digital Pin
* **Pin 3 (Output 1):** Motor Terminal 1
* **Pins 4 & 5 (GND):** Common GND Rail
* **Pin 8 (VCC2 - Motor Power):** 9V Battery Positive (+) Terminal
* **Pin 16 (VCC1 - Logic Power):** 5V Power Rail

---

## 🖼️ Circuit Simulation Layout

![Circuit Schematic](./circuit-layout.png) 
*(Note: Replace this with your exported Tinkercad image file named 'circuit-layout.png' in your repository root)*

---

## 🚀 Features

* **Real-time Performance:** Turn the potentiometer dial to instantly scale the motor speed from 0% to 100%.
* **Dual-Line Telemetry:** The LCD screen provides clear visual feedback displaying:
  * `Set Speed: X%`
  * `RPM: Y`
* **Clean Power Infrastructure:** Leverages top-and-bottom breadboard rail bridging for optimized wire management.
