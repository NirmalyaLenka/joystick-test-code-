#define VRX_PIN 34                                  // X-axis pin
#define VRY_PIN 35                                  // Y-axis pin
#define SW_PIN  32                                  // Button pin

int xValue = 0;                                     // X-axis value
int yValue = 0;                                     // Y-axis value
int swState = 0;                                    // Button state

void setup() {
  Serial.begin(115200);                             // Start serial
  pinMode(SW_PIN, INPUT_PULLUP);                    // Set button mode
}

void loop() {
  xValue = analogRead(VRX_PIN);                     // Read X-axis
  yValue = analogRead(VRY_PIN);                     // Read Y-axis
  swState = digitalRead(SW_PIN);                    // Read button

  Serial.print("X: ");                              // Print label
  Serial.print(xValue);                             // Print X value
  Serial.print(" | Y: ");                           // Print separator
  Serial.print(yValue);                             // Print Y value
  Serial.print(" | Button: ");                      // Print label
  Serial.println(swState == LOW ? "PRESSED" : "RELEASED"); // Button status

  if (xValue < 1000) {                              // Check left move
    Serial.println("Direction: LEFT");              // Print direction
  } else if (xValue > 3000) {                       // Check right move
    Serial.println("Direction: RIGHT");             // Print direction
  } else if (yValue < 1000) {                       // Check up move
    Serial.println("Direction: UP");                // Print direction
  } else if (yValue > 3000) {                       // Check down move
    Serial.println("Direction: DOWN");              // Print direction
  } else {                                          // No movement
    Serial.println("Direction: CENTER");            // Print center
  }

  if (swState == LOW) {                             // Button pressed
    Serial.println("Button Pressed!");              // Print press event
    delay(300);                                     // Debounce delay
  }

  delay(200);                                       // Loop delay
}
