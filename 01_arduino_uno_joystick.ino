// Joystick Test — Arduino Uno (ATmega328P)
// Wiring: VCC->5V, GND->GND, VRX->A0, VRY->A1, SW->D2

#define VRX_PIN  A0
#define VRY_PIN  A1
#define SW_PIN   2

void setup() {
  Serial.begin(9600);
  pinMode(SW_PIN, INPUT_PULLUP);
  Serial.println("Joystick Test: Arduino Uno");
  Serial.println("X\tY\tBTN");
}

void loop() {
  int  x  = analogRead(VRX_PIN);   // 0-1023
  int  y  = analogRead(VRY_PIN);   // 0-1023
  bool sw = !digitalRead(SW_PIN);  // active LOW

  Serial.print("X: "); Serial.print(x);
  Serial.print("  Y: "); Serial.print(y);
  Serial.print("  BTN: "); Serial.println(sw ? "PRESSED" : "open");
  delay(200);
}
