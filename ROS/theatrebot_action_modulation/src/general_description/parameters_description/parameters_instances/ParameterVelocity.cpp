///////////////////////////////////////////////////////////
//  ParameterVelocity.cpp
//  Implementation of the Class ParameterVelocity
//  Created on:      01-abr-2014 05:53:26 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#include "ParameterVelocity.h"

ParameterVelocity::ParameterVelocity(){
	this->velocity_x = 0;
	this->velocity_y = 0;
	this->velocity_theta = 0;
}



ParameterVelocity::~ParameterVelocity(){

}


float ParameterVelocity::getVelocityX(){

	return this->velocity_x;
}


float ParameterVelocity::getVelocityY(){

	return this->velocity_y;
}


float ParameterVelocity::getVelocityTheta(){

	return this->velocity_theta;
}


void ParameterVelocity::setVelocityX(float velocity_x){

	this->velocity_x = velocity_x;
}


void ParameterVelocity::setVelocityY(float velocity_y){

	this->velocity_y = velocity_y;
}


void ParameterVelocity::setVelocityTheta(float velocity_theta){

	this->velocity_theta = velocity_theta;
}


void ParameterVelocity::setVelocity(float velocity_x,float velocity_y,float velocity_theta){

	this->velocity_x = velocity_x;
	this->velocity_y = velocity_y;
	this->velocity_theta = velocity_theta;
}
