#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(10, 11);
char msg;

char call;
bool pass = false;
bool pass2 = false;
String passwordentered;
String message;
#include <Keypad.h>

const byte ROWS = 4; /* four rows */
const byte COLS = 4; /* four columns */
/* define the symbols on the buttons of the keypads */
char hexaKeys[ROWS][COLS] =
{
  {'0', '1', '2', '3'},
  {'4', '5', '6', '7'},
  {'8', '9', 'A', 'B'},
  {'C', 'D', 'E', 'F'}
};
byte rowPins[ROWS] = {3, 2, 1, 0}; /* connect to the row pinouts of the keypad */
byte colPins[COLS] = {7, 6, 5, 4}; /* connect to the column pinouts of the keypad */

/* initialize an instance of class NewKeypad */
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  mySerial.println("setup done");
//  lcd.init();
//  lcd.backlight();
//  delay(1000);
//  enterpassword();
//  lcd.print("ENTER PASSWORD");
//  delay(5000);
//  ReceiveMessage();
  Serial.print("tgbd");
}

void loop()
{
  if (mySerial.available() > 0)
  {

Serial.print("loopd");
    message = mySerial.readString();
  Serial.print("loopd");
    delay(1000);
    if (message.indexOf("123") > -1)
    {
      Serial.println("Correct");
      lcd.clear();
      lcd.setCursor(0, 0);
      Serial.println("here");
      lcd.print("CORRECT PASSWORD");
      pass = true;
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(400);  // Delay of 1000 milli seconds or 1 second
      mySerial.println("AT+CMGS=\"+919305998038\"\r"); // Replace x with mobile number
      delay(400);
      mySerial.println("Correct password");// The SMS text you want to send
      delay(400);
      mySerial.println((char)26);// ASCII code of CTRL+Z
      delay(400);
      Serial.println("correct password");
      lcd.clear();

    }
  }
  while (pass)
  {
  if (Serial.available()>0)
   switch(Serial.read())
  {
  case 's':
      SendMessage();
           break;

  }
    

    char customKey = customKeypad.getKey();
    if (customKey == '4')
    { // PRESS BUTTON 2
      Serial.println("You have enabled calling feature");
      Serial.println("Press A for making a call, B for redial, C for hangup call, D for receive call");
      pass2 = true;
      while (pass2)
      {
        char innerCustomKey = customKeypad.getKey(); // Get the key press once

        if (innerCustomKey != NO_KEY) { // Ensure a key is pressed
          Serial.println(innerCustomKey); // Print the pressed key for debugging

          switch (innerCustomKey) {
            case 'C': // PRESS BUTTON A
              Serial.println("calling");
              MakeCall();
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("CALLING...");
              break;
            case 'D': // PRESS BUTTON B
              RedialCall();
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("REDIALING...");
              break;
            case 'E': // PRESS BUTTON C
              HangupCall();
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("HANGING UP...");
              break;
            case 'F': // PRESS BUTTON D
              ReceiveCall();
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("RECEVING CALL...");
              break;
            case '7':// PRESS BUTTON 0
              pass2 = false;
          }
        }
      }
    }
    else if (customKey == '6')//PRESS BUTTON 8
    {
      Serial.println("in prblm stastement 2");

      twowaycommunicationforsending();
      Serial.println("MESSAGE SENT TO BOARD 2");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("MESSAGE SENT");
    }


    else if (customKey == 'D')// press button B
    {

      twowaycommunicationforrecieving();

    }
  

  else if (customKey == 'C')// press button A
  {

    //FOR PART 3
    mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
    delay(400);  // Delay of 1000 milli seconds or 1 second
    mySerial.println("AT+CMGS=\"+918091410524\"\r"); // BOARD 2 GSM NUMBER anuj
    delay(400);
    mySerial.println("GSM MESSGE HERE ");// The SMS text you want to send
    delay(400);
    mySerial.println((char)26);// ASCII code of CTRL+Z
    delay(400);







  }


}
}


//.............................................................................................
void enterpassword()
{
  //for two way communication we are
  mySerial.println("AT+CMGF=1");
  delay(400);
  mySerial.println("AT+CMGS=\"+919305998038\"\r");//shubham mobile
  delay(400);
  mySerial.println("enter password for BOARD 1");
  Serial.println("enter password for BOARD 1");
  delay(400);
  mySerial.println((char)26);
  delay(400);


}
//...........................................................................................
void twowaycommunicationforsending()
{
  mySerial.println("AT+CMGF=1");
  delay(400);
  mySerial.println("AT+CMGS=\"+918091410524\"\r");//other gsm number here anuj
  delay(400);
  mySerial.println("board 1 to board 2 come in");
  delay(400);
  mySerial.println((char)26);
  delay(400);
}
//................................................................................................
void twowaycommunicationforrecieving()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
  if (mySerial.available() > 0)
  {
    msg = mySerial.read();
    Serial.print(msg);
  }
}
//......................................................................................................
void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(400);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918091410524\"\r"); //  another gsm anuj
  delay(400);
  mySerial.println("hola!!");// The SMS text you want to send
  delay(400);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(400);
  Serial.println("gr");
}
//...........................................................................................................
void ReceiveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
  if (mySerial.available() > 0)
  {
    msg = mySerial.read();
    Serial.print(msg);
  }
}
//....................................................................................................
void MakeCall()
{
  mySerial.println("ATD+919305998038;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println("Calling  "); // print response over serial port
  delay(1000);
}
//..............................................................................................

void HangupCall()
{
  mySerial.println("ATH");
  Serial.println("Hangup Call");
  delay(1000);
}
//............................................................................................
void ReceiveCall()
{
  mySerial.println("ATA");
  delay(1000);
  {
    call = mySerial.read();
    Serial.print(call);
  }
}
//.................................................................................................
void RedialCall()
{
  mySerial.println("ATDL");
  Serial.println("Redialing");
  delay(1000);
}
