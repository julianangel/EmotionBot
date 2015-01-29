/*
 * DecryptAction.cpp
 *
 *  Created on: May 23, 2014
 *      Author: julian
 */

#include "DecryptAction.h"

DecryptAction::DecryptAction() {
	this->action_addition.reset(new ActionAddition);
	this->action_modification.reset(new ActionModification);
	this->emotions_profiles_load = false;

}

DecryptAction::~DecryptAction() {
}


bool DecryptAction::loadInformation(string directory_path_emotion, string file_path_platform){

	PlatformTest1 *platformTest = new PlatformTest1;
	/**************************************
	 * emotion profiles
	 **************************************/
	bool isEmotionsLoad = this->loadEmotionsAvailable(directory_path_emotion);
	/***************************************
	 * platform profilesvoid DecryptAction::
	 ***************************************/
	platforms_available = platformTest->getPlatformDescription();
	/***************************************
	 * actions available
	 ***************************************/
	this->generateActionsAvailable();
	return isEmotionsLoad;
}

bool DecryptAction::has_suffix(const string& s, const string& suffix){
	return (s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());
}

void DecryptAction::loadInformation(){
	EmotionTest1 *emotionTest = new EmotionTest1;
	PlatformTest1 *platformTest = new PlatformTest1;
	/**************************************
	 * emotion profiles
	 **************************************/
	emotions_available = emotionTest->getEmotionProfile();
	/***************************************
	 * platform profilesvoid DecryptAction::
	 ***************************************/
	platforms_available = platformTest->getPlatformDescription();
	/***************************************
	 * actions available
	 ***************************************/
	this->generateActionsAvailable();
}

list<shared_ptr<SimpleActionExecution> > DecryptAction::analyzeActions(string action_name){
	list<shared_ptr<SimpleActionExecution> > action_list;
	if(action_name == "not_do_anything"){
		shared_ptr<NotDoAnythingSimpleAction> temp_action =
			static_pointer_cast<NotDoAnythingSimpleAction>(actions_available[action_name]);
		action_list = temp_action->Analyze();
	}
	return action_list;
}

/*
 * This method gets the name of the action and gets the respective instance of the actions.
 * The action's instances are kept in a hash table.
 * If the action is found
 */
list<shared_ptr<SimpleActionExecution> > DecryptAction::analyzeActions(string action_name, string emotion,
		shared_ptr<ParameterPosition> parameter_position,
		shared_ptr<ParameterTranslation> parameter_translation){
	list<shared_ptr<SimpleActionExecution> > action_list;
	if(action_name == "walk"){
		shared_ptr<WalkCompoundAction> temp_action
		= static_pointer_cast<WalkCompoundAction>(actions_available[action_name]);
		temp_action->setParameterPosition(parameter_position);
		temp_action->setParameterTrnaslation(parameter_translation);
		action_list = temp_action->Analyze();
	}else if(action_name == "move_body"){
		shared_ptr<MoveBodySimpleActionDescription> temp_action
		= static_pointer_cast<MoveBodySimpleActionDescription>(actions_available[action_name]);
		temp_action->setParameterPosition(parameter_position);
		temp_action->setParameterTrnaslation(parameter_translation);
		action_list = temp_action->Analyze();
	}else if(action_name == "move_torso"){
		shared_ptr<MoveTorsoSimpleAction> temp_action
		= static_pointer_cast<MoveTorsoSimpleAction>(actions_available[action_name]);
		shared_ptr<PointPositionParameter> temp_parameter_position
		= static_pointer_cast<PointPositionParameter>(parameter_position);
		temp_action->setParameterPointPosition(temp_parameter_position);
		temp_action->setParameterTranslation(parameter_translation);
		action_list = temp_action->Analyze();
	}else if(action_name =="move_shoulder"){
		shared_ptr<MoveShoulderSimpleActionDescription> temp_action
		= static_pointer_cast<MoveShoulderSimpleActionDescription>(actions_available[action_name]);
		shared_ptr<PointPositionParameter> temp_parameter_position
		= static_pointer_cast<PointPositionParameter>(parameter_position);
		temp_action->setParameterPointPosition(temp_parameter_position);
		temp_action->setParameterTranslation(parameter_translation);
		action_list = temp_action->Analyze();
	}else if(action_name == "oscillate_torso"){
		shared_ptr<OscillateTorsoSimpleAction> temp_action
		= static_pointer_cast<OscillateTorsoSimpleAction>(actions_available[action_name]);
		shared_ptr<PointPositionParameter> temp_parameter_position
		= static_pointer_cast<PointPositionParameter>(parameter_position);
		temp_action->setParameterPointPosition(temp_parameter_position);
		temp_action->setParameterTranslation(parameter_translation);
		action_list = temp_action->Analyze();
	}else if(action_name =="oscillate_body"){
		shared_ptr<OscillateBodyActionDescription> temp_action
		= static_pointer_cast<OscillateBodyActionDescription>(actions_available[action_name]);
		shared_ptr<PointPositionParameter> temp_parameter_position
		= static_pointer_cast<PointPositionParameter>(parameter_position);
		temp_action->setParameterPointPosition(temp_parameter_position);
		temp_action->setParameterTrnaslation(parameter_translation);
		action_list = temp_action->Analyze();
	}else if(action_name =="oscillate_shoulder"){
		shared_ptr<OscillateShoulderDescription> temp_action
		= static_pointer_cast<OscillateShoulderDescription>(actions_available[action_name]);
		shared_ptr<PointPositionParameter> temp_parameter_position
		= static_pointer_cast<PointPositionParameter>(parameter_position);
		temp_action->setParameterPointPosition(temp_parameter_position);
		temp_action->setParameterTranslation(parameter_translation);
		action_list = temp_action->Analyze();
	}
	this->addAdditionalSimpleActions(emotion,&action_list,
			parameter_position,
			parameter_translation);
	ROS_INFO("working here");
	this->addModificationParameters(emotion,&action_list);
	ROS_INFO("here we have: %d", action_list.size());
	return action_list;
}


list<shared_ptr<SimpleActionExecution> > DecryptAction::analyzeActions(string action_name, string emotion,
		string speech){
	list<shared_ptr<SimpleActionExecution> > action_list;
	if(action_name =="speak"){
		shared_ptr<SpeakSimpleAction>  temp_action =
				static_pointer_cast<SpeakSimpleAction >(actions_available[action_name]);
		shared_ptr<string> temp_speech(new string(speech));
			temp_action->setParameterPhraseToSay(temp_speech);
			action_list = temp_action->Analyze();
		}
	this->addModificationParameters(emotion,&action_list);
	return action_list;
}


float DecryptAction::calculateEmotionalFactor(float emotional_intensity, string emotion){
	return this->action_modification->emotionalFactor(emotional_intensity,emotion);
}

list<shared_ptr<SimpleActionExecution> > DecryptAction::analyzeActions(string action_name, string emotion,
		shared_ptr<ParameterPosition> parameter_position,
		shared_ptr<ParameterTranslation> parameter_translation, string speech){
	list<shared_ptr<SimpleActionExecution> > action_list;
	if(action_name=="walk_and_speak"){
		shared_ptr<WalkAndSpeakCompoundAction> temp_action
		= static_pointer_cast<WalkAndSpeakCompoundAction>(actions_available[action_name]);
		temp_action->setParameterPosition(parameter_position);
		temp_action->setParameterTrnaslation(parameter_translation);
		shared_ptr<string> temp_speech(new string(speech));
		temp_action->setParameterPhraseToSay(temp_speech);
		action_list = temp_action->Analyze();
	}
	this->addAdditionalSimpleActions(emotion,&action_list,
			parameter_position,parameter_translation);
	this->addModificationParameters(emotion,&action_list);
	return action_list;
}

void DecryptAction::analyzeEmotion(string emotion,
			list<shared_ptr<SimpleActionExecution> > *simple_actions,
			shared_ptr<ParameterPosition> parameter_position,
			shared_ptr<ParameterTranslation> parameter_translation){
	if(parameter_position != NULL && parameter_translation != NULL){
		this->addAdditionalSimpleActions(emotion,simple_actions,
			parameter_position,parameter_translation);
	}
	this->addModificationParameters(emotion,simple_actions);
}

/*
 * This method look for the actions that are missing in the current list of actions to show an emotion.
 * If the action is already in the list, it is not added
 */
void DecryptAction::addAdditionalSimpleActions(string emotion,
		list<shared_ptr<SimpleActionExecution> > *simple_actions,
		shared_ptr<ParameterPosition> parameter_position,
		shared_ptr<ParameterTranslation> parameter_translation){
	for(list<shared_ptr<SimpleActionExecution> >::iterator it = simple_actions->begin();
			it != simple_actions->end(); it++){
		this->action_addition->addAdditionalSimpleActions(emotion+"_"+(*it)->getActionName(),
				simple_actions,this->emotions_available,
				parameter_position,
				parameter_translation);
		map<string,shared_ptr<EmotionProfile> > emotions_generated;
	}
}
void DecryptAction::setEmotionsProfilesLoad(bool emotions_profiles_load){
	this->emotions_profiles_load = emotions_profiles_load;
}
void DecryptAction::addModificationParameters(string emotion,
		list<shared_ptr<SimpleActionExecution> > *simple_actions){
	if(emotions_profiles_load){
		for(list<shared_ptr<SimpleActionExecution> >::iterator it = simple_actions->begin();
			it != simple_actions->end(); it++){
			this->action_modification->addEmotionParameters(emotion+"_"+(*it)->getActionName(),
					simple_actions,this->emotions_available);
		}
	}
}


bool DecryptAction::loadEmotionsAvailable(string directory_path){
    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    string file;
    int filesReaded = 0;
    struct dirent *ent;
    DIR *dir = opendir(directory_path.c_str());
	//Required to generate the emotion description
	shared_ptr<EmotionParameter> emotion_parameter;
	shared_ptr<ActionChanges> action_changes;
	shared_ptr<EmotionProfile> emotion_profile;
    //If the directory exist try to open all the files that are in it
    if(dir != NULL){
    	while ((ent = readdir (dir)) != NULL) {
    		if(has_suffix(ent->d_name, ".json")){
    			file = directory_path+"/"+ent->d_name;
    			std::ifstream test(file.c_str(), std::ifstream::binary);
    			if(test.good()){
    				Json::Value tempValue, actionsValue, actionValue, parameterValue;
    				bool parsingSuccessful = reader.parse( test, root, false );
    				if ( !parsingSuccessful ){
    					ROS_ERROR_STREAM(reader.getFormatedErrorMessages());
    					ROS_ERROR_STREAM(file);
    					break;
    				}
    				ROS_INFO_STREAM("analyzing file: "<<ent->d_name);
    				vector<string> alias = root.getMemberNames();
    				vector<string>::iterator iteratorAlias;
    				//Get all the objects, expecting that these are emotion description
    				for(iteratorAlias = alias.begin();
    						iteratorAlias != alias.end();
    						iteratorAlias++){
    					tempValue = root[(*iteratorAlias)];
    					if(tempValue.isObject()){
    						//Get description
    						actionsValue = tempValue.get("description","UTF-8");
    						emotion_profile.reset(new EmotionProfile);
    						if(!actionsValue.isNull()){
        						emotion_profile->
        						setEmotionProfileAction(actionsValue.get("emotionProfileAction","UTF-8").asString());
        						emotion_profile->
        						setEmotionProfileEmotion(actionsValue.get("emotionProfileEmotion","UTF-8").asString());
        						emotion_profile->
        						setEmotionProfileName(actionsValue.get("emotionProfileEmotion","UTF-8").asString()+
        								"_"+
        								actionsValue.get("emotionProfileAction","UTF-8").asString());
    						}
    						ROS_INFO("action_emotion: %s",emotion_profile->getEmotionProfileName().c_str());
    						actionsValue = tempValue.get("actions","UTF-8");
    						//Get actions
    						if(!actionsValue.isNull()){
    							vector<string> aliasActions = actionsValue.getMemberNames();
    							vector<string>::iterator iteratorActionsAlias;
    							for(iteratorActionsAlias = aliasActions.begin();
    									iteratorActionsAlias!= aliasActions.end();
    									iteratorActionsAlias++){
    	    						action_changes.reset(new ActionChanges);
    	    						action_changes->setActionChangesName((*iteratorActionsAlias));

    								//(*iteratorActionsAlias) as the action name
    								actionValue = actionsValue.get((*iteratorActionsAlias),"UTF-8");
    								ROS_INFO_STREAM("Action name "<<(*iteratorActionsAlias)<<" "
    										<<action_changes->getActionChangesName());
    								for(int i=0; i<actionValue.size();i++){
        	    						emotion_parameter.reset(new EmotionParameter);
    									parameterValue = actionValue.get(i,"UTF-8");
    									emotion_parameter->
    									setEmotionParameterTime(parameterValue.get("time","UTF-8").asFloat());
    									emotion_parameter->
    									setEmotionParameterSpacing(parameterValue.get("space","UTF-8").asFloat());
    									ROS_INFO("Time %f Spacing %f",emotion_parameter->getEmotionParameterTime(),
    											emotion_parameter->getEmotionParameterSpacing());
    									action_changes->addActioChangesParameter(emotion_parameter);
    									action_changes->setTypeActionEmotion(TypeActionEmotionChangeStaticAction);
    								}
									emotion_profile->addEmotionProfileActionChanges(action_changes);

    							}
    						}
    						emotions_available[emotion_profile->getEmotionProfileName()]=emotion_profile;
    					}
    				}
    				filesReaded++;
    			}else{
    				cout<<"Impossible to open the file"<<ent->d_name<<endl;
    				break;
    			}
    		}
    	}
    	ROS_INFO("Emotions are load it");
    	//printEmotions();
    	closedir (dir);
    	//All the files were processed
    	return true;
    }
    if(filesReaded==0){
    	return false;
    }else{
    	return true;
    }

}

void DecryptAction::printEmotions(){
	for(map<string, shared_ptr<EmotionProfile> >::iterator it = emotions_available.begin();
			it != emotions_available.end();
			it++){
		shared_ptr<EmotionProfile> tempEmotion = (*it).second;
		ROS_INFO_STREAM("name: "<<tempEmotion->getEmotionProfileName());
		vector<shared_ptr<ActionChanges> > tempProfile = tempEmotion->getEmotionProfileActions();
		for(vector<shared_ptr<ActionChanges> >::iterator itProfile = tempProfile.begin();
				itProfile != tempProfile.end(); itProfile++){
			shared_ptr<ActionChanges> tempActionChanges = (*itProfile);
			ROS_INFO_STREAM("action: "<<tempActionChanges->getActionChangesName());
			vector<shared_ptr<EmotionParameter> > tempEmotionParameter =
					tempActionChanges->getActionChangesParameteres();
			for(vector<shared_ptr<EmotionParameter> >::iterator itParameter = tempEmotionParameter.begin();
					itParameter != tempEmotionParameter.end(); itParameter++){
				ROS_INFO_STREAM("Spacing: "<<(*itParameter)->getEmotionParameterSpacing()
						<<" Time: "<<(*itParameter)->getEmotionParameterTime());
			}
		}
	}
}

/**
 * Action Available in the whole system
 */
void DecryptAction::generateActionsAvailable(){
	shared_ptr<NotDoAnythingSimpleAction> not_do_anything_action(new NotDoAnythingSimpleAction);
	this->actions_available[not_do_anything_action->getActionName()]=not_do_anything_action;
	shared_ptr<WalkCompoundAction> walk_action(new WalkCompoundAction);
	this->actions_available[walk_action->getActionName()]=walk_action;
	shared_ptr<WalkAndSpeakCompoundAction> walk_speak_action(new WalkAndSpeakCompoundAction);
	this->actions_available[walk_speak_action->getActionName()]=walk_speak_action;
	shared_ptr<MoveBodySimpleActionDescription> move_body_action(new MoveBodySimpleActionDescription);
	this->actions_available[move_body_action->getActionName()]=move_body_action;
	shared_ptr<MoveShoulderSimpleActionDescription> move_shoulder_action(new MoveShoulderSimpleActionDescription);
	this->actions_available[move_shoulder_action->getActionName()]=move_shoulder_action;
	shared_ptr<OscillateBodyActionDescription>  oscillate_body_action(new OscillateBodyActionDescription);
	this->actions_available[oscillate_body_action->getActionName()]=oscillate_body_action;
	shared_ptr<OscillateShoulderDescription> oscillate_shoulder_action(new OscillateShoulderDescription);
	this->actions_available[oscillate_shoulder_action->getActionName()]=oscillate_shoulder_action;
	shared_ptr<SpeakSimpleAction> speak_action(new SpeakSimpleAction);
	this->actions_available[speak_action->getActionName()]=speak_action;
	shared_ptr<MoveTorsoSimpleAction> torso_action(new MoveTorsoSimpleAction);
	this->actions_available[torso_action->getActionName()]=torso_action;
	shared_ptr<OscillateTorsoSimpleAction> oscillate_torso_action(new OscillateTorsoSimpleAction);
	this->actions_available[oscillate_torso_action->getActionName()]=oscillate_torso_action;

}
