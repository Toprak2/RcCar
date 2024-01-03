#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
 
char c = ' ';
int xPin=A0;
int yPin=A1;
int prevXPos;
int prevYPos;
bool sendData=false;

String formatValue(int value) {
  String strValue = String(abs(value));
  while (strValue.length() < 3) {
    strValue = "0" + strValue;
  }
  return (value < 0 ? "1" : "0") + strValue;
}
void setup() 
{
    // start the serial communication with the host computer
    Serial.begin(9600);
    Serial.println("Arduino with HC-05 is ready");
 
    // start communication with the HC-05 using 9600
    BTserial.begin(9600);  
    Serial.println("BTserial started at 9600");

    pinMode(xPin,INPUT);
    pinMode(yPin,INPUT);

    prevXPos=mapJoystickInput(analogRead(xPin));
    prevYPos=mapJoystickInput(analogRead(yPin));
}
 
void loop()
{
 
    //  // Keep reading from HC-05 and send to Arduino Serial Monitor
    // if (BTserial.available())
    // {  
    //     Serial.write(BTserial.read());
    // }
 
    // // Keep reading from Arduino Serial Monitor and send to HC-05
    // if (Serial.available())
    // {
    //     BTserial.write(Serial.read());  
    // }

    int xPosition=mapJoystickInput(analogRead(xPin));
    int yPosition=mapJoystickInput(analogRead(yPin));

    


    if(abs(xPosition-prevXPos)>=15){
      prevXPos=xPosition;     
      sendData=true;
    }
    
    if(abs(yPosition-prevYPos)>=15){
      prevYPos=yPosition;

      sendData=true;
    }

     
     
    if (sendData) {
      String dataToSend = formatValue(xPosition) + formatValue(yPosition);
      Serial.println(dataToSend); // Send the data
      BTserial.println(dataToSend);
      sendData=false;
    }
  
  
}

int mapJoystickInput(int inputValue){
  return inputValue-512;
}
