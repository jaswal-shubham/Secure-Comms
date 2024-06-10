#include <Arduino.h>

// Function to calculate parity bits
void calculateParityBits(int* data, int* parityBits) {
    // Calculate parity bits
    parityBits[0] = (data[10] + data[9] + data[7] + data[6] + data[4] + data[2] + data[0]) % 2;
    parityBits[1] = (data[10] + data[8] + data[7] + data[5] + data[4] + data[1] + data[0]) % 2;
    parityBits[2] = (data[9] + data[8] + data[7] + data[3] + data[2] + data[1] + data[0]) % 2;
    parityBits[3] = (data[6] + data[5] + data[4] + data[3] + data[2] + data[1] + data[0]) % 2;
}

// Function to encode 11-bit data using a 15,11 Hamming code
void hammingEncode(int* data, int* encodedData) {
    // Calculate parity bits
    int parityBits[4];
    calculateParityBits(data, parityBits);

    // Append parity bits to form the complete 15-bit codeword
    encodedData[0] = data[0];
    encodedData[1] = data[1];
    encodedData[2] = data[2];
    encodedData[3] = data[3];
    encodedData[4] = data[4];
    encodedData[5] = data[5];
    encodedData[6] = data[6];
    encodedData[7] = parityBits[3];
    encodedData[8] = data[7];
    encodedData[9] = data[8];
    encodedData[10] = data[9];
    encodedData[11] = parityBits[2];
    encodedData[12] = data[10];
    encodedData[13] = parityBits[1];
    encodedData[14] = parityBits[0];
}

void setup() {
    Serial.begin(9600); // Start serial communication
}

void loop() {
    if (Serial.available() > 0) { // Check if there's data available to read
        String inputString = Serial.readStringUntil('\n'); // Read input from Serial Monitor

        int inputLength = inputString.length();
       // Serial.println(inputLength);
        int nearestFactorTo88 = 88 * (inputLength / 88);
        //Serial.println(nearestFactorTo88);
        int data[nearestFactorTo88];

        // Convert input string to integer array
        for (int i = 0; i < nearestFactorTo88; ++i) {
            data[i] = inputString.charAt(i) - '0';
            //Serial.print(data[i]);
        }


        // // Calculate total number of bits
        int totalBits = 120;
        int r=4;

        //  Encode data using Hamming code
        int encodedData[totalBits];
        for (int i = 0; i < nearestFactorTo88; i+=11) {
            int dataChunk[11];
            int e[15];
            for (int j = 0; j < 11; ++j) {
                dataChunk[j] = data[i  + j];
            }
            hammingEncode(dataChunk, e);
            int turn =i/11;
            for(int j=0;j<15;j++)
            {
              encodedData[15*turn+j]=e[j];
            }
        }
          
       // Print the encoded data
       for (int i = 0; i < totalBits; ++i) {
            //Serial.print(encodedData[i]);
            // Serial.print(" ");
            // Serial.println( i);
            
        }

        Serial.println();
        int x=0,groups_passed=0;
        int filled =0;
        int chunks=8;
        int final_data[120];
        while(filled<120)
        {
          final_data[filled]= encodedData[x];
          filled++;
          x+=15;
          if(x>=120)
          {
            groups_passed++;
            x=groups_passed;
          }
        }

       for (int i = 0; i < totalBits; ++i) {
            Serial.print(final_data[i]);
      //       // Serial.print(" ");
      //       // Serial.println( i);
            
        }
        // Clear input buffer
        while (Serial.available() > 0) {
            Serial.read();
        }
    
    }}