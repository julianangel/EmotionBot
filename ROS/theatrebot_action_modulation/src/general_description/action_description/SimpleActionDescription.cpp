///////////////////////////////////////////////////////////
//  SimpleAction.cpp
//  Implementation of the Class SimpleAction
//  Created on:      01-abr-2014 05:53:26 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#include "SimpleActionDescription.h"


SimpleActionDescription::SimpleActionDescription(){
	this->action_is_principal = true;
}



SimpleActionDescription::~SimpleActionDescription(){

}


void SimpleActionDescription::setActionIsPrincipal(bool action_is_principal){
	this->action_is_principal = action_is_principal;
}

bool SimpleActionDescription::getActionIsPrincipal(){
	return this->action_is_principal;
}
