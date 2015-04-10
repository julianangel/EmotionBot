#include "TheatreUpperPart.h"

TheatreUpperPart::TheatreUpperPart(){
	left_max = 155;
	center_max = 88;
	right_max = 170;
	left_min = 95;
	center_min = 25;
	right_min = 100;
	//155 front back 95	
	left_base = 115;
	//25 front back 88
	center_base = 55;
	//back 170 front 100
	right_base = 145;	
	left = left_base;
	center = center_base;
	right = right_base;	
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

void TheatreUpperPart::initServo(){
	left = left_base;
	center = center_base;
	right = right_base;
	leftServo.write(this->left);
	centralServo.write(this->center);
	rightServo.write(this->right);
}
int TheatreUpperPart::getLeft(){
	return left-left_base;
}

int TheatreUpperPart::getCenter(){
	return center_base-center;
}

int TheatreUpperPart::getRight(){
	return right-right_base;
}

void TheatreUpperPart::setLeft(int left){
	this->left = left +left_base;
	if(this->left>left_max){
		this->left = left_max;	
	}else if(this->left < left_min){
		this->left = left_min;
	}
	leftServo.write(this->left);
}

void TheatreUpperPart::setCenter(int center){
	this->center = center_base - center;
	if(this->center > center_max){
		this->center = center_max;	
	}else if(this->center < center_min){
		this->center = center_min;
	}
	centralServo.write(this->center);
}

void TheatreUpperPart::setRight(int right){
	this->right = right + right_base;
	if(this->right > right_max){
		this->right = right_max;
	}else if(this->right < right_min){
		this->right = right_min;
	}
	rightServo.write(this->right);
}

void TheatreUpperPart::write(int left, int center, int right){
	this->left = left +left_base;
	if(this->left>left_max){
		this->left = left_max;	
	}else if(this->left < left_min){
		this->left = left_min;
	}
	this->center = center + center_base;
	if(this->center > center_max){
		this->center = center_max;	
	}else if(this->center < center_min){
		this->center = center_min;
	}
	this->right = right + right_base;
	if(this->right > right_max){
		this->right = right_max;
	}else if(this->right < right_min){
		this->right = right_min;
	}	
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
