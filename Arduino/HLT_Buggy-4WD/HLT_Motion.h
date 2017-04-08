/*
  HLT_Motion.h - Library for flashing HLT_Buggy-4WD code.
  Created by Andrea Cimini, March 16, 2017.
  Released into the public domain.
*/
#ifndef HLT_Motion_h
#define HLT_Motion_h

#include "Arduino.h"
#include "HLT_PointXY.h"
#include "HLT_Movement.h"

class HLT_Motion
{
  public:
    HLT_Motion();
    void setPinMotor1(int pinDirA, int pinDirB, int pinSpeed);
    void setPinMotor2(int pinDirA, int pinDirB, int pinSpeed);
    void setPinMotor3(int pinDirA, int pinDirB, int pinSpeed);
    void setPinMotor4(int pinDirA, int pinDirB, int pinSpeed);
    void moveBuggy(HLT_PointXY pointXY);
    void stopBuggy();
    
    bool isError();
    String getError();
    
  private:
    String _error;
    HLT_Movement movement;
    
    int _pin_motor_1_dir_A;
    int _pin_motor_1_dir_B;
    int _pin_motor_1_speed;
    int _pin_motor_2_dir_A;
    int _pin_motor_2_dir_B;
    int _pin_motor_2_speed;
    int _pin_motor_3_dir_A;
    int _pin_motor_3_dir_B;
    int _pin_motor_3_speed;
    int _pin_motor_4_dir_A;
    int _pin_motor_4_dir_B;
    int _pin_motor_4_speed;
    
    void setPinMotor(int pinDirA, int pinDirB, int pinSpeed);
};

#endif
