#include "HLT_Motion.h"

HLT_Motion::HLT_Motion() {
  _error == NULL;
}

bool HLT_Motion::isError() {
  return _error != NULL;
}

String HLT_Motion::getError() {
  return _error;
}

void HLT_Motion::setPinMotor1(int pinDirA, int pinDirB, int pinSpeed) {
  _pin_motor_1_dir_A = pinDirA;
  _pin_motor_1_dir_B = pinDirB;
  _pin_motor_1_speed = pinSpeed;
  
  setPinMotor(pinDirA, pinDirB, pinSpeed);
}

void HLT_Motion::setPinMotor2(int pinDirA, int pinDirB, int pinSpeed) {
  _pin_motor_2_dir_A = pinDirA;
  _pin_motor_2_dir_B = pinDirB;
  _pin_motor_2_speed = pinSpeed;
  
  setPinMotor(pinDirA, pinDirB, pinSpeed);
}

void HLT_Motion::setPinMotor3(int pinDirA, int pinDirB, int pinSpeed) {
  _pin_motor_3_dir_A = pinDirA;
  _pin_motor_3_dir_B = pinDirB;
  _pin_motor_3_speed = pinSpeed;
  
  setPinMotor(pinDirA, pinDirB, pinSpeed);
}

void HLT_Motion::setPinMotor4(int pinDirA, int pinDirB, int pinSpeed) {
  _pin_motor_4_dir_A = pinDirA;
  _pin_motor_4_dir_B = pinDirB;
  _pin_motor_4_speed = pinSpeed;
  
  setPinMotor(pinDirA, pinDirB, pinSpeed);
}

void HLT_Motion::moveBuggy(HLT_PointXY pointXY) {

  movement.calcolate(pointXY);

  //Motor 1-2 (Right)
  analogWrite(_pin_motor_1_speed, movement.getRightSpeed());
  analogWrite(_pin_motor_2_speed, movement.getRightSpeed());
  
  if (movement.getRightDirection() == HLT_Movement::FORWARD_DIRECTION) {
    digitalWrite(_pin_motor_1_dir_A, HIGH);
    digitalWrite(_pin_motor_1_dir_B, LOW);
    digitalWrite(_pin_motor_2_dir_A, LOW);
    digitalWrite(_pin_motor_2_dir_B, HIGH);
  }
  else{
    digitalWrite(_pin_motor_1_dir_A, LOW);
    digitalWrite(_pin_motor_1_dir_B, HIGH);
    digitalWrite(_pin_motor_2_dir_A, HIGH);
    digitalWrite(_pin_motor_2_dir_B, LOW);
  }

  //Motor 3-4 (Left)
  analogWrite(_pin_motor_3_speed, movement.getLeftSpeed());
  analogWrite(_pin_motor_4_speed, movement.getLeftSpeed());
  
  if (movement.getLeftDirection() == HLT_Movement::FORWARD_DIRECTION) {
    digitalWrite(_pin_motor_3_dir_A, HIGH);
    digitalWrite(_pin_motor_3_dir_B, LOW);  
    digitalWrite(_pin_motor_4_dir_A, LOW);
    digitalWrite(_pin_motor_4_dir_B, HIGH);
  }
  else {
    digitalWrite(_pin_motor_3_dir_A, LOW);
    digitalWrite(_pin_motor_3_dir_B, HIGH);  
    digitalWrite(_pin_motor_4_dir_A, HIGH);
    digitalWrite(_pin_motor_4_dir_B, LOW);
  }
}

void HLT_Motion::stopBuggy() {
  //Motor 1-2 (Right)
  analogWrite(_pin_motor_1_speed, 0);  
  analogWrite(_pin_motor_2_speed, 0);  
  //Motor 3-4 (Left)
  analogWrite(_pin_motor_3_speed, 0);
  analogWrite(_pin_motor_4_speed, 0);
}

void HLT_Motion::setPinMotor(int pinDirA, int pinDirB, int pinSpeed) {
  pinMode(pinDirA,OUTPUT);
  pinMode(pinDirB,OUTPUT);
  pinMode(pinSpeed,OUTPUT);
}
