/*
 * ActionAddition.cpp
 *
 *  Created on: May 2, 2014
 *      Author: julian
 */

#include "ActionAddition.h"

ActionAddition::ActionAddition() {
}

ActionAddition::~ActionAddition() {
}

void ActionAddition::addAdditionalSimpleActions(string emotion_and_action,list<boost::shared_ptr<SimpleActionExecution > > *list_simple_action,
		map<string,boost::shared_ptr<EmotionProfile> > emotions_profile,
		boost::shared_ptr<ParameterPosition> parameter_position,
		boost::shared_ptr<ParameterTranslation> parameter_translation){
	//variable to get the list of missing actions
	list<string> list_missing_actions;
	//Gets the description of the emotion
	shared_ptr<EmotionProfile> temp_emotion_description = emotions_profile[emotion_and_action];
	if(temp_emotion_description!=NULL){
		list_missing_actions =
			searchMissingActions(temp_emotion_description->getEmotionProfileActions(),*list_simple_action);
		//Instance of the missing actions
		instanceMissingActions(list_missing_actions,list_simple_action,
				parameter_position,
				parameter_translation);
	}
}

void ActionAddition::instanceMissingActions(list<string> list_missing_actions,
		list<boost::shared_ptr<SimpleActionExecution> > *list_simple_action,
		boost::shared_ptr<ParameterPosition> parameter_position,
		boost::shared_ptr<ParameterTranslation> parameter_translation){
	//for all the acitons that are missin, they are instance
	for(list<string>::iterator it = list_missing_actions.begin();
			it != list_missing_actions.end(); it++){
		shared_ptr<SimpleActionExecution> temp_action = instanceMissingAction(*it,
				parameter_position,
				parameter_translation);
		list_simple_action->push_back(temp_action);
	}
}

/*
 * TODO implement the parameters for the other possible parameters, right now
 * it is just implemented for a position
 */
shared_ptr<SimpleActionExecution> ActionAddition::instanceMissingAction(string missing_action_name,
		boost::shared_ptr<ParameterPosition> parameter_position,
		boost::shared_ptr<ParameterTranslation> parameter_translation){
	//SimpleActionExecution * temp_action_execution = NULL;
	if(missing_action_name=="move_shoulder"){
		shared_ptr<MoveShoulderExecution> temp_action_execution(new MoveShoulderExecution);
		//Here it should be a check for the two cases, one if it is possible to do the cast and other if not
		if(typeid(parameter_position).name()==typeid(PointPositionParameter).name()){
			temp_action_execution->
			setParameterPointPosition(
				boost::static_pointer_cast<PointPositionParameter>(parameter_position));
		}else{
			shared_ptr<PointPositionParameter> temp_point_position_parameter(new PointPositionParameter);
			temp_point_position_parameter->setPointPosition(0.2,0.0,0.0);
			temp_action_execution->setParameterPointPosition(temp_point_position_parameter);
		}
		temp_action_execution->setParameterTranslation(parameter_translation);
		return temp_action_execution;
	}else if(missing_action_name=="move_body"){
		boost::shared_ptr<MoveBodyExecution> temp_action_execution(new MoveBodyExecution);
		temp_action_execution->setParameterDestination(parameter_position);
		temp_action_execution->setParameterTranslation(parameter_translation);
		return temp_action_execution;
	}else if(missing_action_name=="speak"){
		boost::shared_ptr<SpeakExecution> temp_action_execution(new SpeakExecution);
		return temp_action_execution;
	}else if(missing_action_name=="oscillate_body"){
			shared_ptr<OscillateBodyExecution>
			temp_action_execution(new OscillateBodyExecution);
		temp_action_execution->
		setParameterDestination(boost::static_pointer_cast<PointPositionParameter>(
				parameter_position));
		temp_action_execution->setParameterTranslation(parameter_translation);
		return temp_action_execution;
	}else if(missing_action_name=="oscillate_shoulder"){
		boost::shared_ptr<OscillateShoulderExecution>
			temp_action_execution(new OscillateShoulderExecution);
		if(typeid(parameter_position).name()==typeid(PointPositionParameter).name()){
			temp_action_execution->
			setParameterDestination(boost::static_pointer_cast<PointPositionParameter>(parameter_position));
		}else {
			shared_ptr<PointPositionParameter> temp_point_position_parameter(new PointPositionParameter);
			temp_point_position_parameter->setPointPosition(0.2,0.0,0.0);
			temp_action_execution->setParameterDestination(temp_point_position_parameter);
		}
		temp_action_execution->setParameterTranslation(parameter_translation);
		return temp_action_execution;
	}
	shared_ptr<SimpleActionTrajectoryExecution> temp_for_return;
	return temp_for_return;
}

list<string> ActionAddition::searchMissingActions(vector<shared_ptr<ActionChanges> > action_changes,
		list<shared_ptr<SimpleActionExecution> > list_simple_action){
	list<string> temp_missing_actions;
	//for each simple action that it has search for the actions
	for(vector<shared_ptr<ActionChanges> >::iterator it_action = action_changes.begin();
			it_action != action_changes.end(); it_action++){
		//if the action has the same name that the current name in the list
		if(!isTheAction((*it_action)->getActionChangesName(), list_simple_action)){
			temp_missing_actions.push_back((*it_action)->getActionChangesName());
		}
	}
	return temp_missing_actions;
}

bool ActionAddition::isTheAction(string action_name,
		list<shared_ptr<SimpleActionExecution> > list_simple_action){
	for(list<shared_ptr<SimpleActionExecution> >::iterator it_list = list_simple_action.begin();
			it_list != list_simple_action.end(); it_list++){
		if(action_name == (*it_list)->getActionName()){
			return true;
		}
	}
	return false;
}
