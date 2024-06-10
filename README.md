
# Secure-Comms

This Project basically describes the use of GSM module Technology for sending and recieving calls and text.

// Milind Add your readme 

It Also describes the use of error detection and correction techniques where we modified the traditional Hamming code to correct upto 4 bit bursts intead of just one.




## Usage of encoder deoder

1. Enter your text in the text to binary file.(use only 11 characters including space).

2. The generated output will be an 88 bit stream which will be your input to the encoder file.

3. The output of your enocder file will be transmitted across the channel.You can manually introduce a 4 bit burst error here .

4. The corrupted data stream when given input to Decoder will provide you with 88 bit data stream again , which when given given input in binary to text file , will generate the original text meassage for you.

5. Despite of the four bit birsts at any significant position the output generated message will be free from any errors.