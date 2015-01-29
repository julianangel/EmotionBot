/*
 * ActionModification.cpp
 *
 *  Created on: May 2, 2014
 *      Author: julian
 */

#include "ActionModification.h"

ActionModification::ActionModification() {
	// TODO Auto-generated constructor stub

}

ActionModification::~ActionModification() {
	// TODO Auto-generated destructor stub
}


//TODO calculate the emotional factor calculation based on the character traits
float ActionModification::emotionalFactor(float emotional_intensity, string emotion){
	float emotional_factor = 0;
	//TODO a table where is get how each emotion affects the character
	//TODO load this information from files
	//TODO specify how this files should be written
	return emotional_factor;
}

//TODO add character traits into the actions
void ActionModification::addEmotionParameters(string emotion_and_action,
		list<shared_ptr<SimpleActionExecution> > *list_simple_action ,
		map<string,shared_ptr<EmotionProfile > > emotions_profile){
	//Gets the description of the emotion
	shared_ptr<EmotionProfile> temp_emotion_description = emotions_profile[emotion_and_action];
	if(temp_emotion_description!=NULL){
		//For each action changes adds the emotion parameters
		for(list<shared_ptr<SimpleActionExecution > >::iterator it = list_simple_action->begin();
				it != list_simple_action->end(); it++){
			//
			vector<shared_ptr<EmotionParameter> > temp_action_changes =
					searchEmotionParameters(temp_emotion_description,(*it)->getActionName());
			//Add the n
			for(vector<shared_ptr<EmotionParameter> >::iterator it_emotion = temp_action_changes.begin();
				it_emotion != temp_action_changes.end(); it_emotion++){
				shared_ptr<EmotionParameter> temp_emotion_parameter( new EmotionParameter);
				temp_emotion_parameter->setEmotionParameterTime((*it_emotion)->getEmotionParameterTime());
				temp_emotion_parameter->setEmotionParameterSpacing((*it_emotion)->getEmotionParameterSpacing());
				(*it)->addEmotionChange(temp_emotion_parameter);
			}
		}
	}
}


vector<shared_ptr<EmotionParameter> > ActionModification::searchEmotionParameters(
		shared_ptr<EmotionProfile> emotion_profile,
		string action_name){
	vector<shared_ptr<ActionChanges> > temp_action_changes = (emotion_profile->getEmotionProfileActions());
	for(vector<shared_ptr<ActionChanges> >::iterator it = temp_action_changes.begin();
			it != temp_action_changes.end(); it++){
		if((*it)->getActionChangesName()==action_name){
			return ((*it)->getActionChangesParameteres());
		}
	}
	vector<shared_ptr<EmotionParameter> > temp_action_parameter;
	return temp_action_parameter;
}

//This one is used when the planner is going to execute
void ActionModification::modifySimpleActions(shared_ptr<SimpleActionExecution> simple_action){


		/*//Gets the description of the emotion
		EmotionProfile * temp_emotion_description = emotions_profile[emotion_and_action];
		//For each emotion change the parameters
		for(list<SimpleActionExecution *>::iterator it = list_simple_action->begin();
				it != list_simple_action->end(); it++){
			if((*it)->getSimpleActionType()==TypeActionTrajectory){
				SimpleActionTrajectoryExecution * temp_trajectory_execution
				= dynamic_cast<SimpleActionTrajectoryExecution *> (*it);
				if(typeid(temp_trajectory_execution->getParameterTranslation()).name()==typeid(ParameterVelocity).name()){
					this->modifyUsingVelocity(*it,temp_emotion_description);
				}else if(typeid(temp_trajectory_execution->getParameterTranslation()).name()==typeid(ParameterTime).name()){
					this->modifyUsingTime(*it,temp_emotion_description);
				}else if(typeid(temp_trajectory_execution->getParameterTranslation()).name()==typeid(ParameterAcceleration).name()){
					this->modifyUsingAcceleration(*it,temp_emotion_description);
				}else{
					this->modifyUsingPreDefinedValues(*it,temp_emotion_description);
				}
			}
		}*/
}

void ActionModification::modifyUsingPreDefinedValues(shared_ptr<SimpleActionExecution> action_execution,
		shared_ptr<EmotionProfile> emotion_profile){

}

void ActionModification::modifyUsingVelocity(shared_ptr<SimpleActionExecution> action_execution,
		shared_ptr<EmotionProfile> emotion_profile){

}

void ActionModification::modifyUsingTime(shared_ptr<SimpleActionExecution> action_execution,
		shared_ptr<EmotionProfile> emotion_profile){

}

void ActionModification::modifyUsingAcceleration(shared_ptr<SimpleActionExecution> action_execution,
		shared_ptr<EmotionProfile> emotion_profile){

}
