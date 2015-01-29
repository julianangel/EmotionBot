///////////////////////////////////////////////////////////
//  SimpleAction.h
//  Implementation of the Class SimpleAction
//  Created on:      01-abr-2014 05:53:26 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef SIMPLEACTIONDESCRIPTION_H
#define SIMPLEACTIONDESCRIPTION_H

#include "AbstractActionDescription.h"

/*
 * This action is the terminal class in the pattern composed. Thus it has more information
 * that the other classes.
 */

class SimpleActionDescription : public AbstractActionDescription
{

public:
	//Methods
	SimpleActionDescription();
	virtual ~SimpleActionDescription();
	list<shared_ptr<SimpleActionExecution> > Analyze(void) =0;
private:

};
#endif
