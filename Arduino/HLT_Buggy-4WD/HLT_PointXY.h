/*
  HLT_PointXY.h - Library for flashing Buggy 4WD code.
  Created by Andrea Cimini, March 16, 2017.
  Released into the public domain.
*/
#ifndef HLT_PointXY_h
#define HLT_PointXY_h

#include "Arduino.h"
#include <ArduinoJson.h>

class HLT_PointXY
{
  public:
    StaticJsonBuffer<200> jsonBuffer;
    
    HLT_PointXY(String command);
    int getX();
    int getY();
    bool isError();
    String getError();
    
  private:
    int _x;
    int _y;
    String _error;
};

#endif
