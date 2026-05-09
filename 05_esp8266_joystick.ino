// Joystick Test — ESP8266 NodeMCU
// Wiring: VCC->3.3V, GND->GND, VRX->A0, SW->D5 (GPIO14)
// IMPORTANT: ESP8266 has only ONE ADC channel (A0).
// To read both axes, use an analog multiplexer (e.g. CD4051/CD4052).

#define VRX_PIN  A0     // single ADC
#define SW_PIN   14     // D5 on NodeMCU

void setup() {
  Serial.begin(115200);
  pinMode(SW_PIN, INPUT_PULLUP);
  Serial.println("Joystick Test: ESP8266 NodeMCU");
  Serial.println("WARNING: Only X-axis readable. Add mux for Y-axis.");
}

void loop() {
  int  x  = analogRead(VRX_PIN);  // 0-1023
  bool sw = !digitalRead(SW_PIN);

  Serial.printf("X:%4d  BTN:%s\n", x, sw ? "PRESSED" : "open");
  delay(200);
}
