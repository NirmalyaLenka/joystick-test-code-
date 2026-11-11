# Joystick Input Test Collection

[![C](https://img.shields.io/badge/C-source-00599C?logo=c&logoColor=white)](https://en.cppreference.com/w/c)
[![C++](https://img.shields.io/badge/C%2B%2B-source-00599C?logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![Python](https://img.shields.io/badge/Python-MicroPython%20examples-3776AB?logo=python&logoColor=white)](https://www.python.org/)

Small, independent examples for reading a two-axis analog joystick and its push button on several microcontroller platforms. Most examples print raw X/Y readings and button state to a serial console; the ESP32-specific `joystick_esp32.ino` also classifies movement using simple thresholds.

These files are **separate platform examples**, not one application that runs on every board. Read the comments at the top of the exact file you intend to use before wiring or compiling it.

## What is included

- Raw X-axis and Y-axis ADC readings where the target has two suitable analog inputs.
- Active-low joystick push-button reading using an internal pull-up where configured.
- Serial output for quick wiring and input diagnostics.
- Examples spanning Arduino-compatible boards, ESP8266, ESP32, Raspberry Pi Pico, STM32, AVR, PIC, Teensy, nRF52840, SAMD21 and LPC1768.
- A dedicated ESP32 raw-input diagnostic sketch and a separate ESP32 direction-reporting sketch.

## Hardware and tools

### Basic parts

| Item | Status | Notes |
|---|---|---|
| One supported development board or target MCU | Required | Choose one that matches the example you will run. |
| KY-023 / HW-504-style two-axis joystick module | Required for the supplied wiring examples | Check the labels on your module; pin order can vary. |
| Jumper wires and a suitable breadboard or connector | Required | Use a common ground between module and board. |
| USB data cable and the board's programming/serial interface | Usually required | Bare MCUs may need a programmer or USB-to-UART adapter. |
| Board-specific programmer/debugger or USB-to-UART adapter | Conditional | Examples include ST-Link for STM32 and an appropriate serial adapter for bare AVR/PIC targets. |

No single universal BOM covers all targets: supply voltage, programmer, compiler and serial interface depend on the selected board. The parts above describe the minimum common setup, not a claim that every target has been physically assembled or tested.

### Platform and file guide

| File | Target / environment | Output or important note |
|---|---|---|
| `01_arduino_uno_joystick.ino` | Arduino Uno / AVR | Serial Monitor at **9600 baud** |
| `02_arduino_mega_joystick.ino` | Arduino Mega / AVR | Serial Monitor at **115200 baud** |
| `03_arduino_nano_joystick.ino` | Classic Arduino Nano / AVR | Serial Monitor at **9600 baud** |
| `04_esp32_joystick.ino` | ESP32 Arduino core | X/Y ADC and button; **115200 baud** |
| `05_esp8266_joystick.ino` | ESP8266 NodeMCU Arduino core | Reads X and button only; one onboard ADC channel |
| `06_rpi_pico_joystick.py` | Raspberry Pi Pico / MicroPython | Run from the MicroPython REPL |
| `07_stm32_bluepill_joystick.c` | STM32F103 / STM32 HAL | Integration snippet; requires CubeMX/HAL setup |
| `08_stm32_micropython_joystick.py` | Pyboard-style STM32 / MicroPython | Uses `pyb`; pin names are board-specific |
| `09_atmega32_joystick.c` | ATmega32 / AVR-GCC | Bare-metal C; UART output at about **9600 baud** |
| `10_pic16f877a_joystick.c` | PIC16F877A / MPLAB XC8 | Bare-metal C; configured for a **20 MHz** HS oscillator |
| `11_teensy40_joystick.ino` | Teensy 4.0 | Arduino-compatible; **115200 baud** |
| `12_nrf52840_joystick.ino` | Adafruit nRF52840 Feather / Arduino core | Board-specific analog reference and pin aliases |
| `13_samd21_arduino_zero_joystick.ino` | Arduino Zero / SAMD21 | Uses native USB `SerialUSB` |
| `14_lpc1768_mbed_joystick.cpp` | NXP LPC1768 / classic mbed OS 2 API | Legacy mbed API; not intended as a modern Mbed OS 6 drop-in |
| `15_attiny85_joystick.c` | ATtiny85 / AVR-GCC | Bit-banged 9600-baud TX; requires correct clock/fuse setup |
| `joystick_esp32.ino` | ESP32 Arduino core | Raw readings plus LEFT/RIGHT/UP/DOWN/CENTER thresholds |
| `joystick_raw_test.ino` | ESP32 Arduino core | Minimal raw-input diagnostic |

## Wiring

### ESP32 examples

The following map applies to `04_esp32_joystick.ino`, `joystick_esp32.ino` and `joystick_raw_test.ino`.

| Joystick module | ESP32 |
|---|---|
| VCC / + | 3V3 |
| GND | GND |
| VRX / X | GPIO 34 |
| VRY / Y | GPIO 35 |
| SW | GPIO 32 |

GPIO 34 and GPIO 35 are input-only on the classic ESP32 and are suitable for ADC input. GPIO 32 is configured as an input with pull-up; the switch is treated as **active LOW**.

**Voltage safety:** do not feed a 5 V analog signal into an ESP32, ESP8266, Pico, STM32, SAMD21, nRF52840 or other 3.3 V-only input. Power the joystick from 3.3 V for these examples unless the exact board and module specifications establish a different safe arrangement.

### Other boards

Use the wiring comment at the top of the chosen source file. Pin names and ADC ranges differ between targets; do not copy the ESP32 map to another board.

Special cases:

- **ESP8266 NodeMCU:** this target has one ADC input, so the supplied sketch reports only X and the switch. Reading both axes needs an analog multiplexer or another supported ADC arrangement. On bare ESP8266 modules, the ADC input range may be lower than the NodeMCU development-board A0 range; verify the exact board before connecting the joystick.
- **STM32 HAL:** configure ADC1, USART1 and the switch GPIO in the STM32CubeMX project as appropriate; the C file is a function snippet, not a complete generated firmware project.
- **PIC16F877A:** the source assumes a 20 MHz HS oscillator and uses PORTB weak pull-ups for the active-low switch.
- **ATtiny85:** follow the source's physical-pin map and clock/fuse notes. Its serial TX is bit-banged on PB1 and requires a compatible USB-to-UART receiver.
- **Arduino Zero:** open the native USB serial port because the example uses `SerialUSB`.

## Getting started

1. Identify the exact board and runtime you have.
2. Choose **one** matching file from the platform table.
3. Read that file's wiring and configuration comments. Confirm input voltage limits before powering the module.
4. Install the matching toolchain:
   - Arduino IDE plus the correct board package for `.ino` examples.
   - MicroPython firmware and a serial/REPL tool for the Pico or STM32 MicroPython examples.
   - STM32CubeIDE/CubeMX and the matching STM32 HAL project for the Blue Pill snippet.
   - AVR-GCC and a suitable programmer for the ATmega32/ATtiny85 examples.
   - MPLAB X IDE and XC8 for the PIC16F877A example.
   - The appropriate legacy mbed environment for the LPC1768 example.
5. For Arduino sketches, place the selected `.ino` file in a sketch folder with the **same base name** (for example, `04_esp32_joystick/04_esp32_joystick.ino`) before compiling. This repository keeps multiple independent sketches at the root, so do not try to compile the entire root as one Arduino sketch.
6. Build/upload using the selected board's normal workflow. Open its serial console/REPL at the baud rate listed above where applicable.
7. Move the joystick through its range and press/release the switch. Confirm that both axes change and the button state toggles.

### ESP32 quick check

For a basic raw-input check, use `joystick_raw_test.ino`. For threshold-based direction text, use `joystick_esp32.ino`. Both use the ESP32 wiring table above and print at **115200 baud**. The center point and useful thresholds vary by module, ADC configuration and board; adjust them after observing actual readings.

## Reading the output

- Analog values should change as the stick moves; the numeric range depends on the MCU and ADC configuration.
- The switch is active LOW in these examples: **PRESSED** means the input reads low, and **open/idle/released** means it reads high.
- The joystick may not rest at exactly half the ADC range. Record its real center and endpoints before using fixed thresholds in a control application.
- The ESP32 direction sketch uses simple thresholds (<1000 and >3000). These are starting values for its assumed 12-bit readings, not a calibrated dead-zone algorithm.

## Troubleshooting

| Symptom | Checks |
|---|---|
| X or Y remains at an endpoint | Verify VCC/GND, the correct ADC pin and voltage range; test one axis at a time. |
| Button never changes | Confirm SW wiring, common ground and active-low logic. Ensure the selected source configures a pull-up or add the required external pull-up. |
| Readings are noisy or center drifts | Check power and wiring; measure the module's real center; consider averaging/filtering only after the basic wiring is correct. |
| Serial output is unreadable or absent | Match the baud rate, select the correct serial port, and check whether the board uses USB CDC, UART or a REPL. |
| ESP8266 Y value is missing | Expected for this example: the target has one ADC channel. Use a suitable analog multiplexer or another target with two ADC inputs. |
| A board example does not compile as-is | Check whether it is a standalone sketch or an integration snippet and install the matching board package/toolchain. The STM32 HAL file requires generated project setup. |
| PIC values appear incorrect | Confirm the 20 MHz oscillator, ADC pin configuration and serial adapter settings; the code assumes the specified hardware. |

## Repository layout

```text
.
├── 01_arduino_uno_joystick.ino
├── 02_arduino_mega_joystick.ino
├── 03_arduino_nano_joystick.ino
├── 04_esp32_joystick.ino
├── 05_esp8266_joystick.ino
├── 06_rpi_pico_joystick.py
├── 07_stm32_bluepill_joystick.c
├── 08_stm32_micropython_joystick.py
├── 09_atmega32_joystick.c
├── 10_pic16f877a_joystick.c
├── 11_teensy40_joystick.ino
├── 12_nrf52840_joystick.ino
├── 13_samd21_arduino_zero_joystick.ino
├── 14_lpc1768_mbed_joystick.cpp
├── 15_attiny85_joystick.c
├── joystick_esp32.ino
├── joystick_raw_test.ino
└── README.md
```

There are currently no checked-in build scripts, automated tests, CI workflows or separate BOM file in the repository tree. The hardware list above is therefore a quick-start parts guide, not a verified purchase list for every platform.

## License and maintenance

- **License:** no `LICENSE` file is present in the repository tree, so reuse and redistribution terms are not formally declared. Add a license file if you want to grant explicit permissions.
- **Code status:** these are examples for learning and bench diagnostics, not flight-critical or safety-rated input drivers.
- **Verification:** source-level review only for this maintenance pass. The examples have not all been compiled with their respective toolchains or tested on physical hardware.
- **Last updated:** 11 November 2026 — README accuracy pass and fixes to the Arduino Mega serial output and PIC16F877A ADC/UART setup.
- **Maintenance:** when changing a pin, clock, ADC resolution, serial interface or dependency, update the relevant source comment and this guide together.
