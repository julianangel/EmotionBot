/*
 * DecryptAction.h
 *
 *  Created on: May 23, 2014
 *      Author: julian
 */

#ifndef DECRYPTACTION_H_
#define DECRYPTACTION_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include <fstream>
#include <dirent.h>

#include "general_execution/SimpleActionExecution.h"
#include "action_modulation/ActionAddition.h"
#include "action_modulation/ActionModification.h"
#include "general_description/action_description/instance_compound_action_description/WalkAndSpeakCompoundAction.h"
#include "general_description/action_description/instance_compound_action_description/WalkCompoundAction.h"
#include "general_description/parameters_description/parameters_instances/PointPositionParameter.h"
#include "general_description/parameters_description/parameters_instances/ParameterVelocity.h"
#include "instances/emotion_profiles/EmotionTest1.h"
#include "instances/platform_profiles/PlatformTest1.h"
#include "json/json/json.h"

using std::string;
using std::list;
using boost::static_pointer_cast;

/*
 * TODO implement the load information method with the file. to do this, first should be defined the files
 * description, select the language, etc.
 */

class DecryptAction {
public:
	DecryptAction();
	virtual ~DecryptAction();
	//This is pre-defined info
	void loadInformation();
	//This method is used to load the information from all the files present in a given directory
	bool loadInformation(string directory_path_emotion, string file_path_platform);
	list<shared_ptr<SimpleActionExecution> > analyzeActions(string action_name);
	list<shared_ptr<SimpleActionExecution> > analyzeActions(string action_name, string emotion,
			shared_ptr<ParameterPosition> parameter_position,
			shared_ptr<ParameterTranslation> parameter_translation);
	list<shared_ptr<SimpleActionExecution> > analyzeActions(string action_name, string emotion,
			shared_ptr<ParameterPosition> parameter_position,
			shared_ptr<ParameterTranslation> parameter_translation, string speech);
	list<shared_ptr<SimpleActionExecution> > analyzeActions(string action_name, string emotion,string speech);
	void analyzeEmotion(string emotion,
			list<shared_ptr<SimpleActionExecution> > *simple_actions,
			shared_ptr<ParameterPosition> parameter_position,
			shared_ptr<ParameterTranslation> parameter_translation);
	float calculateEmotionalFactor(float emotional_intensity, string emotion);
	void setEmotionsProfilesLoad(bool emotions_profiles_load);
	void printEmotions();
private:
	void generateActionsAvailable();
	void addAdditionalSimpleActions(string emotion,
			list<shared_ptr<SimpleActionExecution> > *simple_actions,
			shared_ptr<ParameterPosition> parameter_position,
			shared_ptr<ParameterTranslation> parameter_translation);
	void addModificationParameters(string emotion,
			list<shared_ptr<SimpleActionExecution> > *simple_actions);
	bool has_suffix(const string& s, const string& suffix);
	bool loadEmotionsAvailable(string directory_path);
	bool loadActionsAvailable(string directory_path);
	bool emotions_profiles_load;
	shared_ptr<ActionAddition> action_addition;
	shared_ptr<ActionModification> action_modification;
	map<string, shared_ptr<AbstractActionDescription> > actions_available;
	map<string, shared_ptr<EmotionProfile> > emotions_available;
	map<string, shared_ptr<PlatformDescription> > platforms_available;

};

#endif /* DECRYPTACTION_H_ */
