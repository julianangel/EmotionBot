/*
  Triskar.cpp - Library for controlling the Triskar robot.
  Created by Martino Migliavacca, August 2, 2013.
  Released into the public domain.
	The espected velocities are in rad/s
  Modification made by Julian Angel
	-variables dth1, dth2 and dth2 now are global variables
	-add of new methods to get the points
	-change everything from meters to milimeters
*/

#include "Arduino.h"
#include "Triskar.h"


Triskar::Triskar(MC33887 & m1, MC33887 & m2, MC33887 & m3)
: _m1(m1), _m2(m2), _m3(m3) {
  _m1.stop();
  _m2.stop();
  _m3.stop();
}

float Triskar::getM1(){
	return dth1;	
}
float Triskar::getM2(){
	return dth2;
}
float Triskar::getM3(){
	return dth3;
}

float Triskar::get_SP_SCALE(){
     return _SP_SCALE;
}

void Triskar::runM(float m1, float m2, float m3){
  // Motor setpoints
  _m1.set((int) (m1 * _SP_SCALE));
  _m2.set((int) (m2 * _SP_SCALE));
  _m3.set((int) (m3 * _SP_SCALE));
}

void Triskar::run(float strafe, float forward, float angular) {
  
// Model parameters
#define _L        110.0f    // Wheel distance from body origin [mm]
#define _R        35.0f    // Wheel radius [mm]

#define _m1_R     (-1.0f / _R)
#define _mL_R     (-_L / _R)
#define _C60_R    (0.500000000f / _R)   // cos(60°) / R
#define _C30_R    (0.866025404f / _R)   // cos(30°) / R

  // Wheel angular speeds
  const float dx12 = _C60_R * strafe;
  const float dy12 = _C30_R * forward;
  const float dthz123 = _mL_R * angular;

  dth1 = dx12 - dy12 + dthz123;
  dth2 = dx12 + dy12 + dthz123;
  dth3 = _m1_R * strafe + dthz123;

  // Motor setpoints
  _m1.set((int) (dth1 * _SP_SCALE));
  _m2.set((int) (dth2 * _SP_SCALE));
  _m3.set((int) (dth3 * _SP_SCALE));
  
  /*Serial.print((int) (dth1 * _SP_SCALE));
  Serial.print(",");
  Serial.print((int) (dth2 * _SP_SCALE));
  Serial.print(",");
  Serial.println((int) (dth3 * _SP_SCALE));*/
}


void Triskar::stop(void) {
  _m1.stop();
  _m2.stop();
  _m3.stop();
}
