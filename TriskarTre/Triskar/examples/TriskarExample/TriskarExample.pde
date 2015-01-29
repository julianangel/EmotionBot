/*
  Example code for the MC33887 Library.
  Created by Martino Migliavacca, August 2, 2013.
  Released into the public domain.
*/

#include <Triskar.h>
#include <MC33887.h>

MC33887 m1(9, 2, 3);
MC33887 m2(10, 4, 5);
MC33887 m3(11, 6, 7);
Triskar triskar(m1, m2, m3);

int pwm = 0;
int diff = 10;

void setup() {
  triskar.stop();
}

void loop()  {
  triskar.run(0, ((float)(pwm)) / 255, 0);

  pwm = pwm + diff;

  if (pwm <= -255 || pwm >= 255) {
    diff = -diff ; 
  }
  
  delay(10);
}
