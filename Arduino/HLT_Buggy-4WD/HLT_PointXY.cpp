#include "HLT_PointXY.h"

HLT_PointXY::HLT_PointXY(String command)
{
  _error == NULL;
  if (command != NULL && command.length() >= 0) {    
    JsonObject& root = jsonBuffer.parseObject(command);
    if (root.success()) {
      _x = ((long)root["x"]) - 255;
      _y = 255 - ((long)root["y"]);

      if (_x < -255 || _x > 255 || _y < -255 || _y > 255) 
        _error = "value out of range (0,510)";
    }
    else
      _error = "parseObject() failed";
  }
  else 
    _error = "command is empty";
}

int HLT_PointXY::getX()
{
  return _x;
}

int HLT_PointXY::getY()
{
  return _y;
}

bool HLT_PointXY::isError()
{
  return _error != NULL;
}

String HLT_PointXY::getError()
{
  return _error;
}


