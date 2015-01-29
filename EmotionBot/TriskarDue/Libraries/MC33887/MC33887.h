/*
  MC33887.h - Library for controlling the Pololu MC33887 motor driver.
  Created by Martino Migliavacca, August 2, 2013.
  Released into the public domain.
*/

#ifndef MC33887_h
#define MC33887_h

#include "Arduino.h"

class MC33887
{
private:
  byte _d2;
  byte _in1;
  byte _in2;
public:
  MC33887(byte d2, byte in1, byte in2);
  void set(int pwm);
  void stop(void);
};

#endif /* MC33887_h */
