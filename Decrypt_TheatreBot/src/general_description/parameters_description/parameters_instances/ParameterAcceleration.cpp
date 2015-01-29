///////////////////////////////////////////////////////////
//  ParameterAcceleration.cpp
//  Implementation of the Class ParameterAcceleration
//  Created on:      01-abr-2014 05:53:25 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#include "ParameterAcceleration.h"


ParameterAcceleration::ParameterAcceleration(){
	this->acceleration_x = 0;
	this->acceleration_y = 0;
	this->acceleration_theta = 0;
	this->acceleration_type = TypeAccelerationNone;
}

ParameterAcceleration::~ParameterAcceleration(){

}

float ParameterAcceleration::getAccelerationX(){

	return this->acceleration_x;
}


void ParameterAcceleration::setAccelerationX(float acceleration_x){

	this->acceleration_x = acceleration_x;
}


float ParameterAcceleration::getAccelerationY(){

	return this->acceleration_y;
}


void ParameterAcceleration::setAccelerationY(float acceleration_y){

	this->acceleration_y = acceleration_y;
}


float ParameterAcceleration::getAccelerationTheta(){

	return this->acceleration_theta;
}


void ParameterAcceleration::setAccelerationTheta(float acceleration_theta){

	this->acceleration_theta = acceleration_theta;
}


TypeAcceleration ParameterAcceleration::getAccelerationType(){

	return  acceleration_type;
}


void ParameterAcceleration::setAccelerationType(TypeAcceleration acceleration_type){

	this->acceleration_type = acceleration_type;
}


void ParameterAcceleration::setAcceleration(float acceleration_x,float acceleration_y,float acceleration_theta){

	this->acceleration_x = acceleration_x;
	this->acceleration_y = acceleration_y;
	this->acceleration_theta = acceleration_theta;
}
