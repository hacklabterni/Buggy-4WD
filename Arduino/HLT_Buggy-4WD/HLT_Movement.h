/*
  HLT_Movement.h - Library for flashing Buggy 4WD code.
  Created by Andrea Cimini, March 16, 2017.
  Released into the public domain.
*/
#ifndef HLT_Movement_h
#define HLT_Movement_h

#include "Arduino.h"
#include "HLT_PointXY.h"

class HLT_Movement
{
  public:
    const static int FORWARD_DIRECTION = 0;
    const static int BACKWARD_DIRECTION = 1;
  
    HLT_Movement();
    void calcolate(HLT_PointXY pointXY);
    int getRightSpeed();
    int getRightDirection();
    int getLeftSpeed();
    int getLeftDirection();    
    
  private:
    int MAX_SPEED = 255;    
    int MIN_SPEED = 100;
    
    int _rightSpeed;
    int _rightDirection;    
    int _leftSpeed;
    int _leftDirection;
        
    int normalizeSpeed(int curSpeed);
};

#endif
