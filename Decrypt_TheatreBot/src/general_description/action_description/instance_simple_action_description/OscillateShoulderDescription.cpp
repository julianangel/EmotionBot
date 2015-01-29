/*
 * OscillateShoulderDescription.cpp
 *
 *  Created on: May 5, 2014
 *      Author: julian
 */

#include "OscillateShoulderDescription.h"

OscillateShoulderDescription::OscillateShoulderDescription() {
	this->action_name = "oscillate_shoulder";
	this->robot_parts_used.push_back("shoulder");
}

OscillateShoulderDescription::~OscillateShoulderDescription() {
}
list<shared_ptr<SimpleActionExecution> > OscillateShoulderDescription::Analyze(void){
	list<shared_ptr<SimpleActionExecution> > temp;
	shared_ptr<OscillateShoulderExecution>oscillate_execution(new OscillateShoulderExecution);
	oscillate_execution->setParameterDestination(this->parameter_destination);
	if(this->parameter_translation != NULL){
		oscillate_execution->setParameterTranslation(this->parameter_translation);
	}
	temp.push_back(oscillate_execution);
	return temp;
}
void OscillateShoulderDescription::setParameterPointPosition(
		shared_ptr<PointPositionParameter> parameter_destination){
	this->parameter_destination = parameter_destination;
}
shared_ptr<PointPositionParameter> OscillateShoulderDescription::getParameterPosition(){
	return this->parameter_destination;
}
void OscillateShoulderDescription::setParameterTranslation(
		shared_ptr<ParameterTranslation> parameter_translation){
	this->parameter_translation = parameter_translation;
}
shared_ptr<ParameterTranslation> OscillateShoulderDescription::getParameterTranslation(){
	return this->parameter_translation;
}

