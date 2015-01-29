///////////////////////////////////////////////////////////
//  SequenceAbstractAction.h
//  Implementation of the Class SequenceAbstractAction
//  Created on:      01-abr-2014 05:53:26 p.m.
//  Original author: Julian
///////////////////////////////////////////////////////////

#ifndef SEQUENCEABTRACTACTIONDESCRIPTION_H
#define SEQUENCEABTRACTACTIONDESCRIPTION_H

#include "AbstractActionDescription.h"

class SequenceAbstractActionDescription : public AbstractActionDescription
{

public:
	SequenceAbstractActionDescription();
	virtual ~SequenceAbstractActionDescription();
	vector<shared_ptr<AbstractActionDescription> > getSequenceAbstractAction();
	void setSequenceAbstractAction(vector<shared_ptr<AbstractActionDescription > > abstract_actions);
	void addNewAbstractAction(shared_ptr<AbstractActionDescription> abstract_action);
protected:
	vector<shared_ptr<AbstractActionDescription> > abstract_actions;
};
#endif
