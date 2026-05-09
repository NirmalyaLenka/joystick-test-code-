// Joystick Test — nRF52840 Feather (Adafruit)
// Wiring: VCC->3.3V, GND->GND, VRX->A0 (P0.02), VRY->A1 (P0.03), SW->D5 (P1.08)

const int VRX = A0, VRY = A1, SW = 5;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);            // 12-bit SAR ADC: 0-4095
  analogReference(AR_INTERNAL_3_0);   // 3.0V internal reference
  pinMode(SW, INPUT_PULLUP);
  Serial.println("Joystick Test: nRF52840 Feather");
}

void loop() {
  int  x  = analogRead(VRX);
  int  y  = analogRead(VRY);
  bool sw = !digitalRead(SW);

  Serial.printf("X:%4d  Y:%4d  BTN:%s\n", x, y, sw ? "PRESSED" : "open");
  delay(150);
}
