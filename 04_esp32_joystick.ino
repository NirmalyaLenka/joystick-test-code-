// Joystick Test — ESP32 (Arduino core)
// Wiring: VCC->3.3V, GND->GND, VRX->GPIO34, VRY->GPIO35, SW->GPIO32
// Note: GPIO34/35 are input-only pins — perfect for ADC

#define VRX_PIN  34
#define VRY_PIN  35
#define SW_PIN   32

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);    // 12-bit: 0-4095
  pinMode(SW_PIN, INPUT_PULLUP);
  Serial.println("Joystick Test: ESP32");
}

void loop() {
  int  x  = analogRead(VRX_PIN);
  int  y  = analogRead(VRY_PIN);
  bool sw = !digitalRead(SW_PIN);

  Serial.printf("X:%4d  Y:%4d  BTN:%s\n", x, y, sw ? "PRESSED" : "open");
  delay(100);
}
