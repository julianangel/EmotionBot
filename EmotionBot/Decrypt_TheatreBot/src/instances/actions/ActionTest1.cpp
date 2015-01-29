/*
 * ActionTest1.cpp
 *
 *  Created on: Apr 3, 2014
 *      Author: julian
 */

#include "ActionTest1.h"

//ActionTest1::ActionTest1() {
	/**
	 * Walk
	 * this actions is composed by move (simple action) and oscillateShoulders (simple action)
	 */
	//Move action Parameters:
	/*SimpleActionDescription * move_walk_description = new SimpleActionDescription();
	move_walk_description->setActionName("move");
	move_walk_description->addRobotPartUsed("legs");
	move_walk_description->setActionDescription("This action moves from point A to B");
	//Shoulder action
	SimpleActionDescription * shoulder_walk_description = new SimpleActionDescription;
	shoulder_walk_description->setActionName("oscillateShoulders");
	shoulder_walk_description->addRobotPartUsed("shoulder");
	shoulder_walk_description->setActionDescription("Oscillate the shoulders");
	walk_description = new SequenceAbstractActionDescription();
	//Set information about the action
	walk_description->setActionName("walk");
	walk_description->setActionDescription("This actions moves one robot from point A to point B");
	walk_description->addRobotPartUsed("legs");
	walk_description->addRobotPartUsed("shoulder");
	walk_description->addNewAbstractAction(move_walk_description);
	walk_description->addNewAbstractAction(shoulder_walk_description);*/

	/**
	 * Walk and talk
	 * this action is composed by walk (abstract action) and talk (simple action)
	 */
	//Instance of move
	/*move_walk_description = new SimpleActionDescription();
	move_walk_description->setActionName("move");
	move_walk_description->addRobotPartUsed("legs");
	move_walk_description->setActionDescription("This action moves from point A to B");
	//Instance of oscillate shoulder
	shoulder_walk_description = new SimpleActionDescription;
	shoulder_walk_description->setActionName("oscillateShoulders");
	shoulder_walk_description->addRobotPartUsed("shoulder");
	shoulder_walk_description->setActionDescription("Oscillate the shoulders");
	//Instance of walk
	SequenceAbstractActionDescription * walk_walk_and_talk_description = new SequenceAbstractActionDescription;
	walk_walk_and_talk_description->setActionName("walk");
	walk_walk_and_talk_description->addRobotPartUsed("legs");
	walk_walk_and_talk_description->addRobotPartUsed("shoulder");
	walk_walk_and_talk_description->addNewAbstractAction(move_walk_description);
	walk_walk_and_talk_description->addNewAbstractAction(shoulder_walk_description);
	//Instance of speak
	SimpleActionDescription * speak_walk_and_talk_description = new SimpleActionDescription();
	speak_walk_and_talk_description->setActionName("speak");
	speak_walk_and_talk_description->addRobotPartUsed("speaker");
	//walk and talk
	walk_and_talk_description = new SequenceAbstractActionDescription;
	walk_and_talk_description->setActionName("move_and_talk");
	walk_and_talk_description->setActionDescription("This generates walking and speaking");
	walk_and_talk_description->addRobotPartUsed("legs");
	walk_and_talk_description->addRobotPartUsed("shoulder");
	walk_and_talk_description->addRobotPartUsed("speaker");
	walk_and_talk_description->addNewAbstractAction(walk_walk_and_talk_description);
	walk_and_talk_description->addNewAbstractAction(speak_walk_and_talk_description);*/
//}

ActionTest1::ActionTest1() {
	//walk_description = new SequenceAbstractActionDescription();
	this->generateWalkDescription();
	//walk_and_talk_description = new SequenceAbstractActionDescription;
	this->generateWalkAndTalkDescription();
}

ActionTest1::~ActionTest1() {
}

/**
	 * Walk
	 * this actions is composed by move (simple action) and oscillateShoulders (simple action)
	 */
void ActionTest1::generateWalkDescription(){
	/*MoveBodySimpleActionDescription * move_body_simple_action = new MoveBodySimpleActionDescription;
	MoveShoulderSimpleActionDescription * move_shoulder_simple_action = new MoveShoulderSimpleActionDescription;
	walk_description->setActionName("walk");
	walk_description->setActionDescription("This actions moves one robot from point A to point B");
	walk_description->addRobotPartUsed("legs");
	walk_description->addRobotPartUsed("shoulder");
	walk_description->addNewAbstractAction(move_body_simple_action);
	walk_description->addNewAbstractAction(move_shoulder_simple_action);*/
}
/**
	 * Walk and talk
	 * this action is composed by walk (abstract action) and talk (simple action)
	 */
void ActionTest1::generateWalkAndTalkDescription(){
	/*MoveBodySimpleActionDescription * move_body_simple_action = new MoveBodySimpleActionDescription;
	MoveShoulderSimpleActionDescription * move_shoulder_simple_action = new MoveShoulderSimpleActionDescription;
	walk_and_talk_description->setActionName("move_and_talk");
	walk_and_talk_description->setActionDescription("This generates walking and speaking");
	walk_and_talk_description->addRobotPartUsed("legs");
	walk_and_talk_description->addRobotPartUsed("shoulder");
	walk_and_talk_description->addNewAbstractAction(move_body_simple_action);
	walk_and_talk_description->addNewAbstractAction(move_shoulder_simple_action);*/

}

shared_ptr<SequenceAbstractActionDescription> ActionTest1::getWalDescription(){
	return this->walk_description;
}


shared_ptr<SequenceAbstractActionDescription> ActionTest1::getWalkAndTalkDescription(){
	return this->walk_and_talk_description;
}
