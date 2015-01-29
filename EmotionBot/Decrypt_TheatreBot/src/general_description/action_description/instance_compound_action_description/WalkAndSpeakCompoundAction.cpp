/*
 * WalkAndSpeakCompoundAction.cpp
 *
 *  Created on: Apr 30, 2014
 *      Author: julian
 */

#include "WalkAndSpeakCompoundAction.h"

WalkAndSpeakCompoundAction::WalkAndSpeakCompoundAction() {
	//walk action
	walk_action.reset(new WalkCompoundAction);
	speak_simple_action.reset(new SpeakSimpleAction);
	speak_simple_action->setParameterPhraseToSay(this->phrase_to_say);
	//add the actions
	this->abstract_actions.push_back(walk_action);
	this->abstract_actions.push_back(speak_simple_action);
	//info about the action
	this->action_description = "goes from point a to b while speaking";
	//parts used
	this->action_name = "walk_and_speak";
	list<string> robot_parts_used_temp = walk_action->getRobotPartsUsed();
	this->robot_parts_used.merge(robot_parts_used_temp);
	robot_parts_used_temp = speak_simple_action->getRobotPartsUsed();
	this->robot_parts_used.merge(robot_parts_used_temp);
}

WalkAndSpeakCompoundAction::~WalkAndSpeakCompoundAction() {
	//delete this->parameter_destination;
	//delete this->parameter_translation;
}

list<shared_ptr<SimpleActionExecution> > WalkAndSpeakCompoundAction::Analyze(){
	list<shared_ptr<SimpleActionExecution> > temp;
	for(vector<shared_ptr<AbstractActionDescription> >::iterator it = abstract_actions.begin();
			it != abstract_actions.end(); ++it){
		list<shared_ptr<SimpleActionExecution> > t = (*it)->Analyze();
		temp.merge(t);
	}
	return temp;
}

void WalkAndSpeakCompoundAction::setParameterPosition(shared_ptr<ParameterPosition> parameter_destination){
	this->parameter_destination = parameter_destination;
	this->walk_action->setParameterPosition(parameter_destination);
}

shared_ptr<ParameterPosition> WalkAndSpeakCompoundAction::getParameterPosition(){
	return this->parameter_destination;
}

void WalkAndSpeakCompoundAction::setParameterTrnaslation(shared_ptr<ParameterTranslation> parameter_translation){
	this->parameter_translation= parameter_translation;
	this->walk_action->setParameterTrnaslation(parameter_translation);
	}

shared_ptr<ParameterTranslation> WalkAndSpeakCompoundAction::getParameterTranslation(){
	return this->parameter_translation;
}

void WalkAndSpeakCompoundAction::setParameterPhraseToSay(shared_ptr<string> phrase_to_say){
	this->phrase_to_say = phrase_to_say;
	this->speak_simple_action->setParameterPhraseToSay(phrase_to_say);
}

shared_ptr<string> WalkAndSpeakCompoundAction::getParameterPhraseToSay(){
	return this->phrase_to_say;
}
