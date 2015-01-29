/*
 * EmotionTest1.cpp
 *
 *  Created on: Apr 15, 2014
 *      Author: julian
 */

#include "EmotionTest1.h"

EmotionTest1::EmotionTest1() {

	this->createMoveHappy();
	this->createMoveAngry();
}

void EmotionTest1::createMoveHappy(){
	/*
	 * This emotion change the movement of the action emotion
	 * for move and happy, the action oscillation move is added
	 */
	//Required to generate the emotion description
	shared_ptr<EmotionParameter> emotion_parameter;
	//
	shared_ptr<ActionChanges> action_changes_move(new ActionChanges);
	//Sets the action's name, in this case it would be change the action move
	action_changes_move->setActionChangesName("move_body");
	emotion_parameter.reset(new EmotionParameter);
	emotion_parameter->setEmotionParameterTime(1250.0);
	emotion_parameter->setEmotionParameterSpacing(1000.0);
	action_changes_move->addActioChangesParameter(emotion_parameter);
	action_changes_move->setTypeActionEmotion(TypeActionEmotionChangeStaticAction);
	//Sets the action's name, in this case it would be change the action oscillation_move
	shared_ptr<ActionChanges> action_changes_oscillation_move(new ActionChanges);
	action_changes_oscillation_move->setActionChangesName("oscillate_body");
	emotion_parameter.reset(new EmotionParameter);
	emotion_parameter->setEmotionParameterTime(0.1);
	emotion_parameter->setEmotionParameterSpacing(0.08);//In this case in radians
	action_changes_oscillation_move->addActioChangesParameter(emotion_parameter);
	action_changes_oscillation_move->setTypeActionEmotion(TypeActionEmotionChangeStaticAction);
	/*
	 * It is created the emotion profile for move and happy
	 */
	emotion_profile_happy_move.reset(new EmotionProfile);
	//Set the name
	emotion_profile_happy_move->setEmotionProfileName("happy_move_body");
	//Action that should be modify
	emotion_profile_happy_move->setEmotionProfileAction("move_body");
	//Emotion that should be convey
	emotion_profile_happy_move->setEmotionProfileEmotion("happy");
	//Add change on the parameters
	emotion_profile_happy_move->addEmotionProfileActionChanges(action_changes_move);
	emotion_profile_happy_move->addEmotionProfileActionChanges(action_changes_oscillation_move);
}

void EmotionTest1::createMoveSad(){

}

void EmotionTest1::createMoveAngry(){
	//Required to generate the emotion description
	shared_ptr<EmotionParameter>emotion_parameter;
	//
	shared_ptr<ActionChanges>action_changes_move(new ActionChanges);
	//Sets the action's name, in this case it would be change the action move
	action_changes_move->setActionChangesName("move_body");
	//-->0
	emotion_parameter.reset(new EmotionParameter);
	emotion_parameter->setEmotionParameterTime(500.0);
	emotion_parameter->setEmotionParameterSpacing(200.0);
	action_changes_move->addActioChangesParameter(emotion_parameter);
	//-->1
	emotion_parameter.reset(new EmotionParameter);
	emotion_parameter->setEmotionParameterTime(300.0);
	emotion_parameter->setEmotionParameterSpacing(300.0);
	action_changes_move->addActioChangesParameter(emotion_parameter);
	//-->2
	emotion_parameter.reset(new EmotionParameter);
	emotion_parameter->setEmotionParameterTime(625.0);
	emotion_parameter->setEmotionParameterSpacing(500.0);
	action_changes_move->addActioChangesParameter(emotion_parameter);
	//-->3
	emotion_parameter.reset(new EmotionParameter);
	emotion_parameter->setEmotionParameterTime(350.0);
	emotion_parameter->setEmotionParameterSpacing(500.0);
	action_changes_move->addActioChangesParameter(emotion_parameter);
	//---
	action_changes_move->setTypeActionEmotion(TypeActionEmotionChangeDynamiAction);
	//Sets the action's name, in this case it would be change the action oscillation_move
	shared_ptr<ActionChanges> action_changes_oscillation_move(new ActionChanges);
	action_changes_oscillation_move->setActionChangesName("oscillate_body");
	//-->0
	emotion_parameter.reset(new EmotionParameter);
	emotion_parameter->setEmotionParameterTime(0.0125);
	emotion_parameter->setEmotionParameterSpacing(0.01);//In this case in radians
	action_changes_oscillation_move->addActioChangesParameter(emotion_parameter);
	//-->1
	emotion_parameter.reset(new EmotionParameter);
	emotion_parameter->setEmotionParameterTime(0.0);
	emotion_parameter->setEmotionParameterSpacing(0.0);//In this case in radians
	action_changes_oscillation_move->addActioChangesParameter(emotion_parameter);
	//-->2
	emotion_parameter.reset(new EmotionParameter);
	emotion_parameter->setEmotionParameterTime(0.0125);
	emotion_parameter->setEmotionParameterSpacing(0.01);//In this case in radians
	action_changes_oscillation_move->addActioChangesParameter(emotion_parameter);
	//-->3
	emotion_parameter.reset(new EmotionParameter);
	emotion_parameter->setEmotionParameterTime(0.0);
	emotion_parameter->setEmotionParameterSpacing(0.0);//In this case in radians
	action_changes_oscillation_move->addActioChangesParameter(emotion_parameter);
	//---
	action_changes_oscillation_move->setTypeActionEmotion(TypeActionEmotionChangeDynamiAction);/*
	 * It is created the emotion profile for move and angry
	 */
	emotion_profile_angry_move.reset(new EmotionProfile);
	//Set the name
	emotion_profile_angry_move->setEmotionProfileName("angry_move_body");
	//Action that should be modify
	emotion_profile_angry_move->setEmotionProfileAction("move_body");
	//Emotion that should be convey
	emotion_profile_angry_move->setEmotionProfileEmotion("angry");
	//Add change on the parameters
	emotion_profile_angry_move->addEmotionProfileActionChanges(action_changes_move);
	emotion_profile_angry_move->addEmotionProfileActionChanges(action_changes_oscillation_move);

}

EmotionTest1::~EmotionTest1() {

}

shared_ptr<EmotionProfile> EmotionTest1::getEmotionProfileMoveHappy(){
	return this->emotion_profile_happy_move;
}

shared_ptr<EmotionProfile> EmotionTest1::getEmotionProfileMoveAngry(){
	return this->emotion_profile_angry_move;
}

map<string,shared_ptr<EmotionProfile> > EmotionTest1::getEmotionProfile(){
	map<string,shared_ptr<EmotionProfile> > emotions_generated;
	emotions_generated[this->getEmotionProfileMoveAngry()->getEmotionProfileName()] = this->getEmotionProfileMoveAngry();
	emotions_generated[this->getEmotionProfileMoveHappy()->getEmotionProfileName()] = this->getEmotionProfileMoveHappy();
	return emotions_generated;
}
