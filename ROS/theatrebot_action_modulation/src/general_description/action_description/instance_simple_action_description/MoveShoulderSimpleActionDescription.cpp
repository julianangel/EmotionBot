/*
 * MoveShoulderSimpleActionDescription.cpp
 *
 *  Created on: Apr 17, 2014
 *      Author: julian
 */

#include "MoveShoulderSimpleActionDescription.h"

MoveShoulderSimpleActionDescription::MoveShoulderSimpleActionDescription() {
	this->action_name = "move_shoulder";
	this->robot_parts_used.push_back("shoulder");
}

MoveShoulderSimpleActionDescription::~MoveShoulderSimpleActionDescription() {
}

list<shared_ptr<SimpleActionExecution> > MoveShoulderSimpleActionDescription::Analyze(){
	list<shared_ptr<SimpleActionExecution> > temp;
	shared_ptr<MoveShoulderExecution> shoulder_execution(new MoveShoulderExecution);
	shoulder_execution->setParameterPointPosition(this->parameter_position);
	shoulder_execution->setTypeAction(TypeActionMandatory);
	shoulder_execution->setActionIsPrincipal(this->action_is_principal);
	if(this->parameter_translation != NULL)
		shoulder_execution->setParameterTranslation(this->parameter_translation);
	temp.push_back(shoulder_execution);
	return temp;
}
void MoveShoulderSimpleActionDescription::setParameterPointPosition(
		shared_ptr<PointPositionParameter> parameter_position){
	this->parameter_position = parameter_position;
}
shared_ptr<PointPositionParameter> MoveShoulderSimpleActionDescription::getParameterPosition(){
	return this->parameter_position;
}
void MoveShoulderSimpleActionDescription::setParameterTranslation(shared_ptr<ParameterTranslation> parameter_translation){
	this->parameter_translation = parameter_translation;
}
shared_ptr<ParameterTranslation> MoveShoulderSimpleActionDescription::getParameterTranslation(){
	return this->parameter_translation;
}
