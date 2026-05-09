// Joystick Test — Arduino Nano (ATmega328P)
// Wiring: VCC->5V, GND->GND, VRX->A0, VRY->A1, SW->D4

const int VRX = A0, VRY = A1, SW = 4;

void setup() {
  Serial.begin(9600);
  pinMode(SW, INPUT_PULLUP);
  Serial.println("Joystick Test: Arduino Nano");
}

void loop() {
  int  x  = analogRead(VRX);
  int  y  = analogRead(VRY);
  bool sw = !digitalRead(SW);

  Serial.print("X: "); Serial.print(x);
  Serial.print("  Y: "); Serial.print(y);
  Serial.print("  BTN: "); Serial.println(sw ? "PRESSED" : "open");
  delay(200);
}
