/*
 * SpeakExecution.cpp
 *
 *  Created on: May 1, 2014
 *      Author: julian
 */

#include "SpeakExecution.h"

SpeakExecution::SpeakExecution() {
	this->action_name = "speak";
	this->type_action = TypeActionSpeak;
}

SpeakExecution::~SpeakExecution() {
}
bool SpeakExecution::executeAction(string platform){
	bool result = false;
	if(platform == "triskar_big"){

	}else if(platform == "triskar_small"){
		cout<<"executing speak"<<endl;
	}
	return result;
}
void SpeakExecution::setParameterPhraseToSay(shared_ptr<string> phrase_to_say){
	this->phrase_to_say = phrase_to_say;
}
shared_ptr<string> SpeakExecution::getParameterPhraseToSay(){
	return this->phrase_to_say;
}

