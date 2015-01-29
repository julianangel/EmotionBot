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
  int _d2;
  int _in1;
  int _in2;
public:
	MC33887(int d2, int in1, int in2);
	MC33887();
	void setInfo(int d2, int in1, int in2);
	void set(int pwm);
	void stop(void);
};

#endif /* MC33887_h */
