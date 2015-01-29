/*
 * SimpleActionExecution.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: julian
 */

#include "SimpleActionExecution.h"

SimpleActionExecution::SimpleActionExecution() {
	type_action = TypeActionUnknown;
}

SimpleActionExecution::~SimpleActionExecution() {

}

TypeAction SimpleActionExecution::getSimpleActionType(){
	return this->type_action;
}


void SimpleActionExecution::setSimpleActionType(TypeAction type_action){
	this->type_action = type_action;
}

void SimpleActionExecution::setActionName(string action_name){
	this->action_name = action_name;
}
string SimpleActionExecution::getActionName(){
	return this->action_name;
}

vector<shared_ptr<EmotionParameter> > SimpleActionExecution::getEmotionChanges(){
	return this->emotion_changes;
}

void SimpleActionExecution::setEmotionChanges(vector<shared_ptr<EmotionParameter> > emotion_changes){
	this->emotion_changes = emotion_changes;
}
void SimpleActionExecution::addEmotionChange(shared_ptr<EmotionParameter>emotion_change){
	this->emotion_changes.push_back(emotion_change);
}
