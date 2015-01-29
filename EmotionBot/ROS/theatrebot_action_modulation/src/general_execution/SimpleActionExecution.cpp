/*
 * SimpleActionExecution.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: julian
 */

#include "SimpleActionExecution.h"

SimpleActionExecution::SimpleActionExecution() {
	type_action = TypeActionUnknown;
	type_emotion_changes = TypeActionEmotionChangeUnknown;
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
TypeAction SimpleActionExecution::getTypeAction(){
	return this->type_action;
}
void SimpleActionExecution::setTypeAction(TypeAction type_action){
	this->type_action = type_action;
}

TypeActionEmotionChange SimpleActionExecution::getTypeEmotiveAction(){
	return this->type_emotion_changes;
}
void SimpleActionExecution::setTypeEmotiveAction(TypeActionEmotionChange type_emotion_changes){
	this->type_emotion_changes = type_emotion_changes;
}

void SimpleActionExecution::setActionIsPrincipal(bool action_is_principal){
	this->action_is_principal = action_is_principal;
}
bool SimpleActionExecution::getActionIsPrincipal(){
	return this->action_is_principal;
}
