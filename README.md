
# Secure-Comms

This Project basically describes the use of GSM module Technology for sending and recieving calls and text.

1.	GSM-Based Voice Call Functionality:
○	Establish a reliable mechanism for Arduino devices to make and receive voice calls using GSM modules.
○	Write code to initiate, manage, and terminate calls .
○	Implement features for call control, such as answering, ending, and redialing.

2.	Two-Way Text Message Communication:
○	Establish a two-way texting functionality for sending and receiving text messages between the Arduino boards
○	You should also be able to change the communication rate(Baud rate).
○	Display the message transmission process on the Serial Monitor 
○	The Message will be a text file and will be unique for each and every team.

3.Security: Implement some cool security features like passwords or mutual verification.

4.User-Interface: Develop a form of User Interface like LCD display or Oled Display. 

5.Hamming Code Implementation for Error Correction: 
○	Normally hamming codes can identify a 2 bit error but only correct single bit errors per hamming block. However, you are to devise and implement a smart Hamming(15,11) block scheme as the channel encoding scheme such that it can handle four bit bursts. 

○	We will simulate burst errors of 4 bits not by tampering with the actual channel but by typing in an appropriately sized binary string(Str) into one of the arduino boards say Board1. Board one returns the channel encoded binary string which is to be transmitted, according to the hamming(15,11) scheme you have devised. Here the judges will artificially introduce 4 bit error bursts in the encoded binary string, which is transmitted to the other board, say Board2. Board2 identifies and corrects the errors using the corresponding channel decoding scheme and returns the original string Str. Remember that there is no actual tampering with the channel.

It Also describes the use of error detection and correction techniques where we modified the traditional Hamming code to correct upto 4 bit bursts intead of just one.

## Usage of encoder deoder

5.1. Enter your text in the text to binary file.(use only 11 characters including space).

5.2. The generated output will be an 88 bit stream which will be your input to the encoder file.

5.3. The output of your enocder file will be transmitted across the channel.You can manually introduce a 4 bit burst error here .

5.4. The corrupted data stream when given input to Decoder will provide you with 88 bit data stream again , which when given given input in binary to text file , will generate the original text meassage for you.

5.5. Despite of the four bit birsts at any significant position the output generated message will be free from any errors.
