/*
 * NotDoAnythingSimpleAction.h
 *
 *  Created on: Jul 18, 2014
 *      Author: julian
 */

#ifndef NOTDOANYTHINGSIMPLEACTION_H_
#define NOTDOANYTHINGSIMPLEACTION_H_

#include "../SimpleActionDescription.h"
#include "../../../general_execution/action_execution/NotDoAnythingExecution.h"

class NotDoAnythingSimpleAction: public SimpleActionDescription {
public:
	NotDoAnythingSimpleAction();
	virtual ~NotDoAnythingSimpleAction();
	list<shared_ptr<SimpleActionExecution> > Analyze(void);
};

#endif /* NOTDOANYTHINGSIMPLEACTION_H_ */
