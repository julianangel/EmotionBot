/*
 * SpeakExecution.h
 *
 *  Created on: May 1, 2014
 *      Author: julian
 */

#ifndef SPEAKEXECUTION_H_
#define SPEAKEXECUTION_H_

#include "../SimpleActionExecution.h"

class SpeakExecution: public SimpleActionExecution {
public:
	SpeakExecution();
	virtual ~SpeakExecution();
	bool executeAction(string platform);
	void setParameterPhraseToSay(shared_ptr<string> phrase_to_say);
	shared_ptr<string> getParameterPhraseToSay();

private:
	shared_ptr<string>phrase_to_say;
};

#endif /* SPEAKEXECUTION_H_ */
