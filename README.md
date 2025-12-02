# ObstaLUX: Wi-Fi Controlled Car with Dynamic Obstacle Avoidance and Auto Light Control

**ObstaLUX** is a smart robotic vehicle prototype built on the NodeMCU (ESP8266) platform. It fuses manual control via a Wi-Fi web interface with autonomous safety features, including infrared-based obstacle detection and environment-adaptive lighting.

## Overview

Traditional remote-controlled cars often lack interactivity with their environment. ObstaLUX addresses this by creating a low-cost, IoT-enabled vehicle that allows seamless wireless control while preventing collisions and adapting to lighting conditions automatically.

## Features

* **Wi-Fi Control:** Remotely controllable via a web-based interface hosted on the NodeMCU.
* **Dynamic Obstacle Avoidance:** Uses an IR sensor to detect obstacles in real-time and automatically stops the vehicle to prevent collisions.
* **Automatic Headlights:** An LDR sensor monitors ambient light intensity; if the environment is dark (value < 200), the LED headlights turn on automatically.
* **Speed Control:** Adjustable motor speed via the web interface (levels 0–9).

## Hardware Architecture

The system relies on the following components:

* **Microcontroller:** NodeMCU (ESP8266)
* **Motor Driver:** L298N (Controls direction and speed of DC motors)
* **Sensors:**

  * IR Sensor (Obstacle detection)
  * LDR (Light intensity measurement)
* **Actuators:**

  * 2× DC Motors
  * LED (Headlight)
* **Power:** Battery Pack (Powers motors via L298N)

## Pin Configuration

| Component     | Label | NodeMCU Pin | Function                        |
| ------------- | ----- | ----------- | ------------------------------- |
| **L298N**     | ENA   | GPIO14 (D5) | Speed Control (Right Motor)     |
| **L298N**     | ENB   | GPIO12 (D6) | Speed Control (Left Motor)      |
| **L298N**     | IN1   | GPIO15 (D8) | Direction (Right Motor)         |
| **L298N**     | IN2   | GPIO13 (D7) | Direction (Right Motor)         |
| **L298N**     | IN3   | GPIO2 (D4)  | Direction (Left Motor)          |
| **L298N**     | IN4   | GPIO0 (D3)  | Direction (Left Motor)          |
| **IR Sensor** | OUT   | GPIO5 (D1)  | Obstacle Input (LOW = Detected) |
| **LDR**       | OUT   | A0          | Analog Light Input              |
| **LED**       | Anode | GPIO4 (D2)  | Headlight Output                |

## Software & Libraries

The project is programmed in **C++** using the Arduino IDE.

**Required Libraries:**

* `ESP8266WiFi.h`
* `WiFiClient.h`
* `ESP8266WebServer.h`

## Installation & Setup

1. **Assembly:** Connect the hardware components according to the Pin Configuration and circuit diagram.
2. **Flash Code:** Upload the `Project.ino` file to the NodeMCU.
3. **Connect:**

   * Power on the vehicle.
   * Connect your mobile or PC to the Wi-Fi Access Point (SSID: **"NodeMCU Car"**).
   * No password is required.
4. **Access Interface:** Open a web browser and navigate to IP address `192.168.4.1`.

## Control Commands

The web server listens for HTTP requests to control movement and speed.

| Command | Action                               |
| ------- | ------------------------------------ |
| **F**   | Move Forward                         |
| **B**   | Move Backward                        |
| **L**   | Turn Left                            |
| **R**   | Turn Right                           |
| **S**   | Stop Robot                           |
| **I**   | Move Forward Right                   |
| **G**   | Move Forward Left                    |
| **J**   | Move Backward Right                  |
| **H**   | Move Backward Left                   |
| **0–9** | Adjust Speed (0 = Low, 9 = Max/1023) |

## Working Mechanism

1. **Initialization:** The NodeMCU initializes the Web Server and sets PinModes.
2. **Command Handling:** When a user sends a command (e.g., "F" for Forward), the NodeMCU triggers the L298N motor driver.
3. **Safety Check:**

   * The IR sensor continuously checks for obstacles. If `digitalRead` returns LOW (obstacle detected), `stopRobot()` is executed immediately.
   * The LDR reads analog values (0–1023). If the value is greater than 200, the LED turns off; if below 200, it turns on.

## References

* **Video Demo:** [https://www.youtube.com/watch?v=AP_Nqc6u3fU](https://www.youtube.com/watch?v=AP_Nqc6u3fU)
* **Project Files:** [https://drive.google.com/drive/u/0/folders/1b0RVtNN4TE_0RgrC2sV9AcCecHgo2HKq](https://drive.google.com/drive/u/0/folders/1b0RVtNN4TE_0RgrC2sV9AcCecHgo2HKq)
