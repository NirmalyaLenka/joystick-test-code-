// Joystick Test — Arduino Zero / SAMD21 (ATSAMD21G18)
// Wiring: VCC->3.3V, GND->GND, VRX->A0, VRY->A1, SW->D2
// Uses SerialUSB (native USB port), not the programming port.

const int VRX = A0, VRY = A1, SW = 2;

void setup() {
  SerialUSB.begin(115200);
  while (!SerialUSB);               // wait for USB serial
  analogReadResolution(12);         // 12-bit: 0-4095
  pinMode(SW, INPUT_PULLUP);
  SerialUSB.println("Joystick Test: Arduino Zero (SAMD21)");
}

void loop() {
  int  x  = analogRead(VRX);
  int  y  = analogRead(VRY);
  bool sw = !digitalRead(SW);

  SerialUSB.printf("X:%4d  Y:%4d  BTN:%s\n", x, y, sw ? "PRESSED" : "open");
  delay(200);
}
