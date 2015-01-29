/*
 * Quaternion.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: julian
 */

#include "Quaternion.h"

Quaternion::Quaternion() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Quaternion::~Quaternion() {
	// TODO Auto-generated destructor stub
}
void Quaternion::setX(float x){
	this->x = x;
}
float Quaternion::getX(){
	return this->x;
}
void Quaternion::setY(float y){
	this->y = y;
}
float Quaternion::getY(){
	return this->y;
}
void Quaternion::setZ(float z){
	this->z = z;
}
float Quaternion::getZ(){
	return this->z;
}
void Quaternion::setW(float w){
	this->w = w;
}
float Quaternion::getW(){
	return this->w;
}
void Quaternion::setQuaternion(float x,float y,float z,float w){
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

