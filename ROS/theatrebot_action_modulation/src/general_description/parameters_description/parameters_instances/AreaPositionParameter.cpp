///////////////////////////////////////////////////////////
//  AreaPosition.cpp
//  Implementation of the Class AreaPosition
//  Created on:      01-abr-2014 05:53:23 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#include "AreaPositionParameter.h"


AreaPositionParameter::AreaPositionParameter(){

}



AreaPositionParameter::~AreaPositionParameter(){

}


string AreaPositionParameter::getAreaType(){

	return  this->area_type;
}


void AreaPositionParameter::setAreaType(string area_type){

	this->area_type = area_type;
}
float AreaPositionParameter::getDistanceToDesirePosition(float robot_poistion){
	return 0;
}
