/*
 * SpeakSimpleAction.h
 *
 *  Created on: Apr 30, 2014
 *      Author: julian
 */

#ifndef SPEAKSIMPLEACTION_H_
#define SPEAKSIMPLEACTION_H_

#include "../SimpleActionDescription.h"
#include "../../../general_execution/action_execution/SpeakExecution.h"

class SpeakSimpleAction: public SimpleActionDescription {
public:
	SpeakSimpleAction();
	virtual ~SpeakSimpleAction();
	list<shared_ptr<SimpleActionExecution> > Analyze();
	void setParameterPhraseToSay(shared_ptr<string> phrase_to_say);
	shared_ptr<string > getParameterPhraseToSay();
private:
	shared_ptr<string>  phrase_to_say;
};

#endif /* SPEAKSIMPLEACTION_H_ */
