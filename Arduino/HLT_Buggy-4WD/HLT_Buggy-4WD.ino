#include "HLT_PointXY.h"
#include "HLT_Motion.h"

// Motor 1
int pinDirA_1 = 4;
int pinDirB_1 = 7;
int pinSpeed_1 = 6;

// Motor 2
int pinDirA_2 = 13;
int pinDirB_2 = 12;
int pinSpeed_2 = 10;

// Motor 3
int pinDirA_3 = 2;
int pinDirB_3 = 3;
int pinSpeed_3 = 5;

// Motor 4
int pinDirA_4 = 11;
int pinDirB_4 = 8;
int pinSpeed_4 = 9; 

HLT_Motion motion;

void setup() {
  Serial.begin(57600);

  motion.setPinMotor1(pinDirA_1, pinDirB_1, pinSpeed_1);
  motion.setPinMotor2(pinDirA_2, pinDirB_2, pinSpeed_2);
  motion.setPinMotor3(pinDirA_3, pinDirB_3, pinSpeed_3);
  motion.setPinMotor4(pinDirA_4, pinDirB_4, pinSpeed_4);
  
  Serial.setTimeout(100); //default 1000, imposto 100 per rendere più veloce la lettura del comando tramite: Serial.readString();
}

void loop() {
  if (Serial.available() > 0) {
    // command = (x,y) ... 0 =< x <= 510 / 0 =< y <= 510
    String command = Serial.readString();
    Serial.println("command="+command);
    HLT_PointXY pointXY(command);
    if (!pointXY.isError()) {
      Serial.println("x = " + String(pointXY.getX()));
      Serial.println("y = " + String(pointXY.getY()));
  
      motion.moveBuggy(pointXY);
      if (motion.isError()) {
        motion.stopBuggy();
        Serial.println("point not valid: " + motion.getError());        
      }
    }
    else {
      motion.stopBuggy();
      Serial.println("command not valid: " + pointXY.getError());
    }
  }
}
