# Arduino VL6180X Time of Flight Distance Sensor 

This project demonstrates how to use the **VL6180X** Time of Flight Distance Sensor from **STMicroelectronics** with an Arduino to measure distances.

## Overview

The **VL6180X** is a Time of Flight (ToF) sensor that can measure distances up to 100 mm. It uses the principle of light reflection to determine the distance of objects in its line of sight. This sensor is based on a **VCSEL (Vertical-cavity surface-emitting laser)** and an **aperture detector**.

### Key Features:
- **Distance Measurement**: Measures distances from 20mm to 100mm.
- **I2C Communication**: Uses I2C to communicate with the Arduino.
- **Ambient Light Sensing**: Can also measure ambient light levels.

## Hardware Requirements
- **Arduino DUE Board** 
- **VL6180X Sensor**
- **Jumper Wires**
- **Breadboard** (optional)

### Wiring

- **VL6180X VCC** → Arduino 5V (or 3.3V depending on your board)
- **VL6180X GND** → Arduino GND
- **VL6180X SDA** → Arduino A4 (SDA Pin on Arduino Uno)
- **VL6180X SCL** → Arduino A5 (SCL Pin on Arduino Uno)

