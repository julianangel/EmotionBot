#include "TheatreUpperPart.h"

TheatreUpperPart::TheatreUpperPart(){
	left = 45;
	center = 40;
	right = 45;	
	this->attach();
}

void TheatreUpperPart::attach(){
	leftServo.attach(3);
        leftServo.write(left);
	centralServo.attach(5);
	centralServo.write(center);
	rightServo.attach(2);
        rightServo.write(right);
}

int TheatreUpperPart::getLeft(){
	return left;
}

int TheatreUpperPart::getCenter(){
	return center;
}

int TheatreUpperPart::getRight(){
	return right;
}

void TheatreUpperPart::setLeft(int left){
	this->left = left;
	leftServo.write(left);
}

void TheatreUpperPart::setCenter(int center){
	this->center = center;
	centralServo.write(center);
}

void TheatreUpperPart::setRight(int right){
	this->right = right;
	rightServo.write(right);
}

void TheatreUpperPart::write(int left, int center, int right){
	this->left = left;
	this->center = center;
	this->right = right;	
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
