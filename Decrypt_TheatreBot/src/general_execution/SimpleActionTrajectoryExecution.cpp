/*
 * SimpleActionTrajectoryExecution.cpp
 *
 *  Created on: May 9, 2014
 *      Author: julian
 */

#include "SimpleActionTrajectoryExecution.h"

SimpleActionTrajectoryExecution::SimpleActionTrajectoryExecution() {
	//this->parameter_translation = NULL;
}

SimpleActionTrajectoryExecution::~SimpleActionTrajectoryExecution() {
	//delete this->parameter_translation;
}

void SimpleActionTrajectoryExecution::setParameterTranslation(
		shared_ptr<ParameterTranslation> parameter_translation){
	this->parameter_translation = parameter_translation;
}
shared_ptr<ParameterTranslation> SimpleActionTrajectoryExecution::getParameterTranslation(){
	return this->parameter_translation;
}

