/*
 * SimpleActionExecution.h
 *
 *  Created on: Apr 4, 2014
 *      Author: julian
 */

#ifndef SIMPLEACTIONEXECUTION_H_
#define SIMPLEACTIONEXECUTION_H_

#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <boost/shared_ptr.hpp>

#include "../types_description/TypeAction.h"
#include "../general_description/parameters_description/ActionParameter.h"
#include "../general_description/parameters_description/parameters_instances/EmotionParameter.h"
#include "../general_description/parameters_description/parameters_instances/PointPositionParameter.h"

using std::cout;
using std::endl;
using std::type_info;
using std::string;
using std::vector;
using boost::shared_ptr;
/*
 * This class is abstract. In this way, each simple action has its own implementation
 */
class SimpleActionExecution {
public:
	SimpleActionExecution();
	virtual ~SimpleActionExecution();
	virtual bool executeAction(string platform)=0;
	//Type of action, this helps to solve conflicts between actions
	TypeAction getSimpleActionType();
	void setSimpleActionType(TypeAction type_action);
	void setActionName(string action_name);
	string getActionName();
	void setEmotionChanges(vector<shared_ptr<EmotionParameter> > emotion_changes);
	void addEmotionChange(shared_ptr<EmotionParameter> emotion_change);
	vector<shared_ptr<EmotionParameter> > getEmotionChanges();

protected:
	/*
	 * Emotion parameters that should be changed when is executing the
	 */
	vector<shared_ptr<EmotionParameter> > emotion_changes;
	/**
	 * It tells if the action is mandatory or it comes from emotional aspect
	 */
	TypeAction type_action;
	/**
	 * name of the action that represents
	 */
	string action_name;

};

#endif /* SIMPLEACTIONEXECUTION_H_ */
