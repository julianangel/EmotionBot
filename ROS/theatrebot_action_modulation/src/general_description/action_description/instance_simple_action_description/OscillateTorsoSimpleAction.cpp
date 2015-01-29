/*
 * OscillateTorsoSimpleAction.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: julian
 */

#include "OscillateTorsoSimpleAction.h"

OscillateTorsoSimpleAction::OscillateTorsoSimpleAction() {
	this->action_name = "oscillate_torso";
	this->robot_parts_used.push_back("torso");
}

OscillateTorsoSimpleAction::~OscillateTorsoSimpleAction() {
	// TODO Auto-generated destructor stub
}
list<shared_ptr<SimpleActionExecution> > OscillateTorsoSimpleAction::Analyze(void){
	list<shared_ptr<SimpleActionExecution> > temp;
	shared_ptr<OscillateTorsoExecution>oscillate_execution(new OscillateTorsoExecution);
	oscillate_execution->setParameterDestination(this->parameter_destination);
	oscillate_execution->setTypeAction(TypeActionMandatory);
	oscillate_execution->setActionIsPrincipal(this->action_is_principal);
	if(this->parameter_translation != NULL){
		oscillate_execution->setParameterTranslation(this->parameter_translation);
	}
	temp.push_back(oscillate_execution);
	return temp;
}
void OscillateTorsoSimpleAction::setParameterPointPosition(
		shared_ptr<PointPositionParameter> parameter_destination){
	this->parameter_destination = parameter_destination;
}
shared_ptr<PointPositionParameter> OscillateTorsoSimpleAction::getParameterPosition(){
	return this->parameter_destination;
}
void OscillateTorsoSimpleAction::setParameterTranslation(
		shared_ptr<ParameterTranslation> parameter_translation){
	this->parameter_translation = parameter_translation;
}
shared_ptr<ParameterTranslation> OscillateTorsoSimpleAction::getParameterTranslation(){
	return this->parameter_translation;
}

