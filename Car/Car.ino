#include <SoftwareSerial.h>
#include <AFMotor.h>

SoftwareSerial BTserial(14, 15); // RX | TX

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup()
{
pinMode(13, OUTPUT);
pinMode(11, OUTPUT); //Sets digital pin 11 as output pin
Serial.begin(9600);
BTserial.begin(9600); //Baud Rate for command Mode.
Serial.println("Enter AT commands!");

release();
setSpeed(200);

}

void loop()
{
  if (BTserial.available() >= 8) { // Check if there are at least 8 characters to read
    String dataReceived = BTserial.readStringUntil('\n'); // Read the incoming data

    String xStr = dataReceived.substring(0, 4); // Get the first 4 characters for x
    int xDirection = xStr.charAt(0) == '1' ? -1 : 1; // Determine the direction
    int x = parseValue(xStr); // Parse the x value

    String yStr = dataReceived.substring(4, 8); // Get the last 4 characters for y
    int yDirection = yStr.charAt(0) == '1' ? -1 : 1; // Determine the direction
    int y = parseValue(yStr); // Parse the y value

    // Map the x and y values from the range 0 to 512 to the range 0 to 255
    int xSpeed = map(x, 0, 512, 0, 255);
    int ySpeed = map(y, 0, 512, 0, 255);

    Serial.println(xSpeed);

    if(xSpeed<=10){
      setSpeed(0);
      release();
    }
    else {
      // Set the direction of the DC motors
      if (xDirection == 1) {
        forward();  
      } 
      else {
      // Set the x motor to go backward
      backward();
      }


      if(ySpeed<=10){

        setSpeed(xSpeed);

      }
      else {

        if(yDirection==1){
          motor2.setSpeed(xSpeed-mapYToX(ySpeed, xSpeed));
          motor3.setSpeed(xSpeed-mapYToX(ySpeed, xSpeed));

          motor1.setSpeed(xSpeed);
          motor4.setSpeed(xSpeed);
        }
        else {
          motor1.setSpeed(xSpeed-mapYToX(ySpeed, xSpeed));
          motor4.setSpeed(xSpeed-mapYToX(ySpeed, xSpeed));

          motor2.setSpeed(xSpeed);
          motor3.setSpeed(xSpeed);
        }
      }
      
    }

    



    // Set the speed of the DC motors
    // analogWrite(X_MOTOR_PIN, xSpeed);
    // analogWrite(Y_MOTOR_PIN, ySpeed);
  }


}

int parseValue(String str) {
  return str.substring(1).toInt(); // Return the last three characters as an integer
}

int mapYToX(int yValue,int xValue){
  return map(yValue, 0, 255, 0, xValue);
}

void setSpeed(int speed){
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);
  
}

void forward(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void backward(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);

}

void left(){
  motor1.run(RELEASE);
  motor4.run(RELEASE);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
}

void right(){
  motor1.run(FORWARD);
  motor4.run(FORWARD);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
}

void release(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
