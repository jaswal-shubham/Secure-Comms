#include <Arduino.h>

void setup() {
  Serial.begin(9600); // Start serial communication
}

void loop() {
  if (Serial.available()) { // Check if there's data available to read
    String inputString = Serial.readStringUntil('\n'); // Read input from Serial Monitor
    int inputLength = inputString.length();

    // Convert binary representation back to text
    String outputString = "";
    for (int i = 0; i < inputLength; i += 8) {
      char character = 0;
      for (int j = 0; j < 8; ++j) {
        character |= ((inputString[i + j] - '0') << (7 - j)); // Construct character from bits
      }
      outputString += character; // Append character to output string
    }

    Serial.println(outputString); // Print the output text

    // Clear input buffer
    while (Serial.available()) {
      Serial.read();
    }
  }
}
