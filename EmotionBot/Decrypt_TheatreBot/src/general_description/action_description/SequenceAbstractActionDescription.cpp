///////////////////////////////////////////////////////////
//  SequenceAbstractAction.cpp
//  Implementation of the Class SequenceAbstractAction
//  Created on:      01-abr-2014 05:53:26 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#include "SequenceAbstractActionDescription.h"


SequenceAbstractActionDescription::SequenceAbstractActionDescription(){

}



SequenceAbstractActionDescription::~SequenceAbstractActionDescription(){

}


vector<shared_ptr<AbstractActionDescription> >
SequenceAbstractActionDescription::getSequenceAbstractAction(){
	return this->abstract_actions;
}

void
SequenceAbstractActionDescription::
setSequenceAbstractAction(vector<shared_ptr<AbstractActionDescription> > abstract_actions){
	this->abstract_actions = abstract_actions;
}

void SequenceAbstractActionDescription::addNewAbstractAction(shared_ptr<AbstractActionDescription> abstract_action){
	this->abstract_actions.push_back(abstract_action);
}
