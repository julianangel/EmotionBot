#include "TheatreUpperPart.h"

TheatreUpperPart::TheatreUpperPart(){
	this->attach();
}

void TheatreUpperPart::attach(){
	leftServo.attach(3);
        leftServo.write(45);
	centralServo.attach(5);
	centralServo.write(40);
	rightServo.attach(2);
        rightServo.write(45);
}

void TheatreUpperPart::write(int left, int center, int right){
	leftServo.write(left);
	//int temp = map(center,-180,180,1380,1620);
	//int temp = center;	
	centralServo.write(center);
	rightServo.write(right);
}

void TheatreUpperPart::detach(){
	leftServo.detach();
	centralServo.detach();
	rightServo.detach();
}

long TheatreUpperPart::map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}