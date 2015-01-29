/*
 * OscillateBodyActionDescription.cpp
 *
 *  Created on: May 5, 2014
 *      Author: julian
 */

#include "OscillateBodyActionDescription.h"

OscillateBodyActionDescription::OscillateBodyActionDescription() {
	this->action_name = "oscillate_body";
	this->robot_parts_used.push_back("legs");
}

OscillateBodyActionDescription::~OscillateBodyActionDescription() {
}

list<shared_ptr<SimpleActionExecution> > OscillateBodyActionDescription::Analyze(void){
	list<shared_ptr<SimpleActionExecution> > temp;
	shared_ptr<OscillateBodyExecution> oscillate_execution(new OscillateBodyExecution);
	oscillate_execution->setParameterDestination(this->parameter_destination);
	if(this->parameter_translation != NULL){
		oscillate_execution->setParameterTranslation(this->parameter_translation);
	}
	temp.push_back(oscillate_execution);
	return temp;
}
void OscillateBodyActionDescription::setParameterPointPosition(
		shared_ptr<PointPositionParameter> parameter_destination){

	this->parameter_destination = parameter_destination;
}
shared_ptr<PointPositionParameter> OscillateBodyActionDescription::getParameterPosition(){

	return this->parameter_destination;
}
void OscillateBodyActionDescription::setParameterTrnaslation(
		shared_ptr<ParameterTranslation> parameter_translation){

	this->parameter_translation = parameter_translation;
}
shared_ptr<ParameterTranslation> OscillateBodyActionDescription::getParameterTranslation(){
	return this->parameter_translation;
}

