#include <Arduino.h>

// Function to calculate parity checker bits
void calculateParityBits(const int data[], int parityBits_checker[]) {
    parityBits_checker[0] = (data[12] + data[10] + data[8] + data[6] + data[4] + data[2] + data[0] + data[14]) % 2;
    parityBits_checker[1] = (data[12] + data[9] + data[8] + data[5] + data[4] + data[1] + data[0] + data[13]) % 2;
    parityBits_checker[2] = (data[10] + data[9] + data[8] + data[3] + data[2] + data[1] + data[0] + data[11]) % 2;
    parityBits_checker[3] = (data[6] + data[5] + data[4] + data[3] + data[2] + data[1] + data[0] + data[7]) % 2;
}

// Function to extract data
void extract_data(const int data[], int dataWord[]) {
    dataWord[0] = data[0];
    dataWord[1] = data[1];
    dataWord[2] = data[2];
    dataWord[3] = data[3];
    dataWord[4] = data[4];
    dataWord[5] = data[5];
    dataWord[6] = data[6];
    dataWord[7] = data[8]; 
    dataWord[8] = data[9];
    dataWord[9] = data[10];
    dataWord[10] = data[12];
}

// Function to decode 15-bit data using a 15,11 Hamming code
void hammingDecode(int data[], int DataWord[]) {
    // Calculate parity bits
    int parityBits_checker[4];
    calculateParityBits(data, parityBits_checker);

    // Checking for error
    if (parityBits_checker[0] + parityBits_checker[1] + parityBits_checker[2] + parityBits_checker[3] == 0) {
        extract_data(data, DataWord);
    } else {
        // Error correction
        int pos = pow(2, 3) * parityBits_checker[3] + pow(2, 2) * parityBits_checker[2] + pow(2, 1) * parityBits_checker[1] + parityBits_checker[0];
        int k = 1;
        for (int i = 14; i >= 0; i--) {
            if (k == pos) {
                data[i] = (data[i] == 0 ? 1 : 0);
                break;
            }
            k++;
        }
        // Extract corrected data
        extract_data(data, DataWord);
    }
}

void setup() {
    Serial.begin(9600);
}

void loop(){
    if(Serial.available() >0) {
     
    

     String inputString = Serial.readStringUntil('\n'); // Read input from Serial Monitor

        
       // Serial.println(inputLength);
        
        //Serial.println(nearestFactorTo88);
        int encoded[120];

        // Convert input string to integer array
        for (int i = 0; i < 120; ++i) {
            encoded[i] = inputString.charAt(i) - '0';
            
        }

    // Decode data
    int parts[8][15];
    int distributed = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 15; j++) {
            parts[i][j] = encoded[i + j*8];
        }
    }

    int v1[88];
    for (int i = 0; i < 8; i++) {
        int DataWord[11];
        int hello[15];
        for (int k=0;k<15;k++)
        {
          hello[k]=parts[i][k];
        }
        hammingDecode(hello, DataWord);
        for (int j = 0; j < 11; j++) {
            v1[i * 11 + j] = DataWord[j];
        }
    }

    // Print the decoded data
    for (int i = 0; i < 88; i++) {
        Serial.print(v1[i]);
    }
    
    Serial.println();

    // Wait for some time before processing the next input
    delay(1000);
    }
}