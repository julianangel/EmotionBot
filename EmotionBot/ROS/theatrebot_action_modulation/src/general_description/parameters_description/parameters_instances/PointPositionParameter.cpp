///////////////////////////////////////////////////////////
//  PointPosition.cpp
//  Implementation of the Class PointPosition
//  Created on:      01-abr-2014 05:53:26 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#include "PointPositionParameter.h"


PointPositionParameter::PointPositionParameter(){
	this->x_position = 0;
	this->y_position = 0;
	this->theta_position = 0;
}



PointPositionParameter::~PointPositionParameter(){

}


float PointPositionParameter::getXPosition(){

	return this->x_position;
}


void PointPositionParameter::setXPosition(float x_position){

	this->x_position = x_position;
}


float PointPositionParameter::getYPosition(){

	return this->y_position;
}


void PointPositionParameter::setYPosition(float y_position){

	this->y_position = y_position;
}


float PointPositionParameter::getThetaPosition(){

	return this->theta_position;
}


void PointPositionParameter::setThetaPosition(float theta_position){

	this->theta_position = theta_position;
}


void PointPositionParameter::setPointPosition(float x_position, float y_position,float theta_poisition){

	this->x_position = x_position;
	this->y_position = y_position;
	this->theta_position = theta_poisition;
}

float PointPositionParameter::getDistanceToDesirePosition(float robot_poistion){
	return 0;
}
