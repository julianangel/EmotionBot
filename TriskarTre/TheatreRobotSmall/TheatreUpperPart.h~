/*
 * ThreatreUpperPart.h
 *
 *  Created on: Oct 9, 2014
 *      Author: julian
 */

#ifndef TheatreUpperPart_H_
#define TheatreUpperPart_H_

#include <Servo.h>	
class TheatreUpperPart{

public:
	TheatreUpperPart();
	void write(int left, int center, int right);
	void detach();
	void attach();
	int getLeft();
	int getCenter();
	int getRight();
	void setLeft(int left);
	void setCenter(int center);
	void setRight(int right);
private:
	int left;
	int center;
	int right;
	Servo leftServo;//pin 2
	Servo centralServo;//pin 3
	Servo rightServo;//pin 4
	long map(long x, long in_min, long in_max, long out_min, long out_max);

};
#endif /* TheatreUpperPart_H_ */
