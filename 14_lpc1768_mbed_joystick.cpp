// Joystick Test — NXP LPC1768 (mbed OS 2 / Classic)
// Wiring: VCC->3.3V, GND->GND, VRX->p15 (ADC0.0), VRY->p16 (ADC0.1), SW->p5
// Add to your mbed project alongside main.cpp, or replace main().

#include "mbed.h"

AnalogIn  vrx(p15);
AnalogIn  vry(p16);
DigitalIn sw(p5);
Serial    serial(USBTX, USBRX);

int main() {
    serial.baud(115200);
    sw.mode(PullUp);
    serial.printf("Joystick Test: LPC1768\r\n");

    while (true) {
        float   x = vrx.read();    // 0.0 - 1.0 (normalised)
        float   y = vry.read();
        bool    b = !sw.read();    // active LOW

        serial.printf("X:%.3f  Y:%.3f  BTN:%s\r\n",
                      x, y, b ? "PRESSED" : "open");
        wait_ms(200);
    }
}
