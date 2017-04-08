#include "HLT_Movement.h"

HLT_Movement::HLT_Movement() {}

void HLT_Movement::calcolate(HLT_PointXY pointXY) {

  int x = abs(pointXY.getX());
  int y = abs(pointXY.getY());

  _leftSpeed = max(x,y);
  _leftDirection = FORWARD_DIRECTION;  

  _rightSpeed = abs(y-x);
  if ( y >= x) {
    _rightDirection = FORWARD_DIRECTION;    
  }
  else {
    _rightDirection = BACKWARD_DIRECTION;
  }

  if (pointXY.getX() < 0) {
    int tempSpeed = _leftSpeed;
    _leftSpeed = _rightSpeed;
    _rightSpeed = tempSpeed;

    if (x - y > 5) { // > 5 e not zero for gap
      _leftDirection  = (_leftDirection == FORWARD_DIRECTION ? BACKWARD_DIRECTION : FORWARD_DIRECTION);    
      _rightDirection = (_rightDirection == FORWARD_DIRECTION ? BACKWARD_DIRECTION : FORWARD_DIRECTION);    
    }
  }

  if (pointXY.getY() < 0) {
    _leftDirection  = (_leftDirection == FORWARD_DIRECTION ? BACKWARD_DIRECTION : FORWARD_DIRECTION);    
    _rightDirection = (_rightDirection == FORWARD_DIRECTION ? BACKWARD_DIRECTION : FORWARD_DIRECTION);    
  }
}

int HLT_Movement::getRightSpeed(){
  return normalizeSpeed(_rightSpeed);
}

int HLT_Movement::getRightDirection(){
  return _rightDirection;
}

int HLT_Movement::getLeftSpeed(){
  return normalizeSpeed(_leftSpeed);
}

int HLT_Movement::getLeftDirection(){
  return _leftDirection;
}

int HLT_Movement::normalizeSpeed(int curSpeed) {
  if (curSpeed <= MIN_SPEED)
    return 0;
  else if (curSpeed > MAX_SPEED)
    return MAX_SPEED;
  else
    return curSpeed;
}


