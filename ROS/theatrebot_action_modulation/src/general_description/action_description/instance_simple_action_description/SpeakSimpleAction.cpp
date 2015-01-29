/*
 * SpeakSimpleAction.cpp
 *
 *  Created on: Apr 30, 2014
 *      Author: julian
 */

#include "SpeakSimpleAction.h"

SpeakSimpleAction::SpeakSimpleAction() {
	this->action_name = "speak";
	this->robot_parts_used.push_back("speaker");
}

SpeakSimpleAction::~SpeakSimpleAction() {
	// TODO Auto-generated destructor stub
}
list<shared_ptr<SimpleActionExecution> > SpeakSimpleAction::Analyze(){
	list<shared_ptr<SimpleActionExecution> > temp;
	shared_ptr<SpeakExecution>speak_execution(new SpeakExecution);
	speak_execution->setTypeAction(TypeActionMandatory);
	speak_execution->setActionIsPrincipal(this->action_is_principal);
	speak_execution->setParameterPhraseToSay(this->phrase_to_say);
	temp.push_back(speak_execution);
	return temp;
}
void SpeakSimpleAction::setParameterPhraseToSay(shared_ptr<string>phrase_to_say){
	this->phrase_to_say = phrase_to_say;
}
shared_ptr<string> SpeakSimpleAction::getParameterPhraseToSay(){
	return this->phrase_to_say;
}

