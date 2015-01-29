///////////////////////////////////////////////////////////
//  ParameterTime.cpp
//  Implementation of the Class ParameterTime
//  Created on:      01-abr-2014 05:53:25 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#include "ParameterTime.h"


ParameterTime::ParameterTime(){
	this->time_value = 0;
}



ParameterTime::~ParameterTime(){

}

float ParameterTime::getTimeValue(){

	return this->time_value;
}


void ParameterTime::setTimeValue(float time_value){

	this->time_value = time_value;
}
