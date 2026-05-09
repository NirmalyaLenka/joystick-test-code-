# Joystick Test — STM32 Pyboard / STM32F4xx (MicroPython)
# Wiring: VCC->3.3V, GND->GND, VRX->X19 (PA4), VRY->X20 (PA5), SW->X1 (PA0)

from pyb import ADC, Pin, delay

vrx = ADC(Pin('X19'))   # PA4
vry = ADC(Pin('X20'))   # PA5
sw  = Pin('X1', Pin.IN, Pin.PULL_UP)

print("Joystick Test: STM32 MicroPython (Pyboard)")
print("X\tY\tBTN")

while True:
    x   = vrx.read()    # 0-4095
    y   = vry.read()
    btn = "PRESSED" if not sw.value() else "open"
    print(f"X:{x:4d}  Y:{y:4d}  BTN:{btn}")
    delay(200)
