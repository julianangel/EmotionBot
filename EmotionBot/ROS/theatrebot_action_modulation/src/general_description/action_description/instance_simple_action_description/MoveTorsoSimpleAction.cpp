/*
 * MoveTorsoSimpleAction.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: julian
 */

#include "MoveTorsoSimpleAction.h"

MoveTorsoSimpleAction::MoveTorsoSimpleAction() {
	this->action_name = "move_torso";
	this->robot_parts_used.push_back("torso");
}

MoveTorsoSimpleAction::~MoveTorsoSimpleAction() {
}

list<shared_ptr<SimpleActionExecution> > MoveTorsoSimpleAction::Analyze(){
	list<shared_ptr<SimpleActionExecution> > temp;
	shared_ptr<MoveTorsoExecution> torso_execution(new MoveTorsoExecution);
	torso_execution->setParameterPointPosition(this->parameter_position);
	torso_execution->setTypeAction(TypeActionMandatory);
	torso_execution->setActionIsPrincipal(this->action_is_principal);
	if(this->parameter_translation != NULL)
		torso_execution->setParameterTranslation(this->parameter_translation);
	temp.push_back(torso_execution);
	return temp;
}

void MoveTorsoSimpleAction::setParameterPointPosition(
		shared_ptr<PointPositionParameter> parameter_position){
	this->parameter_position = parameter_position;
}

shared_ptr<PointPositionParameter> MoveTorsoSimpleAction::getParameterPosition(){
	return this->parameter_position;
}

void MoveTorsoSimpleAction::setParameterTranslation(shared_ptr<ParameterTranslation> parameter_translation){
	this->parameter_translation = parameter_translation;
}

shared_ptr<ParameterTranslation> MoveTorsoSimpleAction::getParameterTranslation(){
	return this->parameter_translation;
}
