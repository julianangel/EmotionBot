/*
 * MoveSimpleActionDescription.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: julian
 */

#include "MoveBodySimpleActionDescription.h"

MoveBodySimpleActionDescription::MoveBodySimpleActionDescription() {

	this->action_name = "move_body";
	this->robot_parts_used.push_back("legs");
}

MoveBodySimpleActionDescription::~MoveBodySimpleActionDescription() {

}

list<shared_ptr<SimpleActionExecution> > MoveBodySimpleActionDescription::Analyze(void){
	list<shared_ptr<SimpleActionExecution> > temp;
	shared_ptr<MoveBodyExecution> move_execution(new MoveBodyExecution);
	move_execution->setParameterDestination(this->parameter_destination);
	if(this->parameter_translation != NULL){
		move_execution->setParameterTranslation(this->parameter_translation);
	}
	temp.push_back(move_execution);
	return temp;
}


void MoveBodySimpleActionDescription::setParameterPosition(
		shared_ptr<ParameterPosition> parameter_destination){
	this->parameter_destination = parameter_destination;
}
shared_ptr<ParameterPosition> MoveBodySimpleActionDescription::getParameterPosition(){
	return this->parameter_destination;
}
void MoveBodySimpleActionDescription::setParameterTrnaslation(
		shared_ptr<ParameterTranslation> parameter_translation){
	this->parameter_translation = parameter_translation;
}
shared_ptr<ParameterTranslation> MoveBodySimpleActionDescription::getParameterTranslation(){
	return this->parameter_translation;
}
