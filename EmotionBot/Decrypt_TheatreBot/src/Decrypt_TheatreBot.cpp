//============================================================================
// Name        : Decrypt_TheatreBot.cpp
// Author      : Julian
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <vector>
#include <typeinfo>

//#include "instances/actions/ActionTest1.h"
#include "instances/emotion_profiles/EmotionTest1.h"
#include "instances/platform_profiles/PlatformTest1.h"
#include "general_description/action_description/instance_compound_action_description/WalkAndSpeakCompoundAction.h"
#include "general_description/action_description/instance_compound_action_description/WalkCompoundAction.h"
#include "general_description/parameters_description/parameters_instances/ParameterVelocity.h"
#include "action_modulation/ActionAddition.h"
#include "action_modulation/ActionModification.h"

using namespace std;

int main() {
	/*
	 * Upload the system parameters
	 */

	/***************************
	 * Variables
	 ***************************/
	EmotionTest1 *emotionTest = new EmotionTest1;
	WalkCompoundAction *walk_action = new WalkCompoundAction;
	PlatformTest1 *platformTest = new PlatformTest1;
	ActionAddition *action_addition = new ActionAddition;
	ActionModification *action_modification = new ActionModification;
	/******************************
	 * Actions profiles
	 ******************************/
	WalkAndSpeakCompoundAction * walk_speak_action = new WalkAndSpeakCompoundAction;
	/**************************************
	 * emotion profiles
	 **************************************/
	map<string,EmotionProfile *> emotions_generated;
	emotions_generated[emotionTest->getEmotionProfileMoveAngry()->getEmotionProfileName()] = emotionTest->getEmotionProfileMoveAngry();
	emotions_generated[emotionTest->getEmotionProfileMoveHappy()->getEmotionProfileName()] = emotionTest->getEmotionProfileMoveHappy();
	/***************************************
	 * platform profiles
	 ***************************************/
	map<string, PlatformDescription *> temp_platforms = platformTest->getPlatformDescription();
	/*******************************
	 * Send action with parameters
	 *******************************/
	PointPositionParameter *position_parameter = new PointPositionParameter;
	position_parameter->setPointPosition(1000.0,0.0,0.0);
	walk_action->setParameterPosition(position_parameter);
	position_parameter = new PointPositionParameter;
	position_parameter->setPointPosition(1500.0,0.0,0.0);
	walk_speak_action->setParameterPosition(position_parameter);
	/******************************
	 * Call the method to create simple actions
	 ******************************/
	list<SimpleActionExecution *> temp_analyze_walks_action = walk_speak_action->Analyze();
	list<SimpleActionExecution *> temp_analyze_walks_speak_action = walk_speak_action->Analyze();
	/************
	 * Add additional movements
	 ************/
	//Get the missing actions
	action_addition->addAdditionalSimpleActions("happy_move", &temp_analyze_walks_speak_action,
					emotions_generated);
	for(list<SimpleActionExecution *>::iterator it = temp_analyze_walks_speak_action.begin();
			it != temp_analyze_walks_speak_action.end(); it++){
		cout<<(*it)->getActionName()<<" - "<<typeid(*(*it)).name()<< "-> "<<(typeid(*(*it)).name()==typeid(MoveBodyExecution).name())<<endl;
	}
	/************
	 * changing parameters
	 ************/
	action_modification->modifySimpleActions("happy_move", &temp_analyze_walks_speak_action,
					emotions_generated);
	/********
	 * Delete everything
	 *******/
	delete walk_action;
	delete walk_speak_action;
	delete emotionTest;
	delete platformTest;
	return 0;
}
