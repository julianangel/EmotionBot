/*
 * ActionAddition.h
 *
 *  Created on: May 2, 2014
 *      Author: julian
 */

#ifndef ACTIONADDITION_H_
#define ACTIONADDITION_H_

#include <list>
#include <string>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include "../general_execution/SimpleActionTrajectoryExecution.h"
#include "../general_description/emotion_description/EmotionProfile.h"
#include "../general_description/action_description/instance_simple_action_description/MoveBodySimpleActionDescription.h"
#include "../general_description/action_description/instance_simple_action_description/MoveShoulderSimpleActionDescription.h"
#include "../general_description/action_description/instance_simple_action_description/SpeakSimpleAction.h"
#include "../general_description/action_description/instance_simple_action_description/OscillateBodyActionDescription.h"
#include "../general_description/action_description/instance_simple_action_description/OscillateShoulderDescription.h"

using std::string;
using std::list;
using std::map;
using std::vector;
/*
 * This class gets the desire action and adds decomposed this action into
 * simple actions. then, it adds the actions that are emotional.
 */
class ActionAddition {
public:
	//constructor
	ActionAddition();
	//desctructor
	virtual ~ActionAddition();
	/*
	 * Parameters:
	 * 	emotion_and_action: emotion and action that should be analyze
	 * 	list_simple_action: pointer to the list of all the actions
	 * 	emotions_profile: map with the name of the emotion and how it is represented
	 * 	parameter_position: where it should go the robot, it could be position, area or landmark
	 * 	parameter_translation: describes how it should be done. it could be velocity, time or acceleration
	 */
	void addAdditionalSimpleActions(string emotion_and_action,list<shared_ptr<SimpleActionExecution > > *list_simple_action,
			map<string,shared_ptr<EmotionProfile> > emotions_profile,
			shared_ptr<ParameterPosition> parameter_position,
			shared_ptr<ParameterTranslation> parameter_translation);
private:
	/*
	 * This method looks for the actions that are not yet added and that are necessary to
	 * show the emotion
	 * Parameters:
	 * 	action_changes: changes that should be done in the current action.
	 * 	list_simple_action: list of the current actions
	 * Returns:
	 *  the list of actions that are missing to show the emotion
	 */
	list<string> searchMissingActions(vector<shared_ptr<ActionChanges> > action_changes,
			list<shared_ptr<SimpleActionExecution> > list_simple_action);
	bool isTheAction(string action_name,
			list<shared_ptr<SimpleActionExecution> > list_simple_action);
	void instanceMissingActions(list<string> list_missing_actions,
			list<shared_ptr<SimpleActionExecution> > *list_simple_action,
			shared_ptr<ParameterPosition> parameter_position,
			shared_ptr<ParameterTranslation> parameter_translation);
			shared_ptr<SimpleActionExecution> instanceMissingAction(string missing_action_name,
			shared_ptr<ParameterPosition> parameter_position,
			shared_ptr<ParameterTranslation> parameter_translation);
};

#endif /* ACTIONADDITION_H_ */
