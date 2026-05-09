// Joystick Test — Teensy 4.0 (iMXRT1062)
// Wiring: VCC->3.3V, GND->GND, VRX->A0 (pin 14), VRY->A1 (pin 15), SW->D2

const int VRX = A0, VRY = A1, SW = 2;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);    // 12-bit: 0-4095
  analogReadAveraging(16);     // hardware averaging for cleaner readings
  pinMode(SW, INPUT_PULLUP);
  Serial.println("Joystick Test: Teensy 4.0");
}

void loop() {
  int  x  = analogRead(VRX);
  int  y  = analogRead(VRY);
  bool sw = !digitalRead(SW);

  Serial.printf("X:%4d  Y:%4d  BTN:%s\n", x, y, sw ? "PRESSED" : "open");
  delay(100);
}
