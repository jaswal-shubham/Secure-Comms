#include <Arduino.h>

void setup() {
  Serial.begin(9600); // Start serial communication
}

void loop() {
  if (Serial.available()) { // Check if there's data available to read
    String inputString = Serial.readStringUntil('\n'); // Read input from Serial Monitor
    int inputLength = inputString.length();

    // Convert each character to binary representation and print
    for (int i = 0; i < inputLength; ++i) {
      char character = inputString.charAt(i);
      for (int j = 7; j >= 0; --j) {
        Serial.print((character >> j) & 1); // Extract each bit and print
      }
    }

    // Clear input buffer
    while (Serial.available()) {
      Serial.read();
    }
    Serial.println(); // Print newline character
  }
}
