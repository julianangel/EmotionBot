/*
  Example code for the MC33887 Library.
  Created by Martino Migliavacca, August 2, 2013.
  Released into the public domain.
*/

#include <MC33887.h>

MC33887 m(9, 2, 3); // d2, in1, in2 pins

int pwm = 0;
int diff = 10;

void setup() {
  m.stop();
}

void loop() {
  m.set(pwm);

  pwm = pwm + diff;

  if (pwm <= -255 || pwm >= 255) {
    diff = -diff ; 
  }
  
  delay(10);
}
