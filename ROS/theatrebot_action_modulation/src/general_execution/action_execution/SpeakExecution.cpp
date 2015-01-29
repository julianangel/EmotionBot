/*
 * SpeakExecution.cpp
 *
 *  Created on: May 1, 2014
 *      Author: julian
 */

#include "SpeakExecution.h"

SpeakExecution::SpeakExecution() {
	this->action_name = "speak";
}

SpeakExecution::~SpeakExecution() {
}

void SpeakExecution::setParameterPhraseToSay(shared_ptr<string> phrase_to_say){
	this->phrase_to_say = phrase_to_say;
}
shared_ptr<string> SpeakExecution::getParameterPhraseToSay(){
	return this->phrase_to_say;
}

theatrebot_action_modulation::ActionExecutionActionDescriptionMessage
SpeakExecution::getMessage(){
	theatrebot_action_modulation::ActionExecutionActionDescriptionMessage temp;
	temp.action_name.data = this->action_name;
	if(this->type_action==TypeActionEmotional){
		temp.action_type.data = "emotional";
	}else if(this->type_action == TypeActionMandatory){
		temp.action_type.data = "mandatory";
	}
	temp.action_is_principal.data = this->action_is_principal;
	//TODO think what to do here
	temp.phrase_to_say.data = *(this->phrase_to_say);
	//Emotion
	for(vector<shared_ptr<EmotionParameter> >::iterator it = emotion_changes.begin();
			it != emotion_changes.end(); it++){
		theatrebot_action_modulation::EmotionParametersMessage temp_emotion;
		temp_emotion.timing = (*it)->getEmotionParameterTime();
		temp_emotion.spacing = (*it)->getEmotionParameterSpacing();
		temp.emotion_parameters.push_back(temp_emotion);
	}
	return temp;
}

