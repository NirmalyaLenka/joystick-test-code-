# Joystick Test — Raspberry Pi Pico (MicroPython)
# Wiring: VCC->3.3V, GND->GND, VRX->GP26 (ADC0), VRY->GP27 (ADC1), SW->GP15

from machine import ADC, Pin
import utime

vrx = ADC(26)   # GP26 — ADC0
vry = ADC(27)   # GP27 — ADC1
sw  = Pin(15, Pin.IN, Pin.PULL_UP)

print("Joystick Test: Raspberry Pi Pico")
print("X\t\tY\t\tBTN")

while True:
    x   = vrx.read_u16()   # 0-65535
    y   = vry.read_u16()
    btn = "PRESSED" if not sw.value() else "open"
    print(f"X:{x:6d}  Y:{y:6d}  BTN:{btn}")
    utime.sleep_ms(200)
