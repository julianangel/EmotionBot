/*
 * WalkAndSpeakCompoundAction.h
 *
 *  Created on: Apr 30, 2014
 *      Author: julian
 */

#ifndef WALKANDSPEAKCOMPOUNDACTION_H_
#define WALKANDSPEAKCOMPOUNDACTION_H_

#include "../SequenceAbstractActionDescription.h"
#include "WalkCompoundAction.h"
#include "../instance_simple_action_description/SpeakSimpleAction.h"

class WalkAndSpeakCompoundAction:  public SequenceAbstractActionDescription {
public:
	WalkAndSpeakCompoundAction();
	virtual ~WalkAndSpeakCompoundAction();
	list<shared_ptr<SimpleActionExecution> > Analyze();
	void setParameterPosition(shared_ptr<ParameterPosition> parameter_destination);
	shared_ptr<ParameterPosition> getParameterPosition();
	void setParameterTrnaslation(shared_ptr<ParameterTranslation> parameter_translation);
	shared_ptr<ParameterTranslation> getParameterTranslation();
	void setParameterPhraseToSay(shared_ptr<string> phrase_to_say);
	shared_ptr<string> getParameterPhraseToSay();
private:
	shared_ptr<WalkCompoundAction> walk_action;
	shared_ptr<SpeakSimpleAction> speak_simple_action;
	shared_ptr<string> phrase_to_say;
	/**
	 * This parameter specifies the final destination of the robot.
	 * Therefore, it is used the abstract class ParameterPosition,
	 */
	shared_ptr<ParameterPosition> parameter_destination;
	/**
	 * This parameter constrains the trajectory: time, velocity, acceleration.
	 * This parameter could be optional
	 */
	shared_ptr<ParameterTranslation> parameter_translation;
};

#endif /* WALKANDSPEAKCOMPOUNDACTION_H_ */
