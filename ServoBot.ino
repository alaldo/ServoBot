#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

SoftwareSerial BT(8,9);    // Define RX y TX pins of Bluetooth module

// Called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

/******* Knee movements to extend  *******/
void raiseFrontLeftKnee() {
  //Left front knee extended position
  pwm.setPWM(0,0,100);
}

void raiseBackLeftKnee() {
  //Left rear knee extended position
  pwm.setPWM(2,0,110);
}

void raiseFrontRightKnee() {
  //Right front knee extended position
  pwm.setPWM(4,0,400);
}

void raiseBackRightKnee() {
  //Right rear knee extended position
  pwm.setPWM(6,0,500);
}

void standUp() {
  raiseFrontLeftKnee();
  raiseBackLeftKnee();
  raiseFrontRightKnee();
  raiseBackRightKnee();
}
/******* End knee movements to extend *******/


/******* Knee movements to relax *******/
void lowerFrontLeftKnee() {
  //Left front knee extended position
  pwm.setPWM(0,0,280);
}

void lowerBackLeftKnee() {
  //Left rear knee extended position
  pwm.setPWM(2,0,300);
}

void lowerFrontRightKnee() {
  //Right front knee extended position
  pwm.setPWM(4,0,200);
}

void lowerBackRightKnee() {
  //Right rear knee extended position
  pwm.setPWM(6,0,300);
}

void sitDown() {
  lowerFrontLeftKnee();
  lowerBackLeftKnee();
  lowerFrontRightKnee();
  lowerBackRightKnee();
}
/******* End knee movements to relax *******/


/******* Left front femur movement *******/
void frontLeftForward() {
  //Right front femur forward position
  pwm.setPWM(1,0,180);
}

void frontLeftBackward() {
  //Right front femur back position
  pwm.setPWM(1,0,300);
}

void frontLeftCenter() {
  //Right front femur center position
  pwm.setPWM(1,0,250);
}
/******* End left front femur movement *******/


/******* Left rear femur movement *******/
void backLeftForward() {
  //Right front femur forward position
  pwm.setPWM(3,0,210);
}

void backLeftBackward() {
  //Femur delantero derecho posicion atras
  pwm.setPWM(3,0,330);
}

void backLeftCenter() {
  //Femur delantero derecho posicion centro
  pwm.setPWM(3,0,250);
}
/******* End left rear femur movement *******/


/******* Right front femur movement *******/
void frontRightForward() {
  //Right front femur forward position
  pwm.setPWM(5,0,410);
}

void frontRightBackward() {
  //Right front femur back position
  pwm.setPWM(5,0,230);
}

void frontRightCenter() {
  //Right front femur center position
  pwm.setPWM(5,0,300);
}
/******* End right front femur movement *******/


/******* Right rear femur movement *******/
void backRightForward() {
  //Femur delantero derecho posicion adelante
  pwm.setPWM(7,0,380);
}

void backRightBackward() {
  //Femur delantero derecho posicion atras
  pwm.setPWM(7,0,230);
}

void backRightCenter() {
  //Femur delantero derecho posicion centro
  pwm.setPWM(7,0,350);
}
/******* End right rear femur movement *******/

/******* Forward movement *******/
void goForward(int moveStatus) {
  switch(moveStatus) {
    case 1:
      frontLeftForward();
      break;
    case 2:
      backLeftForward();
      break;
    case 3:
      frontRightForward();
      break;
    case 4:
      backRightForward();
      break;
    default:
      break;
  }
}
/******* End forward movement *******/

void resetFemurs() {
  backRightCenter();
  frontRightCenter();
  backLeftCenter();
  frontLeftCenter();
}

void allForward() {
  frontLeftForward();
  backLeftForward();
  frontRightForward();
  backRightForward();
}

void allBackward() {
  frontLeftBackward();
  backLeftBackward();
  frontRightBackward();
  backRightBackward();
}

void setup()
{
  BT.begin(9600);       // We initialize the BT serial port (For AT 2 Mode)
  Serial.begin(9600);   // We initialize the serial port
  
  delay(10);
  
  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);

  resetFemurs();
}

int moveStatus = 0;

void loop()
{
  if(BT.available())    // If data arrives through the BT port, it is sent to the serial monitor
  {
    String order = BT.readString();
     Serial.write(BT.read());
     if(order == "up") {
      standUp();
     }
     
     if(order == "down") {
      resetFemurs();
      delay(500);
      sitDown();
     }
     
     if(order == "forward") {
      allForward();
      delay(500);
      allBackward();
      delay(500);
      resetFemurs();
     }

     if(order == "backward") {
      frontRightForward();
     }
  }
}
