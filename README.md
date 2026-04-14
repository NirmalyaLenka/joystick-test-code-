# ESP32 Joystick Test

## Overview

This project reads analog and digital input from a KY-023 joystick module connected to an ESP32 and prints the axis values, direction, and button state to the Serial Monitor.

---

## Hardware Required

- ESP32 development board
- KY-023 joystick module (or equivalent dual-axis joystick with push button)
- Jumper wires
- USB cable for power and programming

---

## Pin Connections

| Joystick Pin | ESP32 Pin | Description          |
|--------------|-----------|----------------------|
| VCC          | 3.3V      | Power supply         |
| GND          | GND       | Ground               |
| VRX          | GPIO 34   | X-axis analog input  |
| VRY          | GPIO 35   | Y-axis analog input  |
| SW           | GPIO 32   | Push button input    |

Note: GPIO 34 and 35 on ESP32 are input-only pins and are well suited for analog reading. Do not connect them to voltages above 3.3V.

---

## How It Works

The joystick module outputs two analog voltages representing the X and Y axis positions. When the stick is centered, both values sit near the midpoint of the ADC range (around 2048 on a 12-bit ADC). Moving the stick in any direction shifts the values toward 0 or 4095.

The push button built into the joystick is active LOW. When pressed, the SW pin is pulled to GND. The code uses INPUT_PULLUP on that pin so it reads HIGH at rest and LOW when pressed.

The sketch reads all three inputs every 200 milliseconds and prints them to the Serial Monitor at 115200 baud. It also determines and prints the current direction (LEFT, RIGHT, UP, DOWN, or CENTER) based on threshold comparisons.

---

## Direction Thresholds

| Condition         | Direction Reported |
|-------------------|--------------------|
| X value below 1000  | LEFT             |
| X value above 3000  | RIGHT            |
| Y value below 1000  | UP               |
| Y value above 3000  | DOWN             |
| All values in range | CENTER           |

These thresholds can be adjusted in the code depending on the specific joystick module used and how it is calibrated.

---

## Setup Steps

1. Connect the joystick module to the ESP32 according to the pin table above.
2. Open the Arduino IDE and install ESP32 board support if not already done.
3. Open the joystick_esp32.ino file.
4. Select your ESP32 board from Tools > Board.
5. Select the correct COM port from Tools > Port.
6. Upload the sketch.
7. Open Serial Monitor at 115200 baud to see live output.

---

## Expected Serial Output

```
X: 2048 | Y: 2047 | Button: RELEASED
Direction: CENTER
X: 312 | Y: 2050 | Button: RELEASED
Direction: LEFT
X: 2048 | Y: 2048 | Button: PRESSED
Button Pressed!
Direction: CENTER
```

---

## Troubleshooting

- If all values read 0 or 4095 constantly, check that VCC is connected to 3.3V and not 5V.
- If the button never registers, confirm the SW pin is connected to GPIO 32 and INPUT_PULLUP is set correctly.
- If direction readings seem inverted, swap the VRX and VRY connections or adjust the threshold conditions in the code.

---

## Possible Projects

**RC Car Controller**
Use the joystick to control a two-motor RC car over Wi-Fi or Bluetooth. The X-axis steers left and right while the Y-axis controls forward and reverse speed through PWM motor drivers such as the L298N or L9110S.

**Pan-Tilt Camera Mount**
Connect two servo motors to build a pan-tilt bracket for a camera or sensor. The X-axis controls the pan servo and the Y-axis controls the tilt servo. The button can toggle a photo capture or recording state via an attached camera module.

**Wireless Drone Controller**
Pair two ESP32 boards over ESP-NOW. One board reads the joystick and transmits X, Y, and button values. The other board on the drone translates those values into motor speed commands through an ESC or motor driver.

**OLED Menu Navigator**
Connect a small SSD1306 OLED display. Use the joystick to scroll through a menu system, select options with the button press, and build a standalone portable device such as a sensor dashboard or settings panel.

**Robot Arm Control**
Map the X and Y axes to two servo joints of a robotic arm. Add a second joystick for additional joints. The button can be used to open or close a servo-based gripper at the end of the arm.

**Bluetooth Game Controller**
Use the ESP32 Bluetooth HID library to make the ESP32 appear as a gamepad to a phone or PC. The joystick axes map to the left analog stick and the button maps to a gamepad button, allowing you to control games wirelessly.

**Tank or Differential Drive Robot**
Translate joystick X and Y values into left and right motor speeds using a mixing algorithm. Moving the stick forward drives both motors equally. Tilting sideways slows one motor and speeds up the other to steer.

**Motorized Camera Slider**
Drive a stepper motor along a camera slider rail using joystick direction. The Y-axis moves the carriage forward and backward at variable speeds based on how far the stick is pushed. The button can mark start and end points for automated runs.

---

## License

This project is released for open use. No restrictions apply.
