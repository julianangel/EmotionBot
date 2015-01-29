/*
 * NotDoAnythingSimpleAction.cpp
 *
 *  Created on: Jul 18, 2014
 *      Author: julian
 */

#include "NotDoAnythingSimpleAction.h"

NotDoAnythingSimpleAction::NotDoAnythingSimpleAction() {
	this->action_name = "not_do_anything";
	this->robot_parts_used.push_back("none");
}

NotDoAnythingSimpleAction::~NotDoAnythingSimpleAction() {
}

list<shared_ptr<SimpleActionExecution> > NotDoAnythingSimpleAction::Analyze(){
	list<shared_ptr<SimpleActionExecution> > temp;
	shared_ptr<NotDoAnythingExecution> not_do_anything(new NotDoAnythingExecution);
	not_do_anything->setTypeAction(TypeActionMandatory);
	not_do_anything->setActionIsPrincipal(this->action_is_principal);
	temp.push_back(not_do_anything);
	return temp;
}

