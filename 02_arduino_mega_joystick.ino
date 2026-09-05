// Joystick Test — Arduino Mega (ATmega2560)
// Wiring: VCC->5V, GND->GND, VRX->A0, VRY->A1,SW->D22

#define VRX_PIN  A0
#define VRY_PIN  A1
#define SW_PIN   22

void setup() {
  Serial.begin(115200);
  pinMode(SW_PIN, INPUT_PULLUP);
  Serial.println("Joystick Test: Arduino Mega");
  Serial.println("X\tY\tBTN");
}

void loop() {
  int  x  = analogRead(VRX_PIN);
  int  y  = analogRead(VRY_PIN);
  bool sw = !digitalRead(SW_PIN);

  Serial.printf("X:%4d  Y:%4d  BTN:%s\n", x, y, sw ? "PRESSED" : "open");
  delay(200);
}
