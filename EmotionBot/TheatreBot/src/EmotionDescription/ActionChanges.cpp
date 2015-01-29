/*
 * ActionChanges.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: julian
 */

#include "ActionChanges.h"

ActionChanges::ActionChanges() {
	this->repeat = false;
	this->reference = 0.0;
}

ActionChanges::~ActionChanges() {
	for(std::vector<EmotionParameter *>::iterator it = action_emotion_parameters.begin();
			it != action_emotion_parameters.end(); ++it){
		delete *it;
	}
}


void ActionChanges::setReference(float reference){
	this->reference = reference;
}

void ActionChanges::setRepetition(bool repeat){
	this->repeat = repeat;
}

float ActionChanges::getReference(){
	return this->reference;
}

bool ActionChanges::getRepetition(){
	return this->repeat;
}

void ActionChanges::addEmotionParameter(EmotionParameter *parameter){
	this->action_emotion_parameters.push_back(parameter);
}

void ActionChanges::setActionThatModyfies(string action_name){
	this->action_that_changes = action_name;
}

string ActionChanges::getActionThatModyfies(){
	return action_that_changes;
}


void ActionChanges::clearVectorParameters(){
	this->action_emotion_parameters.clear();
}

vector<EmotionParameter *> ActionChanges::getVectorParameters(){
	return action_emotion_parameters;
}

void ActionChanges::setVectorParameters(vector<EmotionParameter *> parameters){
	this->action_emotion_parameters = parameters;
}

vector<EmotionParameter *> ActionChanges::copyVectorParameters(){
	vector<EmotionParameter *> temp;
	for(vector<EmotionParameter *>::iterator it = action_emotion_parameters.begin(); it != action_emotion_parameters.end(); it++){
			temp.push_back((*it)->copyEmotionParameter());
		}
	return temp;
}
