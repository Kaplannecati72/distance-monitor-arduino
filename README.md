# Distance-Time Altitude Monitor (Arduino & C++)

I developed this project as part of my practical studies in embedded systems and software development. My main goal was to process ultrasonic sensor data to build a real-time altitude measurement and alert system.

## 🧠 How It Works (Logic & Mathematics)
The system calculates distance by measuring the **Time of Flight (ToF)** of ultrasonic sound waves reflecting off a surface.

**The Core Formula Used:**
$$Distance = \frac{Duration \times 0.0343}{2}$$

- **Data Filtering:** I implemented logic to filter out erroneous sensor readings (below 2cm and above 400cm).
- **I2C Protocol:** I used the I2C communication protocol for the display connection to reduce wiring complexity and stabilize data transmission.

## 🛠️ Hardware & Software
- **Microcontroller:** Arduino Uno
- **Sensor:** HC-SR04 Ultrasonic Distance Sensor
- **Components:** I2C LCD Display (16x2) and Active Buzzer
- **Language:** C++ (Arduino Framework)

## ⚡ Key Features
- **Dynamic Acoustic Feedback:** The buzzer frequency increases as the distance decreases, providing an intuitive proximity warning.
- **High-Precision Data:** Displays real-time altitude with 0.1cm precision.

---
*Developed by a Mathematics student at Ankara University with a focus on Embedded Systems and Software Engineering.*
